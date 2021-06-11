#pragma once

class Device
{
public:
	void Init();

	ComPtr<IDXGIFactory> GetFactory() const { return mFactory; }
	ComPtr<ID3D12Device> GetDevice() const { return mDevice; }

private:
	ComPtr<IDXGIFactory> mFactory = nullptr;
	ComPtr<ID3D12Device> mDevice = nullptr;
};

