#pragma once

#include "Component.h"

class Transform;
class MonoBehaviour;

class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;

	void Init();

	void Awake();
	void Start();
	void Update();
	void LateUpdate();

	std::shared_ptr<Transform> GetTransform();

	void AddComponent(std::shared_ptr<Component> component);

private:
	std::array<std::shared_ptr<Component>, FIXED_COMPONENT_COUNT> mComponents;
	std::vector<std::shared_ptr<MonoBehaviour>> mScripts;
};
