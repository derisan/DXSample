#include "CorePch.h"
#include "SwapChain.h"

void SwapChain::Init(const WindowInfo& info, ComPtr<ID3D12Device> device, ComPtr<IDXGIFactory> factory, ComPtr<ID3D12CommandQueue> cmdQueue)
{
	createSwapChain(info, factory, cmdQueue);
	createRTV(device);
}

void SwapChain::Present()
{
	mSwapChain->Present(0, 0);
}

void SwapChain::SwapIndex()
{
	mBackBufferIndex = (mBackBufferIndex + 1) % SWAP_CHAIN_BUFFER_COUNT;
}

void SwapChain::createSwapChain(const WindowInfo& info, ComPtr<IDXGIFactory> factory, ComPtr<ID3D12CommandQueue> cmdQueue)
{
	mSwapChain.Reset();

	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = static_cast<uint32>(info.Width);
	sd.BufferDesc.Height = static_cast<uint32>(info.Height);
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = SWAP_CHAIN_BUFFER_COUNT;
	sd.OutputWindow = info.hWnd;
	sd.Windowed = info.bWindowed;
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	factory->CreateSwapChain(cmdQueue.Get(), &sd, &mSwapChain);

	for (int i = 0; i < SWAP_CHAIN_BUFFER_COUNT; i++)
	{
		mSwapChain->GetBuffer(i, IID_PPV_ARGS(&mRenderTargets[i]));
	}
}

void SwapChain::createRTV(ComPtr<ID3D12Device> device)
{
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
		device->CreateRenderTargetView(mRenderTargets[i].Get(), nullptr, mRtvHandles[i]);
	}
}
