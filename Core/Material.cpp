#include "CorePch.h"
#include "Material.h"
#include "Shader.h"
#include "Texture.h"

Material::Material()
	: Object(OBJECT_TYPE::MATERIAL)
{

}



void Material::SetTexture(std::shared_ptr<Texture> texture, TEXTURE_TYPE type)
{
	uint8 idx = static_cast<uint8>(type);
	mTextures[idx] = texture;
	mTextureCount++;
}

void Material::Render()
{
	mShader->Render();

	for (int i = 0; i < mTextureCount; i++)
	{
		mTextures[i]->Render(i);
	}
}

