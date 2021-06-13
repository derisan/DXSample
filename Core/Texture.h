#pragma once

class Texture
{
public:
	void Init(const std::wstring& path);
	void Render();

	inline D3D12_GPU_DESCRIPTOR_HANDLE GetSrvGpuHandle() { return mSrvGpuHandle; }
	inline ComPtr<ID3D12DescriptorHeap> GetSrvHeap() const { return mSrvHeap; }

private:
	void createTexture(const std::wstring& path);
	void createView();

private:
	ScratchImage mRawImage = {};
	ComPtr<ID3D12Resource> mTexture = nullptr;
	ComPtr<ID3D12DescriptorHeap> mSrvHeap = nullptr;
	D3D12_GPU_DESCRIPTOR_HANDLE mSrvGpuHandle;
};

