#include "CorePch.h"
#include "Mesh.h"
#include "Engine.h"

void Mesh::Init(std::vector<Vertex>& vec)
{
	mVertexCount = vec.size();
	uint32 bufferSize = mVertexCount * sizeof(Vertex);

	DEVICE->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(bufferSize),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&mVertexBuffer));

	void* mappedData;
	mVertexBuffer->Map(0, nullptr, &mappedData);
	::memcpy(mappedData, vec.data(), bufferSize);
	mVertexBuffer->Unmap(0, nullptr);

	mVertexBufferView.BufferLocation = mVertexBuffer->GetGPUVirtualAddress();
	mVertexBufferView.SizeInBytes = bufferSize;
	mVertexBufferView.StrideInBytes = sizeof(Vertex);
}

void Mesh::Render()
{
	CMD_LIST->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	CMD_LIST->IASetVertexBuffers(0, 1, &mVertexBufferView);
	CMD_LIST->DrawInstanced(mVertexCount, 1, 0, 0);
}
