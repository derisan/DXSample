#pragma once

#include "Object.h"

class Shader;
class Texture;

struct MaterialParams
{
	int32 bUseNormalMap;
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
	void SetUseNormalMap(int32 value) { mMaterialParams.bUseNormalMap = value; }

	void Render();

private:
	std::shared_ptr<Shader> mShader = nullptr;
	std::array<std::shared_ptr<Texture>, TEXTURE_COUNT> mTextures;

	MaterialParams mMaterialParams = {};
	uint32 mTextureCount = 0;

	UploadBuffer<MaterialParams> mUploadBuffer;
};

