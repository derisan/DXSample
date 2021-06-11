#include "CorePch.h"
#include "CommandQueue.h"
#include "Engine.h"

CommandQueue::~CommandQueue()
{
	::CloseHandle(mFenceEvent);
}

void CommandQueue::Init(ComPtr<ID3D12Device> device, std::shared_ptr<SwapChain> swapChain)
{
	mSwapChain = swapChain;

	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

	HRESULT hr = device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&mCmdQueue));
	
	device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&mCmdAlloc));
	device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, mCmdAlloc.Get(), nullptr, IID_PPV_ARGS(&mCmdList));
	
	device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&mFence));
	mFenceEvent = ::CreateEvent(nullptr, false, false, nullptr);
}

void CommandQueue::FlushResCmdQueue()
{
	mCmdList->Close();

	ID3D12CommandList* cmdLists[] = { mCmdList.Get() };
	mCmdQueue->ExecuteCommandLists(_countof(cmdLists), cmdLists);

	WaitSync();
}

void CommandQueue::WaitSync()
{
	mFenceValue++;

	mCmdQueue->Signal(mFence.Get(), mFenceValue);

	if (mFence->GetCompletedValue() < mFenceValue)
	{
		mFence->SetEventOnCompletion(mFenceValue, mFenceEvent);
		::WaitForSingleObject(mFenceEvent, INFINITE);
	}
}

void CommandQueue::RenderBegin(const D3D12_VIEWPORT& viewport, const D3D12_RECT& scissorRect)
{
	mCmdAlloc->Reset();
	mCmdList->Reset(mCmdAlloc.Get(), nullptr);

	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		mSwapChain->GetCurrentBackBuffer().Get(),
		D3D12_RESOURCE_STATE_PRESENT,
		D3D12_RESOURCE_STATE_RENDER_TARGET); 

	mCmdList->ResourceBarrier(1, &barrier);

	mCmdList->SetGraphicsRootSignature(ROOT_SIGNATURE.Get());
	mCmdList->RSSetViewports(1, &viewport);
	mCmdList->RSSetScissorRects(1, &scissorRect);

	D3D12_CPU_DESCRIPTOR_HANDLE backBufferView = mSwapChain->GetCurrentBackBufferView();
	mCmdList->ClearRenderTargetView(backBufferView, Colors::LightCyan, 0, nullptr);
	mCmdList->OMSetRenderTargets(1, &backBufferView, false, nullptr);
}

void CommandQueue::RenderEnd()
{
	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		mSwapChain->GetCurrentBackBuffer().Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET,
		D3D12_RESOURCE_STATE_PRESENT);

	mCmdList->ResourceBarrier(1, &barrier);
	mCmdList->Close();

	ID3D12CommandList* cmdLists[] = { mCmdList.Get() };
	mCmdQueue->ExecuteCommandLists(_countof(cmdLists), cmdLists);

	mSwapChain->Present();

	WaitSync();

	mSwapChain->SwapIndex();
}