#pragma once

class SwapChain
{
public:
	void Init(const WindowInfo& info, ComPtr<IDXGIFactory> factory, ComPtr<ID3D12CommandQueue> cmdQueue);
	void Present();
	void SwapIndex();

	ComPtr<IDXGISwapChain> GetSwapChain() const { return mSwapChain; };
	ComPtr<ID3D12Resource> GetRenderTarget(uint32 idx) const { return mRenderTargets[idx]; }
	ComPtr<ID3D12Resource> GetCurrentBackBufferResource() const { return mRenderTargets[mBackBufferIndex]; }
	uint32 GetCurrentBackBufferIndex() const { return mBackBufferIndex; }

private:
	ComPtr<IDXGISwapChain> mSwapChain = nullptr;
	ComPtr<ID3D12Resource> mRenderTargets[SWAP_CHAIN_BUFFER_COUNT];
	uint32 mBackBufferIndex = 0;
};

