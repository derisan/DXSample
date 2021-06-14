#include "CorePch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"
#include "Transform.h"
#include "TestCameraScript.h"
#include "ResourceManager.h"

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
	std::shared_ptr<Scene> scene = std::make_shared<Scene>();

#pragma region Camera
	{
		std::shared_ptr<GameObject> camera = std::make_shared<GameObject>();
		camera->AddComponent(std::make_shared<Transform>());
		camera->AddComponent(std::make_shared<Camera>());
		camera->AddComponent(std::make_shared<TestCameraScript>());
		camera->GetTransform()->SetLocalPosition(vec3(0.0f, 0.0f, -5.0f));
		scene->AddGameObject(camera);
	}
#pragma endregion

#pragma region Sphere
	{
		std::shared_ptr<GameObject> sphere = std::make_shared<GameObject>();
		sphere->AddComponent(std::make_shared<Transform>());
		
		std::shared_ptr<MeshRenderer> meshRenderer = std::make_shared<MeshRenderer>();
		std::shared_ptr<Mesh> sphereMesh = GET_SINGLETON(ResourceManager)->LoadSphereMesh();
		meshRenderer->SetMesh(sphereMesh);
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		std::shared_ptr<Texture> texture = std::make_shared<Texture>();
		shader->Init(L"..\\Resources\\Shaders\\default.hlsli");
		texture->Init(L"..\\Resources\\Textures\\veigar.jpg");
		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->Init(shader, texture);
		meshRenderer->SetMaterial(material);

		sphere->AddComponent(meshRenderer);
		scene->AddGameObject(sphere);
	}
#pragma endregion

#pragma region Cube
	{
		std::shared_ptr<GameObject> cube = std::make_shared<GameObject>();
		cube->AddComponent(std::make_shared<Transform>());
		cube->GetTransform()->SetLocalPosition(vec3(2.0f, 0.0f, 0.0f));
		
		std::shared_ptr<MeshRenderer> meshRenderer = std::make_shared<MeshRenderer>();
		std::shared_ptr<Mesh> cubeMesh = GET_SINGLETON(ResourceManager)->LoadCubeMesh();
		meshRenderer->SetMesh(cubeMesh);
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		std::shared_ptr<Texture> texture = std::make_shared<Texture>();
		shader->Init(L"..\\Resources\\Shaders\\default.hlsli");
		texture->Init(L"..\\Resources\\Textures\\veigar.jpg");
		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->Init(shader, texture);
		meshRenderer->SetMaterial(material);

		cube->AddComponent(meshRenderer);
		scene->AddGameObject(cube);
	}
#pragma endregion

		return scene;
}
