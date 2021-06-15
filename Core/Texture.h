#pragma once

#include "Object.h"

class Texture : public Object
{
public:
	Texture();

	void Init(const std::wstring& path);
	void Render(int paramIdx);

	virtual void Load(const std::wstring& path) override;

private:
	void createTexture(const std::wstring& path);
	void createView();

private:
	ScratchImage mRawImage = {};
	ComPtr<ID3D12Resource> mTexture = nullptr;
	ComPtr<ID3D12DescriptorHeap> mSrvHeap = nullptr;
	D3D12_GPU_DESCRIPTOR_HANDLE mSrvGpuHandle = {};
};

