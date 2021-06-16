#pragma once

class Mesh;

class Terrain
{
	struct HeightMapType
	{
		float x, y, z;
	};

public:
	std::shared_ptr<Mesh> Init(const char* filename);

private:
	bool loadHeightMap(const char* filename);
	void normalizeHeightMap();
	std::shared_ptr<Mesh> generateBuffers();

private:
	int mTerrainWidth = 0;
	int mTerrainHeight = 0;
	int mVertexCount = 0;
	int mIndexCount = 0;

	HeightMapType* mHeightMap = nullptr;
};