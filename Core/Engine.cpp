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
	mRootSignature = std::make_shared<RootSignature>();
	
	mDevice->Init();
	mCmdQueue->Init(mDevice->GetDevice(), mSwapChain);
	mSwapChain->Init(info, mDevice->GetDevice(), mDevice->GetFactory(), mCmdQueue->GetCmdQueue());
	mRootSignature->Init(mDevice->GetDevice());

	mTimer->Init();
	mInput->Init(info.hWnd);
}

void Engine::ResizeWindow(int32 width, int32 height)
{
	mWindow.Width = width;
	mWindow.Height = height;

	RECT rect = { 0, 0, width, height };
	::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	::SetWindowPos(mWindow.hWnd, 0, 100, 100, width, height, 0);
}

void Engine::showFPS()
{
	uint32 fps = mTimer->GetFPS();

	WCHAR text[100] = L"";
	::wsprintf(text, L"FPS : %d", fps);
	::SetWindowText(mWindow.hWnd, text);
}

void Engine::RenderBegin()
{
	mCmdQueue->RenderBegin(mViewport, mScissorRect);
}

void Engine::RenderEnd()
{
	mCmdQueue->RenderEnd();
}

void Engine::Update()
{
	mInput->Update();
	mTimer->Update();

	showFPS();
}
