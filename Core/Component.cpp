#include "CorePch.h"
#include "Component.h"
#include "GameObject.h"
#include "Transform.h"

Component::Component(COMPONENT_TYPE type)
	: mType(type)
{

}

std::shared_ptr<GameObject> Component::GetOwner()
{
	return mOwner.lock();
}

std::shared_ptr<Transform> Component::GetTransform()
{
	return mOwner.lock()->GetTransform();
}
