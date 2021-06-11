#pragma once

class SwapChain;
class DescriptorHeap;

class CommandQueue
{
public:
	~CommandQueue();

	void Init(ComPtr<ID3D12Device> device, std::shared_ptr<SwapChain> swapChain);
	void FlushResCmdQueue();
	void WaitSync();

	void RenderBegin(const D3D12_VIEWPORT& viewport, const D3D12_RECT& scissorRect);
	void RenderEnd();

	ComPtr<ID3D12CommandQueue> GetCmdQueue() const { return mCmdQueue; }
	ComPtr<ID3D12GraphicsCommandList> GetCmdList() const { return mCmdList; }

private:
	ComPtr<ID3D12CommandQueue> mCmdQueue = nullptr;
	ComPtr<ID3D12CommandAllocator> mCmdAlloc = nullptr;
	ComPtr<ID3D12GraphicsCommandList> mCmdList = nullptr;
	ComPtr<ID3D12Fence> mFence = nullptr;

	uint64 mFenceValue = 0;
	HANDLE mFenceEvent = INVALID_HANDLE_VALUE;

	std::shared_ptr<SwapChain> mSwapChain = nullptr;
};

