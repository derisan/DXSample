#include "CorePch.h"
#include "DescriptorHeap.h"
#include "SwapChain.h"

void DescriptorHeap::Init(ComPtr<ID3D12Device> device, std::shared_ptr<SwapChain> swapChain)
{
	mSwapChain = swapChain;
	mRtvIncrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	D3D12_DESCRIPTOR_HEAP_DESC heapDesc;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	heapDesc.NodeMask = 0;
	heapDesc.NumDescriptors = SWAP_CHAIN_BUFFER_COUNT;
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;

	device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&mRtvHeap));

	D3D12_CPU_DESCRIPTOR_HANDLE rtvHeapStart = mRtvHeap->GetCPUDescriptorHandleForHeapStart();
	for (int i = 0; i < SWAP_CHAIN_BUFFER_COUNT; i++)
	{
		mRtvHandles[i] = CD3DX12_CPU_DESCRIPTOR_HANDLE(rtvHeapStart, i * mRtvIncrementSize);
		device->CreateRenderTargetView(mSwapChain->GetRenderTarget(i).Get(), nullptr, mRtvHandles[i]);
	}
}

D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeap::GetBackBufferView()
{
	return GetRTV(mSwapChain->GetCurrentBackBufferIndex());
}
