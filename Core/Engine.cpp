#include "CorePch.h"
#include "Engine.h"

void Engine::Init(const WindowInfo& info)
{
	mWindow = info;
	ResizeWindow(info.Width, info.Height);

	mViewport = { 0.0f, 0.0f, static_cast<float>(info.Width), static_cast<float>(info.Height), 0.0f, 1.0f };
	mScissorRect = CD3DX12_RECT(0, 0, info.Width, info.Height);

	mDevice = std::make_shared<Device>();
	mCmdQueue = std::make_shared<CommandQueue>();
	mSwapChain = std::make_shared<SwapChain>();
	mDescHeap = std::make_shared<DescriptorHeap>();
	
	mDevice->Init();
	mCmdQueue->Init(mDevice->GetDevice(), mSwapChain, mDescHeap);
	mSwapChain->Init(info, mDevice->GetFactory(), mCmdQueue->GetCmdQueue());
	mDescHeap->Init(mDevice->GetDevice(), mSwapChain);
}

void Engine::Render()
{
	renderBegin();


	renderEnd();
}

void Engine::ResizeWindow(int32 width, int32 height)
{
	mWindow.Width = width;
	mWindow.Height = height;

	RECT rect = { 0, 0, width, height };
	::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	::SetWindowPos(mWindow.hWnd, 0, 100, 100, width, height, 0);
}

void Engine::renderBegin()
{
	mCmdQueue->RenderBegin(mViewport, mScissorRect);
}

void Engine::renderEnd()
{
	mCmdQueue->RenderEnd();
}
