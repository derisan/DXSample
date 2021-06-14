#include "CorePch.h"
#include "TestCameraScript.h"
#include "Transform.h"
#include "Camera.h"
#include "GameObject.h"
#include "Input.h"
#include "Timer.h"


TestCameraScript::TestCameraScript()
	: MonoBehaviour()
{

}

TestCameraScript::~TestCameraScript()
{

}

void TestCameraScript::Update()
{
	vec3 pos = GetTransform()->GetLocalPosition();

	float deltaTime = TIMER->GetDeltaTime();

	if (INPUT->IsButtonHold(KEY_TYPE::W))
		pos += GetTransform()->GetForward() * mSpeed * deltaTime;

	if (INPUT->IsButtonHold(KEY_TYPE::S))
		pos -= GetTransform()->GetForward() * mSpeed * deltaTime;

	if (INPUT->IsButtonHold(KEY_TYPE::A))
		pos -= GetTransform()->GetRight() * mSpeed * deltaTime;

	if (INPUT->IsButtonHold(KEY_TYPE::D))
		pos += GetTransform()->GetRight() * mSpeed * deltaTime;

	if (INPUT->IsButtonHold(KEY_TYPE::Q))
	{
		vec3 rotation = GetTransform()->GetLocalRotation();
		rotation.x += deltaTime * 30.0f;
		GetTransform()->SetLocalRotation(rotation);
	}

	if (INPUT->IsButtonHold(KEY_TYPE::E))
	{
		vec3 rotation = GetTransform()->GetLocalRotation();
		rotation.x -= deltaTime * 30.0f;
		GetTransform()->SetLocalRotation(rotation);
	}

	GetTransform()->SetLocalPosition(pos);
}