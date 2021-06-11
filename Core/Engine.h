#pragma once

#include "Device.h"
#include "CommandQueue.h"
#include "DescriptorHeap.h"
#include "SwapChain.h"

class Engine
{
public:
	void Init(const WindowInfo& info);
	void Render();
	void ResizeWindow(int32 width, int32 height);

private:
	void renderBegin();
	void renderEnd();

private:
	WindowInfo mWindow = {};
	D3D12_VIEWPORT mViewport = {};
	D3D12_RECT mScissorRect = {};

	std::shared_ptr<Device> mDevice = nullptr;
	std::shared_ptr<CommandQueue> mCmdQueue = nullptr;
	std::shared_ptr<SwapChain> mSwapChain = nullptr;
	std::shared_ptr<DescriptorHeap> mDescHeap = nullptr;
};

