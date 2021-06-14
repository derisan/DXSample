#include "CorePch.h"
#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
#include "Engine.h"

Scene::Scene()
	: mLightCb(DEVICE.Get(), 1, true)
{

}

void Scene::Awake()
{
	for(const auto& obj : mGameObjects)
	{
		obj->Awake();
	}
}

void Scene::Start()
{
	for (const auto& obj : mGameObjects)
	{
		obj->Start();
	}
}

void Scene::Update()
{
	for (const auto& obj : mGameObjects)
	{
		obj->Update();
	}
}

void Scene::LateUpdate()
{
	for (const auto& obj : mGameObjects)
	{
		obj->LateUpdate();
	}
}

void Scene::FinalUpdate()
{
	for (const auto& obj : mGameObjects)
	{
		obj->FinalUpdate();
	}
}

void Scene::Render()
{
	setLightData();

	for (const auto& obj : mGameObjects)
	{
		auto& camera = obj->GetCamera();

		if (camera == nullptr)
		{
			continue;
		}

		camera->Render();
	}
}

void Scene::AddGameObject(std::shared_ptr<GameObject> obj)
{
	mGameObjects.push_back(std::move(obj));
}

void Scene::RemoveGameObject(std::shared_ptr<GameObject> obj)
{
	auto iter = std::find(mGameObjects.begin(), mGameObjects.end(), obj);
	if (iter != mGameObjects.end())
	{
		std::iter_swap(iter, mGameObjects.end() - 1);
		mGameObjects.pop_back();
	}
}

void Scene::setLightData()
{
	LightParams lightParams = {};

	for (auto& obj : mGameObjects)
	{
		auto light = obj->GetLight();

		if (light == nullptr)
		{
			continue;
		}

		lightParams.Lights[lightParams.LightCount++] = light->GetLightInfo();
	}

	mLightCb.CopyData(0, lightParams);

	CMD_LIST->SetGraphicsRootConstantBufferView(ROOT_PARAMS_LIGHT, mLightCb.Resource()->GetGPUVirtualAddress());
}
