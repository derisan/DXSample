#include "CorePch.h"
#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include "Engine.h"

Material::Material()
	: Object(OBJECT_TYPE::MATERIAL)
	, mUploadBuffer(DEVICE.Get(), 1, true)
{

}


void Material::SetTexture(std::shared_ptr<Texture> texture, TEXTURE_TYPE type)
{
	uint8 idx = static_cast<uint8>(type);
	mTextures[idx] = texture;
	mTextureCount++;

	if (mTextureCount == 2)
	{
		SetUseNormalMap(1);
	}

	mUploadBuffer.CopyData(0, mMaterialParams);
}

void Material::Render()
{
	CMD_LIST->SetGraphicsRootConstantBufferView(RootParamIndex::ROOT_PARAM_MATERIAL, mUploadBuffer.Resource()->GetGPUVirtualAddress());

	mShader->Render();

	for (int i = 0; i < mTextureCount; i++)
	{
		mTextures[i]->Render(i);
	}
}

