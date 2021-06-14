#pragma once

#include "Device.h"
#include "CommandQueue.h"
#include "SwapChain.h"
#include "RootSignature.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"


class Engine
{
public:
	void Init(const WindowInfo& info);
	
	void Update();
	void Render();

	void ResizeWindow(int32 width, int32 height);

	std::shared_ptr<Device> GetDevice() { return mDevice; }
	std::shared_ptr<CommandQueue> GetCmdQueue() { return mCmdQueue; }
	std::shared_ptr<SwapChain> GetSwapChain() { return mSwapChain; }
	std::shared_ptr<RootSignature> GetRootSignature() { return mRootSignature; }

private:
	void renderBegin();
	void renderEnd();
	void showFPS();

private:
	WindowInfo mWindow = {};
	D3D12_VIEWPORT mViewport = {};
	D3D12_RECT mScissorRect = {};

	std::shared_ptr<Device> mDevice = nullptr;
	std::shared_ptr<CommandQueue> mCmdQueue = nullptr;
	std::shared_ptr<SwapChain> mSwapChain = nullptr;
	std::shared_ptr<RootSignature> mRootSignature = nullptr;
};

