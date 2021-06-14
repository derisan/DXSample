#include "CorePch.h"
#include "Shader.h"
#include "Engine.h"

Shader::Shader()
	: Object(OBJECT_TYPE::SHADER)
{

}

void Shader::Init(const std::wstring& path)
{
	uint32 compileFlag = 0;
#ifdef _DEBUG
	compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ComPtr<ID3DBlob> vsBlob;
	ComPtr<ID3DBlob> errBlob;

	if (FAILED(::D3DCompileFromFile(path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS_Main",
		"vs_5_0", compileFlag, 0, &vsBlob, &errBlob)))
	{
		::MessageBoxA(nullptr, "Vertex Shader Create Failed !", nullptr, MB_OK);
	}

	ComPtr<ID3DBlob> psBlob;
	if (FAILED(::D3DCompileFromFile(path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS_Main",
		"ps_5_0", compileFlag, 0, &psBlob, &errBlob)))
	{
		::MessageBoxA(nullptr, "Pixel Shader Create Failed !", nullptr, MB_OK);
	}

	D3D12_INPUT_ELEMENT_DESC desc[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		{"TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	};

	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
	psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	psoDesc.SampleMask = UINT_MAX;
	psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDesc.NumRenderTargets = 1;
	psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	psoDesc.SampleDesc.Count = 1;
	psoDesc.DSVFormat = gEngine->GetSwapChain()->GetDepthStencilFormat();
	psoDesc.VS = { vsBlob->GetBufferPointer(), vsBlob->GetBufferSize() };
	psoDesc.PS = { psBlob->GetBufferPointer(), psBlob->GetBufferSize() };
	psoDesc.InputLayout = { desc, _countof(desc) };
	psoDesc.pRootSignature = ROOT_SIGNATURE.Get();

	DEVICE->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&mPipelineState));
}

void Shader::Render()
{
	CMD_LIST->SetPipelineState(mPipelineState.Get());
}
