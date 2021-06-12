#include "pch.h"
#include "Game.h"
#include "Engine.h"

std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>();
std::unique_ptr<Mesh> mesh2 = std::make_unique<Mesh>();
std::unique_ptr<Shader> shader = std::make_unique<Shader>();
std::shared_ptr<Texture> texture = std::make_shared<Texture>();


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
	shader->Init(L"..//Resources//Shaders//default.hlsli");
	texture->Init(L"..//Resources//Textures//veigar.jpg");
	mesh->SetTexture(texture);
	mesh->SetOffset(vec4(0.25f, -0.5f, 0.0f, 0.0f));
	
	mesh2->Init(vertices, indices);
	mesh2->SetOffset(vec4(-0.25f, 0.0f, 0.2f, 0.0f));
	mesh2->SetTexture(texture);
}

void Game::Run()
{
	gEngine->RenderBegin();

	shader->Update();
	mesh->Render();
	mesh2->Render();

	gEngine->RenderEnd();
}
