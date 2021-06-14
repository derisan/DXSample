#pragma once

#include "Object.h"

class Shader : public Object
{
public:
	Shader();

	void Init(const std::wstring& path);
	void Render();

private:
	
	ComPtr<ID3D12PipelineState> mPipelineState = nullptr;
};

