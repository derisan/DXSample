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
	void SetTopology(D3D_PRIMITIVE_TOPOLOGY topo) { mTopology = topo; }

private:
	ComPtr<ID3D12Resource> mVertexBuffer = nullptr;
	D3D12_VERTEX_BUFFER_VIEW mVertexBufferView = {};
	uint32 mVertexCount = 0;

	ComPtr<ID3D12Resource> mIndexBuffer = nullptr;
	D3D12_INDEX_BUFFER_VIEW mIndexBufferView = {};
	uint32 mIndexCount = 0;

	D3D_PRIMITIVE_TOPOLOGY mTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
};

