#pragma once

class Shader
{
public:
	void Init(const std::wstring& path);
	void Render();

private:
	
	ComPtr<ID3D12PipelineState> mPipelineState = nullptr;
};

