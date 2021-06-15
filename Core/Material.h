#pragma once

#include "Object.h"

class Shader;
class Texture;

struct MaterialParams
{
	vec4 SomeValue;
};

enum class TEXTURE_TYPE : uint8
{
	DIFFUSE_MAP,
	NORMAL_MAP,

	END
};

enum
{
	TEXTURE_COUNT = static_cast<uint8>(TEXTURE_TYPE::END)
};

class Material : public Object
{
public:
	Material();

	void SetShader(std::shared_ptr<Shader> shader) { mShader = std::move(shader); }
	void SetTexture(std::shared_ptr<Texture> texture, TEXTURE_TYPE type);

	void Render();

private:
	std::shared_ptr<Shader> mShader = nullptr;
	std::array<std::shared_ptr<Texture>, TEXTURE_COUNT> mTextures;

	uint32 mTextureCount = 0;
};

