#pragma once

class RootSignature
{
public:
	void Init(ComPtr<ID3D12Device> device);

	ComPtr<ID3D12RootSignature> GetRootSignature() const { return mRootSignature; }

private:
	ComPtr<ID3D12RootSignature> mRootSignature = nullptr;
};

