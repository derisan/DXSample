#include "CorePch.h"
#include "Texture.h"
#include "Engine.h"

Texture::Texture()
	: Object(OBJECT_TYPE::TEXTURE)
{

}

void Texture::Init(const std::wstring& path)
{
	createTexture(path);
	createView();
}

void Texture::Render(int paramIdx)
{
	ID3D12DescriptorHeap* ppHeaps[] = { mSrvHeap.Get() };
	CMD_LIST->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
	CMD_LIST->SetGraphicsRootDescriptorTable(ROOT_PARAMS_DIFFUSE + paramIdx, mSrvHeap->GetGPUDescriptorHandleForHeapStart());
}

void Texture::Load(const std::wstring& path)
{
	Init(path);
}

void Texture::createTexture(const std::wstring& path)
{
	// 파일 확장자 얻기
	std::wstring ext = fs::path(path).extension();

	if (ext == L".dds" || ext == L".DDS")
		::LoadFromDDSFile(path.c_str(), DDS_FLAGS_NONE, nullptr, mRawImage);
	else if (ext == L".tga" || ext == L".TGA")
		::LoadFromTGAFile(path.c_str(), nullptr, mRawImage);
	else // png, jpg, jpeg, bmp
		::LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, nullptr, mRawImage);

	HRESULT hr = ::CreateTexture(DEVICE.Get(), mRawImage.GetMetadata(), &mTexture);
	if (FAILED(hr))
		assert(nullptr);

	std::vector<D3D12_SUBRESOURCE_DATA> subResources;

	hr = ::PrepareUpload(DEVICE.Get(),
		mRawImage.GetImages(),
		mRawImage.GetImageCount(),
		mRawImage.GetMetadata(),
		subResources);

	if (FAILED(hr))
		assert(nullptr);

	const uint64 bufferSize = ::GetRequiredIntermediateSize(mTexture.Get(), 0, static_cast<uint32>(subResources.size()));

	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

	ComPtr<ID3D12Resource> textureUploadHeap;
	hr = DEVICE->CreateCommittedResource(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(textureUploadHeap.GetAddressOf()));

	if (FAILED(hr))
		assert(nullptr);

	::UpdateSubresources(CMD_LIST.Get(),
		mTexture.Get(),
		textureUploadHeap.Get(),
		0, 0,
		static_cast<unsigned int>(subResources.size()),
		subResources.data());

	gEngine->GetCmdQueue()->FlushResCmdQueue();
}

void Texture::createView()
{
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
	heapDesc.NumDescriptors = 1;
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

	DEVICE->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&mSrvHeap));

	mSrvGpuHandle = mSrvHeap->GetGPUDescriptorHandleForHeapStart();

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = mRawImage.GetMetadata().format;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Texture2D.MipLevels = 1;

	DEVICE->CreateShaderResourceView(mTexture.Get(), &srvDesc, mSrvHeap->GetCPUDescriptorHandleForHeapStart());
}
