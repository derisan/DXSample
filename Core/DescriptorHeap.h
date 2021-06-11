#pragma once

class SwapChain;

class DescriptorHeap
{
public:
	void Init(ComPtr<ID3D12Device> device, std::shared_ptr<SwapChain> swapChain);

	D3D12_CPU_DESCRIPTOR_HANDLE GetRTV(uint32 idx) { return mRtvHandles[idx]; }
	D3D12_CPU_DESCRIPTOR_HANDLE GetBackBufferView();

private:
	ComPtr<ID3D12DescriptorHeap> mRtvHeap = nullptr;
	uint32 mRtvIncrementSize = 0;
	D3D12_CPU_DESCRIPTOR_HANDLE mRtvHandles[SWAP_CHAIN_BUFFER_COUNT];

	std::shared_ptr<SwapChain> mSwapChain = nullptr;
};

