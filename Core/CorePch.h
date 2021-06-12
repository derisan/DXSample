#pragma once

#include <windows.h>
#include <tchar.h>
#include <memory>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <map>
#include <filesystem>
namespace fs = std::filesystem;


#include "d3dx12.h"
#include "DirectXTex/DirectXTex.h"
#include "DirectXTex/DirectXTex.inl"
#include <d3d12.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
using namespace DirectX;
using namespace DirectX::PackedVector;
using namespace Microsoft::WRL;


#pragma comment(lib, "d3d12")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "d3dcompiler")

#ifdef _DEBUG
	#pragma comment(lib, "DirectXTexd.lib")
#else
	#pragma comment(lib, "DirectXTex.lib")
#endif


using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;
using vec2 = XMFLOAT2;
using vec3 = XMFLOAT3;
using vec4 = XMFLOAT4;
using matrix = XMFLOAT4X4;

enum
{
	SWAP_CHAIN_BUFFER_COUNT = 2
};

struct WindowInfo
{
	HWND	hWnd; 
	int32	Width; 
	int32	Height;
	bool	bWindowed; 
};

struct Vertex
{
	vec3 Position;
	vec2 UV;
};

extern std::unique_ptr<class Engine> gEngine;

#define DEVICE gEngine->GetDevice()->GetDevice()
#define CMD_LIST gEngine->GetCmdQueue()->GetCmdList()
#define ROOT_SIGNATURE gEngine->GetRootSignature()->GetRootSignature()
#define INPUT gEngine->GetInput()
#define DELTA_TIME gEngine->GetTimer()->GetDeltaTime()