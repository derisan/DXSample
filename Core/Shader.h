#pragma once

class Shader
{
public:
	void Init(const std::wstring& path);
	void Update();

private:
	
	ComPtr<ID3D12PipelineState> mPipelineState = nullptr;
};

