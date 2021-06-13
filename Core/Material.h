#pragma once

class Shader;
class Texture;

struct MaterialParams
{
	vec4 SomeValue;
};

class Material
{
public:
	void Init(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture);
	void Render();

private:
	std::shared_ptr<Shader> mShader = nullptr;
	std::shared_ptr<Texture> mTexture = nullptr;
};
