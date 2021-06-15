#pragma once

#include "Object.h"

enum class RASTERIZER_TYPE
{
	CULL_NONE,
	CULL_FRONT,
	CULL_BACK,
	WIREFRAME
};

enum class DEPTH_STENCIL_TYPE
{
	LESS,
	LESS_EQUAL,
	GREATER,
	GREATER_EQUAL
};

struct ShaderInfo
{
	RASTERIZER_TYPE rsType = RASTERIZER_TYPE::CULL_BACK;
	DEPTH_STENCIL_TYPE dsType = DEPTH_STENCIL_TYPE::LESS;
};

class Shader : public Object
{
public:
	Shader();

	void Init(const std::wstring& path, const ShaderInfo& info = ShaderInfo());
	void Render();

private:
	
	ComPtr<ID3D12PipelineState> mPipelineState = nullptr;
};

