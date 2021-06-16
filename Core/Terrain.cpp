#include "CorePch.h"
#include "Terrain.h"
#include "Mesh.h"

std::shared_ptr<Mesh> Terrain::Init(const char* filename)
{
	loadHeightMap(filename);

	normalizeHeightMap();

	return generateBuffers();
}

bool Terrain::loadHeightMap(const char* filename)
{
	// 바이너리 모드로 높이맵 파일을 엽니다.
	FILE* filePtr = nullptr;
	if (fopen_s(&filePtr, filename, "rb") != 0)
	{
		return false;
	}

	// 파일 헤더를 읽습니다.
	BITMAPFILEHEADER bitmapFileHeader;
	if (fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr) != 1)
	{
		return false;
	}

	// 비트맵 정보 헤더를 읽습니다.
	BITMAPINFOHEADER bitmapInfoHeader;
	if (fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr) != 1)
	{
		return false;
	}

	// 지형의 크기를 저장합니다.
	mTerrainWidth = bitmapInfoHeader.biWidth;
	mTerrainHeight = bitmapInfoHeader.biHeight;

	// 비트맵 이미지 데이터의 크기를 계산합니다.
	int imageSize = mTerrainWidth * mTerrainHeight * 3;

	// 비트맵 이미지 데이터에 메모리를 할당합니다.
	unsigned char* bitmapImage = new unsigned char[imageSize];
	if (!bitmapImage)
	{
		return false;
	}

	// 비트맵 데이터의 시작 부분으로 이동합니다.
	fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

	// 비트맵 이미지 데이터를 읽습니다.
	if (fread(bitmapImage, 1, imageSize, filePtr) != imageSize)
	{
		return false;
	}

	// 파일을 닫습니다.
	if (fclose(filePtr) != 0)
	{
		return false;
	}

	// 높이 맵 데이터를 저장할 구조체를 만듭니다.
	mHeightMap = new HeightMapType[mTerrainWidth * mTerrainHeight];
	if (!mHeightMap)
	{
		return false;
	}

	// 이미지 데이터 버퍼의 위치를 ​​초기화합니다.
	int k = 0;

	// 이미지 데이터를 높이 맵으로 읽어들입니다.
	for (int j = 0; j < mTerrainHeight; j++)
	{
		for (int i = 0; i < mTerrainWidth; i++)
		{
			unsigned char height = bitmapImage[k];

			int index = (mTerrainHeight * j) + i;

			mHeightMap[index].x = (float)i;
			mHeightMap[index].y = (float)height;
			mHeightMap[index].z = (float)j;

			k += 3;
		}
	}

	// 비트맵 이미지 데이터를 해제합니다.
	delete[] bitmapImage;
	bitmapImage = 0;

	return true;
}

void Terrain::normalizeHeightMap()
{
	for (int j = 0; j < mTerrainHeight; j++)
	{
		for (int i = 0; i < mTerrainWidth; i++)
		{
			mHeightMap[(mTerrainHeight * j) + i].y /= 15.0f;
		}
	}
}

std::shared_ptr<Mesh> Terrain::generateBuffers()
{
		// 지형 메쉬의 정점 수를 계산합니다.
	mVertexCount = (mTerrainWidth - 1) * (mTerrainHeight - 1) * 12;

	// 인덱스 수를 꼭지점 수와 같게 설정합니다.
	mIndexCount = mVertexCount;

	// 정점 배열을 만듭니다.
	std::vector<Vertex> vertices(mVertexCount);


	std::vector<uint32> indices(mIndexCount);

	// 정점 배열에 대한 인덱스를 초기화합니다.
	int index = 0;

	// 지형 데이터로 정점 및 인덱스 배열을 로드합니다.
	for(int j=0; j<(mTerrainHeight-1); j++)
	{
		for(int i=0; i<(mTerrainWidth-1); i++)
		{
			int index1 = (mTerrainHeight * j) + i;          // 왼쪽 아래.
			int index2 = (mTerrainHeight * j) + (i+1);      // 오른쪽 아래.
			int index3 = (mTerrainHeight * (j+1)) + i;      // 왼쪽 위.
			int index4 = (mTerrainHeight * (j+1)) + (i+1);  // 오른쪽 위.

			// 왼쪽 위.
			vertices[index].Position = XMFLOAT3(mHeightMap[index3].x, mHeightMap[index3].y, mHeightMap[index3].z);
			//vertices[index].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			indices[index] = index;
			index++;

			// 오른쪽 위.
			vertices[index].Position = XMFLOAT3(mHeightMap[index4].x, mHeightMap[index4].y, mHeightMap[index4].z);
			//vertices[index].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			indices[index] = index;
			index++;

			// 오른쪽 위.
			vertices[index].Position = XMFLOAT3(mHeightMap[index4].x, mHeightMap[index4].y, mHeightMap[index4].z);
			//vertices[index].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			indices[index] = index;
			index++;

			// 왼쪽 아래.
			vertices[index].Position = XMFLOAT3(mHeightMap[index1].x, mHeightMap[index1].y, mHeightMap[index1].z);
			//vertices[index].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			indices[index] = index;
			index++;

			// 왼쪽 아래.
			vertices[index].Position = XMFLOAT3(mHeightMap[index1].x, mHeightMap[index1].y, mHeightMap[index1].z);
			//vertices[index].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			indices[index] = index;
			index++;

			// 왼쪽 위.
			vertices[index].Position = XMFLOAT3(mHeightMap[index3].x, mHeightMap[index3].y, mHeightMap[index3].z);
			//vertices[index].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			indices[index] = index;
			index++;

			// 왼쪽 아래.
			vertices[index].Position = XMFLOAT3(mHeightMap[index1].x, mHeightMap[index1].y, mHeightMap[index1].z);
			//vertices[index].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			indices[index] = index;
			index++;

			// 오른쪽 위.
			vertices[index].Position = XMFLOAT3(mHeightMap[index4].x, mHeightMap[index4].y, mHeightMap[index4].z);
			//vertices[index].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			indices[index] = index;
			index++;

			// 오른쪽 위.
			vertices[index].Position = XMFLOAT3(mHeightMap[index4].x, mHeightMap[index4].y, mHeightMap[index4].z);
			//vertices[index].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			indices[index] = index;
			index++;

			// 오른쪽 아래.
			vertices[index].Position = XMFLOAT3(mHeightMap[index2].x, mHeightMap[index2].y, mHeightMap[index2].z);
			//vertices[index].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			indices[index] = index;
			index++;

			// 오른쪽 아래.
			vertices[index].Position = XMFLOAT3(mHeightMap[index2].x, mHeightMap[index2].y, mHeightMap[index2].z);
			//vertices[index].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			indices[index] = index;
			index++;

			// 왼쪽 아래.
			vertices[index].Position = XMFLOAT3(mHeightMap[index1].x, mHeightMap[index1].y, mHeightMap[index1].z);
			//vertices[index].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			indices[index] = index;
			index++;			
		}
	}

	std::shared_ptr<Mesh> terrain = std::make_shared<Mesh>();
	terrain->Init(vertices, indices);
	return terrain;
}

