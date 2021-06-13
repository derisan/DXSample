#include "CorePch.h"
#include "Material.h"
#include "Shader.h"
#include "Texture.h"

void Material::Init(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture)
{
	mShader = std::move(shader);
	mTexture = std::move(texture);
}

void Material::Render()
{
	mShader->Render();
	mTexture->Render();
}

