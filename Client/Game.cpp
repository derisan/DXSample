#include "pch.h"
#include "Game.h"
#include "Engine.h"

std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
std::shared_ptr<Shader> shader = std::make_shared<Shader>();
std::shared_ptr<Texture> texture = std::make_shared<Texture>();
std::shared_ptr<Material> material = std::make_shared<Material>();

void Game::Init(const WindowInfo& info)
{
	gEngine->Init(info);

	std::vector<Vertex> vertices(4);
	vertices[0].Position = vec3(-0.5f, -0.5f, 0.5f);
	vertices[0].UV = vec2(0.0f, 1.0f);
	vertices[1].Position = vec3(-0.5f, 0.5f, 0.5f);
	vertices[1].UV = vec2(0.0f, 0.0f);
	vertices[2].Position = vec3(0.5f, 0.5f, 0.5f);
	vertices[2].UV = vec2(1.0f, 0.0f);
	vertices[3].Position = vec3(0.5f, -0.5f, 0.5f);
	vertices[3].UV = vec2(1.0f, 1.0f);

	std::vector<uint32> indices;
	{
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);
	}
	{
		indices.push_back(0);
		indices.push_back(2);
		indices.push_back(3);
	}

	mesh->Init(vertices, indices);
	mesh->SetOffset(vec4(0.25f, -0.5f, 0.0f, 0.0f));
	shader->Init(L"..//Resources//Shaders//default.hlsli");
	texture->Init(L"..//Resources//Textures//veigar.jpg");
	material->Init(shader, texture);
	mesh->SetMaterial(material);
}

void Game::Run()
{
	gEngine->Update();

	gEngine->RenderBegin();

	static vec4 offset = {};


	if (INPUT->IsButtonHold(KEY_TYPE::W))
		offset.y += 1.f * DELTA_TIME;
	if (INPUT->IsButtonHold(KEY_TYPE::S))
		offset.y -= 1.f * DELTA_TIME;
	if (INPUT->IsButtonHold(KEY_TYPE::A))
		offset.x -= 1.f * DELTA_TIME;
	if (INPUT->IsButtonHold(KEY_TYPE::D))
		offset.x += 1.f * DELTA_TIME;

	mesh->SetOffset(offset);
	mesh->Render();

	gEngine->RenderEnd();
}
