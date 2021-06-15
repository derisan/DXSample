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
#include "Light.h"

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
		std::shared_ptr<Texture> texture = GET_SINGLETON(ResourceManager)->Load<Texture>(L"Waffle", L"..\\Resources\\Textures\\Waffle.jpg");
		std::shared_ptr<Texture> tex2 = GET_SINGLETON(ResourceManager)->Load<Texture>(L"Waffle_Normal", L"..\\Resources\\Textures\\Waffle_Normal.jpg");
		shader->Init(L"..\\Resources\\Shaders\\default.hlsli");
		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture, TEXTURE_TYPE::DIFFUSE_MAP);
		material->SetTexture(tex2, TEXTURE_TYPE::NORMAL_MAP	);
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
		std::shared_ptr<Texture> texture = GET_SINGLETON(ResourceManager)->Load<Texture>(L"Waffle", L"..\\Resources\\Textures\\Waffle.jpg");
		std::shared_ptr<Texture> tex2 = GET_SINGLETON(ResourceManager)->Load<Texture>(L"Waffle_Normal", L"..\\Resources\\Textures\\Waffle_Normal.jpg");
		shader->Init(L"..\\Resources\\Shaders\\default.hlsli");
		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture, TEXTURE_TYPE::DIFFUSE_MAP);
		material->SetTexture(tex2, TEXTURE_TYPE::NORMAL_MAP);
		meshRenderer->SetMaterial(material);

		cube->AddComponent(meshRenderer);
		scene->AddGameObject(cube);
	}
#pragma endregion

#pragma region Directional Light
	{
		std::shared_ptr<GameObject> light = std::make_shared<GameObject>();
		light->AddComponent(std::make_shared<Transform>());
		light->AddComponent(std::make_shared<Light>());
		light->GetLight()->SetLightDirection(vec3(1.f, 0.f, 1.f));
		light->GetLight()->SetLightType(LIGHT_TYPE::DIRECTIONAL_LIGHT);
		light->GetLight()->SetDiffuse(vec3(1.0f, 1.0f, 1.0f));
		light->GetLight()->SetAmbient(vec3(0.1f, 0.1f, 0.1f));
		light->GetLight()->SetSpecular(vec3(0.3f, 0.3f, 0.3f));
		scene->AddGameObject(light);
	}
#pragma endregion


#pragma region Skybox
	std::shared_ptr<GameObject> skybox = std::make_shared<GameObject>();
	skybox->AddComponent(std::make_shared<Transform>());
	std::shared_ptr<MeshRenderer> meshRenderer = std::make_shared<MeshRenderer>();
	{
		std::shared_ptr<Mesh> sphereMesh = GET_SINGLETON(ResourceManager)->LoadSphereMesh();
		meshRenderer->SetMesh(sphereMesh);
	}
	{
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		shader->Init(L"..\\Resources\\Shaders\\skybox.hlsli",
				{ RASTERIZER_TYPE::CULL_NONE, DEPTH_STENCIL_TYPE::LESS_EQUAL });
		std::shared_ptr<Texture> tex = GET_SINGLETON(ResourceManager)->Load<Texture>(L"Skybox", L"..\\Resources\\Textures\\Sky01.jpg");
		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(tex, TEXTURE_TYPE::DIFFUSE_MAP);
		meshRenderer->SetMaterial(material);
	}
	skybox->AddComponent(meshRenderer);
	scene->AddGameObject(skybox);

#pragma endregion

		return scene;
}
