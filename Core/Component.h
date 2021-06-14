#pragma once

class GameObject;
class Transform;

enum class COMPONENT_TYPE : uint8
{
	TRANSFORM,
	MESH_RENDERER,
	MONO_BEHAVIOUR,
	END
};

enum
{
	FIXED_COMPONENT_COUNT = static_cast<uint8>(COMPONENT_TYPE::END) - 1
};

class Component
{
public:
	Component(COMPONENT_TYPE type);
	virtual ~Component() = default;

	virtual void Awake() {};
	virtual void Start() {};
	virtual void Update() {};
	virtual void LateUpdate() {};
	virtual void FinalUpdate() {};

	COMPONENT_TYPE GetType() const { return mType; }
	bool IsValid() const { return mOwner.expired() == false; }

protected:
	std::shared_ptr<GameObject> GetOwner();
	std::shared_ptr<Transform> GetTransform();

private:
	friend class GameObject;
	void SetOwner(std::shared_ptr<GameObject> owner) { mOwner = owner; }

private:
	COMPONENT_TYPE mType;
	std::weak_ptr<GameObject> mOwner;
};

