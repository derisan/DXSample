#include "CorePch.h"
#include "Mesh.h"
#include "Engine.h"


void Mesh::Init(const std::vector<Vertex>& vertices, const std::vector<uint32>& indices)
{
	mVertexCount = vertices.size();
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
	::memcpy(mappedData, vertices.data(), bufferSize);
	mVertexBuffer->Unmap(0, nullptr);

	mVertexBufferView.BufferLocation = mVertexBuffer->GetGPUVirtualAddress();
	mVertexBufferView.SizeInBytes = bufferSize;
	mVertexBufferView.StrideInBytes = sizeof(Vertex);

	mIndexCount = indices.size();
	bufferSize = sizeof(uint32) * mIndexCount;

	DEVICE->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(bufferSize),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr, IID_PPV_ARGS(&mIndexBuffer));

	mIndexBuffer->Map(0, nullptr, &mappedData);
	::memcpy(mappedData, indices.data(), bufferSize);
	mIndexBuffer->Unmap(0, nullptr);

	mIndexBufferView.BufferLocation = mIndexBuffer->GetGPUVirtualAddress();
	mIndexBufferView.Format = DXGI_FORMAT_R32_UINT;
	mIndexBufferView.SizeInBytes = bufferSize;
}

void Mesh::Render()
{
	CMD_LIST->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	CMD_LIST->IASetVertexBuffers(0, 1, &mVertexBufferView);
	CMD_LIST->IASetIndexBuffer(&mIndexBufferView);

	CMD_LIST->SetGraphicsRoot32BitConstants(0, 4, &mOffset, 0);

	ID3D12DescriptorHeap* ppHeaps[] = { mTexture->GetSrvHeap().Get() };
	CMD_LIST->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
	CMD_LIST->SetGraphicsRootDescriptorTable(1, mTexture->GetSrvGpuHandle());

	CMD_LIST->DrawIndexedInstanced(mIndexCount, 1, 0, 0, 0);
}
