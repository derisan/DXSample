#include "CorePch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture.h"
#include "Shader.h"

void SceneManager::Update()
{
	if (mActiveScene == nullptr)
	{
		return;
	}

	mActiveScene->Update();
	mActiveScene->LateUpdate();
	mActiveScene->FinalUpdate();
}

void SceneManager::Render()
{
	if (mActiveScene == nullptr)
	{
		return;
	}

	mActiveScene->Render();
}

void SceneManager::LoadScene(const std::wstring& sceneName)
{
	mActiveScene = LoadTestScene();

	mActiveScene->Awake();
	mActiveScene->Start();
}

std::shared_ptr<Scene> SceneManager::LoadTestScene()
{
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


	std::shared_ptr<GameObject> obj = std::make_shared<GameObject>();
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

	std::shared_ptr<Scene> scene = std::make_shared<Scene>();

	scene->AddGameObject(obj);

	return scene;
}
