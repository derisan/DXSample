#include "CorePch.h"
#include "Device.h"

void Device::Init()
{
#ifdef _DEBUG
	ComPtr<ID3D12Debug> debugger;
	::D3D12GetDebugInterface(IID_PPV_ARGS(&debugger));
	debugger->EnableDebugLayer();
#endif

	::CreateDXGIFactory(IID_PPV_ARGS(&mFactory));
	::D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&mDevice));
}
