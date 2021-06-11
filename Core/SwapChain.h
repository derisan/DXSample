#pragma once

class SwapChain
{
public:
	void Init(const WindowInfo& info, ComPtr<ID3D12Device> device, ComPtr<IDXGIFactory> factory, ComPtr<ID3D12CommandQueue> cmdQueue);
	void Present();
	void SwapIndex();

	ComPtr<IDXGISwapChain> GetSwapChain() const { return mSwapChain; };
	ComPtr<ID3D12Resource> GetCurrentBackBuffer() const { return mRenderTargets[mBackBufferIndex]; }
	D3D12_CPU_DESCRIPTOR_HANDLE GetCurrentBackBufferView() const { return mRtvHandles[mBackBufferIndex]; }
	
private:
	void createSwapChain(const WindowInfo& info, ComPtr<IDXGIFactory> factory, ComPtr<ID3D12CommandQueue> cmdQueue);
	void createRTV(ComPtr<ID3D12Device> device);

private:
	ComPtr<IDXGISwapChain> mSwapChain = nullptr;
	ComPtr<ID3D12Resource> mRenderTargets[SWAP_CHAIN_BUFFER_COUNT];
	uint32 mBackBufferIndex = 0;

	ComPtr<ID3D12DescriptorHeap> mRtvHeap = nullptr;
	uint32 mRtvIncrementSize = 0;
	D3D12_CPU_DESCRIPTOR_HANDLE mRtvHandles[SWAP_CHAIN_BUFFER_COUNT];
};

