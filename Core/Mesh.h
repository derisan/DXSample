#pragma once

#include "Object.h"

class Texture;
class Material;

class Mesh : public Object
{
public:
	Mesh();

	void Init(const std::vector<Vertex>& vertices, const std::vector<uint32>& indices);
	void Render();

private:
	ComPtr<ID3D12Resource> mVertexBuffer = nullptr;
	D3D12_VERTEX_BUFFER_VIEW mVertexBufferView = {};
	uint32 mVertexCount = 0;

	ComPtr<ID3D12Resource> mIndexBuffer = nullptr;
	D3D12_INDEX_BUFFER_VIEW mIndexBufferView = {};
	uint32 mIndexCount = 0;
};

