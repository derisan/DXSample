#pragma once

class Texture;

class Mesh
{
public:
	void Init(const std::vector<Vertex>& vertices, const std::vector<uint32>& indices);
	void Render();

	void SetTexture(std::shared_ptr<Texture> texture) { mTexture = texture; }

private:
	ComPtr<ID3D12Resource> mVertexBuffer = nullptr;
	D3D12_VERTEX_BUFFER_VIEW mVertexBufferView = {};
	uint32 mVertexCount = 0;

	ComPtr<ID3D12Resource> mIndexBuffer = nullptr;
	D3D12_INDEX_BUFFER_VIEW mIndexBufferView = {};
	uint32 mIndexCount = 0;

	std::shared_ptr<Texture> mTexture = nullptr;
};

