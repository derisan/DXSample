#include "CorePch.h"
#include "GameObject.h"
#include "Transform.h"
#include "MonoBehaviour.h"
#include "MeshRenderer.h"
#include "Camera.h"

GameObject::GameObject()
	: Object(OBJECT_TYPE::GAMEOBJECT)
{

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

std::shared_ptr<Component> GameObject::getComponentByType(COMPONENT_TYPE type)
{
	uint8 index = static_cast<uint8>(type);
	return mComponents[index];
}

std::shared_ptr<Transform> GameObject::GetTransform()
{
	return std::static_pointer_cast<Transform>(getComponentByType(COMPONENT_TYPE::TRANSFORM));
}

std::shared_ptr<Camera> GameObject::GetCamera()
{
	return std::static_pointer_cast<Camera>(getComponentByType(COMPONENT_TYPE::CAMERA));
}

std::shared_ptr<MeshRenderer> GameObject::GetMeshRenderer()
{
	return std::static_pointer_cast<MeshRenderer>(getComponentByType(COMPONENT_TYPE::MESH_RENDERER));
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
