#pragma once

class Texture;
class Material;

class Mesh
{
public:
	void Init(const std::vector<Vertex>& vertices, const std::vector<uint32>& indices);
	void Render();

	void SetOffset(const vec4& offset) { mOffset = offset; }
	void SetMaterial(std::shared_ptr<Material> material) { mMaterial = std::move(material); }

private:
	ComPtr<ID3D12Resource> mVertexBuffer = nullptr;
	D3D12_VERTEX_BUFFER_VIEW mVertexBufferView = {};
	uint32 mVertexCount = 0;

	ComPtr<ID3D12Resource> mIndexBuffer = nullptr;
	D3D12_INDEX_BUFFER_VIEW mIndexBufferView = {};
	uint32 mIndexCount = 0;

	std::shared_ptr<Material> mMaterial = nullptr;

	vec4 mOffset = {};
};

