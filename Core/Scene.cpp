#include "CorePch.h"
#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"

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
