#include "CorePch.h"
#include "GameObject.h"
#include "Transform.h"
#include "MonoBehaviour.h"
#include "MeshRenderer.h"

void GameObject::Init()
{
	AddComponent(std::make_shared<Transform>());
}

void GameObject::Awake()
{
	for (auto& component : mComponents)
	{
		if (component)
		{
			component->Awake();
		}
	}

	for (auto& script : mScripts)
	{
		script->Awake();
	}
}

void GameObject::Start()
{
	for (auto& component : mComponents)
	{
		if (component)
		{
			component->Start();
		}
	}

	for (auto& script : mScripts)
	{
		script->Start();
	}
}

void GameObject::Update()
{
	for (auto& component : mComponents)
	{
		if (component)
		{
			component->Update();
		}
	}

	for (auto& script : mScripts)
	{
		script->Update();
	}
}

void GameObject::LateUpdate()
{
	for (auto& component : mComponents)
	{
		if (component)
		{
			component->LateUpdate();
		}
	}

	for (auto& script : mScripts)
	{
		script->LateUpdate();
	}
}

void GameObject::FinalUpdate()
{
	for (auto& component : mComponents)
	{
		if (component)
		{
			component->FinalUpdate();
		}
	}
}

void GameObject::Render()
{
	uint8 index = static_cast<uint8>(COMPONENT_TYPE::MESH_RENDERER);

	if (mComponents[index] != nullptr)
	{
		std::static_pointer_cast<MeshRenderer>(mComponents[index])->Render();
	}
}

std::shared_ptr<Transform> GameObject::GetTransform()
{
	uint8 index = static_cast<uint8>(COMPONENT_TYPE::TRANSFORM);
	return std::static_pointer_cast<Transform>(mComponents[index]);
}

void GameObject::AddComponent(std::shared_ptr<Component> component)
{
	component->SetOwner(shared_from_this());

	uint8 index = static_cast<uint8>(component->GetType());
	if (index < FIXED_COMPONENT_COUNT)
	{
		mComponents[index] = component;
	}
	else
	{
		mScripts.push_back(std::static_pointer_cast<MonoBehaviour>(component));
	}
}

