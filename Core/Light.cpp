#include "CorePch.h"
#include "Light.h"
#include "Transform.h"

Light::Light()
	: Component(COMPONENT_TYPE::LIGHT)
{

}

Light::~Light()
{

}

void Light::FinalUpdate()
{
	mLightInfo.Position = GetTransform()->GetWorldPosition();
}
