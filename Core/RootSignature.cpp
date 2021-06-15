#include "CorePch.h"
#include "RootSignature.h"

void RootSignature::Init(ComPtr<ID3D12Device> device)
{
	D3D12_DESCRIPTOR_RANGE ranges[1];
	ranges[0].BaseShaderRegister = 0;
	ranges[0].NumDescriptors = 1;
	ranges[0].OffsetInDescriptorsFromTableStart = 0;
	ranges[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	ranges[0].RegisterSpace = 0;
	
	CD3DX12_ROOT_PARAMETER params[4];
	params[ROOT_PARAMS_WORLD].InitAsConstantBufferView(0);
	params[ROOT_PARAMS_VIEWPROJ].InitAsConstantBufferView(1);
	params[ROOT_PARAMS_LIGHT].InitAsConstantBufferView(2);
	params[ROOT_PARAMS_DIFFUSE].InitAsDescriptorTable(_countof(ranges), ranges, D3D12_SHADER_VISIBILITY_PIXEL);

	D3D12_ROOT_SIGNATURE_DESC sigDesc = CD3DX12_ROOT_SIGNATURE_DESC(_countof(params), params, 1,
		&CD3DX12_STATIC_SAMPLER_DESC(0), D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ComPtr<ID3DBlob> sigBlob = nullptr;
	ComPtr<ID3DBlob> errBlob = nullptr;
	::D3D12SerializeRootSignature(&sigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &sigBlob, &errBlob);

	device->CreateRootSignature(0, sigBlob->GetBufferPointer(), sigBlob->GetBufferSize(), IID_PPV_ARGS(&mRootSignature));
}
