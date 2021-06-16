#include "CorePch.h"
#include "ResourceManager.h"
#include "Terrain.h"

std::shared_ptr<Mesh> ResourceManager::LoadCubeMesh()
{
	std::shared_ptr<Mesh> findMesh = Get<Mesh>(L"Cube");
	if (findMesh)
		return findMesh;

	float w2 = 0.5f;
	float h2 = 0.5f;
	float d2 = 0.5f;

	std::vector<Vertex> vec(24);

	// ¾Õ¸é
	vec[0] = Vertex(vec3(-w2, -h2, -d2), vec2(0.0f, 1.0f), vec3(0.0f, 0.0f, -1.0f), vec3(1.0f, 0.0f, 0.0f));
	vec[1] = Vertex(vec3(-w2, +h2, -d2), vec2(0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f), vec3(1.0f, 0.0f, 0.0f));
	vec[2] = Vertex(vec3(+w2, +h2, -d2), vec2(1.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f), vec3(1.0f, 0.0f, 0.0f));
	vec[3] = Vertex(vec3(+w2, -h2, -d2), vec2(1.0f, 1.0f), vec3(0.0f, 0.0f, -1.0f), vec3(1.0f, 0.0f, 0.0f));
	// µÞ¸é
	vec[4] = Vertex(vec3(-w2, -h2, +d2), vec2(1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f), vec3(-1.0f, 0.0f, 0.0f));
	vec[5] = Vertex(vec3(+w2, -h2, +d2), vec2(0.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f), vec3(-1.0f, 0.0f, 0.0f));
	vec[6] = Vertex(vec3(+w2, +h2, +d2), vec2(0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), vec3(-1.0f, 0.0f, 0.0f));
	vec[7] = Vertex(vec3(-w2, +h2, +d2), vec2(1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), vec3(-1.0f, 0.0f, 0.0f));
	// À­¸é
	vec[8] = Vertex(vec3(-w2, +h2, -d2), vec2(0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f));
	vec[9] = Vertex(vec3(-w2, +h2, +d2), vec2(0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f));
	vec[10] = Vertex(vec3(+w2, +h2, +d2), vec2(1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f));
	vec[11] = Vertex(vec3(+w2, +h2, -d2), vec2(1.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f));
	// ¾Æ·§¸é
	vec[12] = Vertex(vec3(-w2, -h2, -d2), vec2(1.0f, 1.0f), vec3(0.0f, -1.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f));
	vec[13] = Vertex(vec3(+w2, -h2, -d2), vec2(0.0f, 1.0f), vec3(0.0f, -1.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f));
	vec[14] = Vertex(vec3(+w2, -h2, +d2), vec2(0.0f, 0.0f), vec3(0.0f, -1.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f));
	vec[15] = Vertex(vec3(-w2, -h2, +d2), vec2(1.0f, 0.0f), vec3(0.0f, -1.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f));
	// ¿ÞÂÊ¸é
	vec[16] = Vertex(vec3(-w2, -h2, +d2), vec2(0.0f, 1.0f), vec3(-1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));
	vec[17] = Vertex(vec3(-w2, +h2, +d2), vec2(0.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));
	vec[18] = Vertex(vec3(-w2, +h2, -d2), vec2(1.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));
	vec[19] = Vertex(vec3(-w2, -h2, -d2), vec2(1.0f, 1.0f), vec3(-1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));
	// ¿À¸¥ÂÊ¸é
	vec[20] = Vertex(vec3(+w2, -h2, -d2), vec2(0.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f));
	vec[21] = Vertex(vec3(+w2, +h2, -d2), vec2(0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f));
	vec[22] = Vertex(vec3(+w2, +h2, +d2), vec2(1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f));
	vec[23] = Vertex(vec3(+w2, -h2, +d2), vec2(1.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f));

	std::vector<uint32> idx(36);

	// ¾Õ¸é
	idx[0] = 0; idx[1] = 1; idx[2] = 2;
	idx[3] = 0; idx[4] = 2; idx[5] = 3;
	// µÞ¸é
	idx[6] = 4; idx[7] = 5; idx[8] = 6;
	idx[9] = 4; idx[10] = 6; idx[11] = 7;
	// À­¸é
	idx[12] = 8; idx[13] = 9; idx[14] = 10;
	idx[15] = 8; idx[16] = 10; idx[17] = 11;
	// ¾Æ·§¸é
	idx[18] = 12; idx[19] = 13; idx[20] = 14;
	idx[21] = 12; idx[22] = 14; idx[23] = 15;
	// ¿ÞÂÊ¸é
	idx[24] = 16; idx[25] = 17; idx[26] = 18;
	idx[27] = 16; idx[28] = 18; idx[29] = 19;
	// ¿À¸¥ÂÊ¸é
	idx[30] = 20; idx[31] = 21; idx[32] = 22;
	idx[33] = 20; idx[34] = 22; idx[35] = 23;

	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
	mesh->Init(vec, idx);
	Add(L"Cube", mesh);

	return mesh;
}

std::shared_ptr<Mesh> ResourceManager::LoadSphereMesh()
{
	std::shared_ptr<Mesh> findMesh = Get<Mesh>(L"Sphere");
	if (findMesh)
		return findMesh;

	float radius = 0.5f; // ±¸ÀÇ ¹ÝÁö¸§
	uint32 stackCount = 20; // °¡·Î ºÐÇÒ
	uint32 sliceCount = 20; // ¼¼·Î ºÐÇÒ

	std::vector<Vertex> vec;

	Vertex v;

	// ºÏ±Ø
	v.Position = vec3(0.0f, radius, 0.0f);
	v.UV = vec2(0.5f, 0.0f);
	v.Normal = v.Position;
	v.Normal.Normalize();
	v.Tangent = vec3(1.0f, 0.0f, 1.0f);
	vec.push_back(v);

	float stackAngle = XM_PI / stackCount;
	float sliceAngle = XM_2PI / sliceCount;

	float deltaU = 1.f / static_cast<float>(sliceCount);
	float deltaV = 1.f / static_cast<float>(stackCount);

	// °í¸®¸¶´Ù µ¹¸é¼­ Á¤Á¡À» °è»êÇÑ´Ù (ºÏ±Ø/³²±Ø ´ÜÀÏÁ¡Àº °í¸®°¡ X)
	for (uint32 y = 1; y <= stackCount - 1; ++y)
	{
		float phi = y * stackAngle;

		// °í¸®¿¡ À§Ä¡ÇÑ Á¤Á¡
		for (uint32 x = 0; x <= sliceCount; ++x)
		{
			float theta = x * sliceAngle;

			v.Position.x = radius * sinf(phi) * cosf(theta);
			v.Position.y = radius * cosf(phi);
			v.Position.z = radius * sinf(phi) * sinf(theta);

			v.UV = vec2(deltaU * x, deltaV * y);

			v.Normal = v.Position;
			v.Normal.Normalize();

			v.Tangent.x = -radius * sinf(phi) * sinf(theta);
			v.Tangent.y = 0.0f;
			v.Tangent.z = radius * sinf(phi) * cosf(theta);
			v.Tangent.Normalize();

			vec.push_back(v);
		}
	}

	// ³²±Ø
	v.Position = vec3(0.0f, -radius, 0.0f);
	v.UV = vec2(0.5f, 1.0f);
	v.Normal = v.Position;
	v.Normal.Normalize();
	v.Tangent = vec3(1.0f, 0.0f, 0.0f);
	vec.push_back(v);

	std::vector<uint32> idx(36);

	// ºÏ±Ø ÀÎµ¦½º
	for (uint32 i = 0; i <= sliceCount; ++i)
	{
		//  [0]
		//   |  \
		//  [i+1]-[i+2]
		idx.push_back(0);
		idx.push_back(i + 2);
		idx.push_back(i + 1);
	}

	// ¸öÅë ÀÎµ¦½º
	uint32 ringVertexCount = sliceCount + 1;
	for (uint32 y = 0; y < stackCount - 2; ++y)
	{
		for (uint32 x = 0; x < sliceCount; ++x)
		{
			//  [y, x]-[y, x+1]
			//  |		/
			//  [y+1, x]
			idx.push_back(1 + (y)*ringVertexCount + (x));
			idx.push_back(1 + (y)*ringVertexCount + (x + 1));
			idx.push_back(1 + (y + 1) * ringVertexCount + (x));
			//		 [y, x+1]
			//		 /	  |
			//  [y+1, x]-[y+1, x+1]
			idx.push_back(1 + (y + 1) * ringVertexCount + (x));
			idx.push_back(1 + (y)*ringVertexCount + (x + 1));
			idx.push_back(1 + (y + 1) * ringVertexCount + (x + 1));
		}
	}

	// ³²±Ø ÀÎµ¦½º
	uint32 bottomIndex = static_cast<uint32>(vec.size()) - 1;
	uint32 lastRingStartIndex = bottomIndex - ringVertexCount;
	for (uint32 i = 0; i < sliceCount; ++i)
	{
		//  [last+i]-[last+i+1]
		//  |      /
		//  [bottom]
		idx.push_back(bottomIndex);
		idx.push_back(lastRingStartIndex + i);
		idx.push_back(lastRingStartIndex + i + 1);
	}

	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
	mesh->Init(vec, idx);
	Add(L"Sphere", mesh);

	return mesh;
}

std::shared_ptr<Mesh> ResourceManager::LoadTerrainMesh(int32 sizeX, int32 sizeZ)
{
	std::shared_ptr<Mesh> findMesh = Get<Mesh>(L"Terrain");
	if (findMesh)
	{
		return findMesh;
	}

	//std::vector<Vertex> vec;

	//for (int32 z = 0; z < sizeZ + 1; z++)
	//{
	//	for (int32 x = 0; x < sizeX + 1; x++)
	//	{
	//		Vertex vtx;
	//		vtx.Position = vec3(static_cast<float>(x), 0, static_cast<float>(z));
	//		vtx.UV = vec2(static_cast<float>(x), static_cast<float>(sizeZ - z));
	//		vtx.Normal = vec3(0.f, 1.f, 0.f);
	//		vtx.Tangent = vec3(1.f, 0.f, 0.f);

	//		vec.push_back(vtx);
	//	}
	//}

	//std::vector<uint32> idx;

	//for (int32 z = 0; z < sizeZ; z++)
	//{
	//	for (int32 x = 0; x < sizeX; x++)
	//	{
	//		//  [0]
	//		//   |	\
	//		//  [2] - [1]
	//		idx.push_back((sizeX + 1) * (z + 1) + (x));
	//		idx.push_back((sizeX + 1) * (z)+(x + 1));
	//		idx.push_back((sizeX + 1) * (z)+(x));
	//		//  [1] - [2]
	//		//   	\  |
	//		//		  [0]
	//		idx.push_back((sizeX + 1) * (z)+(x + 1));
	//		idx.push_back((sizeX + 1) * (z + 1) + (x));
	//		idx.push_back((sizeX + 1) * (z + 1) + (x + 1));
	//	}
	//}
	//
	//std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
	//mesh->Init(vec, idx);
	//Add(L"Terrain", mesh);
	//return mesh;

	std::unique_ptr<Terrain> terrain = std::make_unique<Terrain>();
	return terrain->Init("..//Resources//Textures//heightmap01.bmp");
}