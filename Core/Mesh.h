#pragma once

class Mesh
{
public:
	void Init(std::vector<Vertex>& vec);
	void Render();

private:
	ComPtr<ID3D12Resource> mVertexBuffer = nullptr;
	D3D12_VERTEX_BUFFER_VIEW mVertexBufferView = {};
	uint32 mVertexCount = 0;
};

