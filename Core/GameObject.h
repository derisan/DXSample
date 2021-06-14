#pragma once

#include "Component.h"
#include "Object.h"

class Transform;
class Camera;
class MonoBehaviour;

class GameObject : public Object, public std::enable_shared_from_this<GameObject>
{
public:
	GameObject();
	virtual ~GameObject() = default;

	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();
	void Render();

	std::shared_ptr<Transform> GetTransform();

	void AddComponent(std::shared_ptr<Component> component);

private:
	std::shared_ptr<Component> getComponentByType(COMPONENT_TYPE type);

private:
	std::array<std::shared_ptr<Component>, FIXED_COMPONENT_COUNT> mComponents;
	std::vector<std::shared_ptr<MonoBehaviour>> mScripts;
};
