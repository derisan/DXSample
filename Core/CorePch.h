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
#include "SimpleMath.h"
#include "SimpleMath.inl"
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
using vec2 = SimpleMath::Vector2;
using vec3 = SimpleMath::Vector3;
using vec4 = SimpleMath::Vector4;
using matrix = SimpleMath::Matrix;

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
	Vertex() {}

	Vertex(vec3 pos, vec2 uv, vec3 norm, vec3 tangent)
		: Position(pos), UV(uv), Normal(norm), Tangent(tangent) {}

	vec3 Position;
	vec2 UV;
	vec3 Normal;
	vec3 Tangent;
};

extern std::unique_ptr<class Engine> gEngine;

#define DECLARE_SINGLETON(type)		\
private:							\
	type() {};							\
public:								\
	type(const type&) = delete;		\
	static type* GetInstance()		\
	{								\
		static type instance;		\
		return &instance;			\
	}								\

#define GET_SINGLETON(type) type::GetInstance()

#define DEVICE gEngine->GetDevice()->GetDevice()
#define CMD_LIST gEngine->GetCmdQueue()->GetCmdList()
#define ROOT_SIGNATURE gEngine->GetRootSignature()->GetRootSignature()
#define INPUT GET_SINGLETON(Input)
#define TIMER GET_SINGLETON(Timer)
#define DELTA_TIME gEngine->GetTimer()->GetDeltaTime()

#define ASPECT_RATIO gEngine->GetAspectRatio()

#define ROOT_PARAMS_WORLD		0
#define ROOT_PARAMS_VIEWPROJ	1
#define ROOT_PARAMS_TEXTURE		2