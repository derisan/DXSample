#include "pch.h"
#include "Game.h"
#include "Engine.h"

#include "GameObject.h"
#include "MeshRenderer.h"

std::shared_ptr<GameObject> obj = std::make_shared<GameObject>();

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

	obj->Init();

	std::shared_ptr<MeshRenderer> meshRenderer = std::make_shared<MeshRenderer>();
	{
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		mesh->Init(vertices, indices);
		meshRenderer->SetMesh(mesh);
	}

	{
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		std::shared_ptr<Texture> texture = std::make_shared<Texture>();
		shader->Init(L"..\\Resources\\Shaders\\default.hlsli");
		texture->Init(L"..\\Resources\\Textures\\veigar.jpg");
		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->Init(shader, texture);
		meshRenderer->SetMaterial(material);
	}

	obj->AddComponent(meshRenderer);
}

void Game::Run()
{
	gEngine->Update();

	gEngine->RenderBegin();

	obj->Update();

	gEngine->RenderEnd();
}
