#include "CorePch.h"
#include "RootSignature.h"

void RootSignature::Init(ComPtr<ID3D12Device> device)
{
	D3D12_DESCRIPTOR_RANGE diffuseRange[1];
	diffuseRange[0].BaseShaderRegister = 0;
	diffuseRange[0].NumDescriptors = 1;
	diffuseRange[0].OffsetInDescriptorsFromTableStart = 0;
	diffuseRange[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	diffuseRange[0].RegisterSpace = 0;

	CD3DX12_DESCRIPTOR_RANGE normalRange(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 1);
	
	CD3DX12_ROOT_PARAMETER params[RootParamIndex::END];
	params[RootParamIndex::ROOT_PARAM_WORLD].InitAsConstantBufferView(0);
	params[RootParamIndex::ROOT_PARAM_VIEWPROJ].InitAsConstantBufferView(1);
	params[RootParamIndex::ROOT_PARAM_LIGHT].InitAsConstantBufferView(2);
	params[RootParamIndex::ROOT_PARAM_MATERIAL].InitAsConstantBufferView(3);
	params[RootParamIndex::ROOT_PARAM_DIFFUSE].InitAsDescriptorTable(_countof(diffuseRange), diffuseRange, D3D12_SHADER_VISIBILITY_PIXEL);
	params[RootParamIndex::ROOT_PARAM_NORMAL].InitAsDescriptorTable(1, &normalRange, D3D12_SHADER_VISIBILITY_PIXEL);

	D3D12_ROOT_SIGNATURE_DESC sigDesc = CD3DX12_ROOT_SIGNATURE_DESC(_countof(params), params, 1,
		&CD3DX12_STATIC_SAMPLER_DESC(0), D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ComPtr<ID3DBlob> sigBlob = nullptr;
	ComPtr<ID3DBlob> errBlob = nullptr;
	::D3D12SerializeRootSignature(&sigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &sigBlob, &errBlob);

	device->CreateRootSignature(0, sigBlob->GetBufferPointer(), sigBlob->GetBufferSize(), IID_PPV_ARGS(&mRootSignature));
}
