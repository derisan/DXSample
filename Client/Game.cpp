#include "pch.h"
#include "Game.h"
#include "Engine.h"

std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>();
std::unique_ptr<Shader> shader = std::make_unique<Shader>();

void Game::Init(const WindowInfo& info)
{
	gEngine->Init(info);

	std::vector<Vertex> vertices(3);
	vertices[0].Position = vec3(0.f, 0.5f, 0.5f);
	vertices[0].Color = vec4(1.f, 0.f, 0.f, 1.f);
	vertices[1].Position = vec3(0.5f, -0.5f, 0.5f);
	vertices[1].Color = vec4(0.f, 1.0f, 0.f, 1.f);
	vertices[2].Position = vec3(-0.5f, -0.5f, 0.5f);
	vertices[2].Color = vec4(0.f, 0.f, 1.f, 1.f);

	mesh->Init(vertices);
	shader->Init(L"..//Resources//Shaders//default.hlsli");
}

void Game::Run()
{
	gEngine->RenderBegin();

	shader->Update();
	mesh->Render();

	gEngine->RenderEnd();
}
