#include "CorePch.h"
#include "Camera.h"
#include "Transform.h"
#include "Engine.h"

matrix Camera::sViewMatrix;
matrix Camera::sProjectionMatrix;

Camera::Camera()
	: Component(COMPONENT_TYPE::CAMERA)
{

}

Camera::~Camera()
{

}

void Camera::FinalUpdate()
{
	matrix viewMatrix = {};
	matrix projectionMatrix = {};

	switch (mType)
	{
	case PROJECTION_TYPE::PERSPECTIVE:
		viewMatrix = GetTransform()->GetLocalToWorldMatrix().Invert();
		projectionMatrix = XMMatrixPerspectiveFovLH(XMConvertToRadians(mFOV), ASPECT_RATIO, mNear, mFar);
		break;

	case PROJECTION_TYPE::ORTHOGRAPHIC:
		viewMatrix = matrix::Identity;
		projectionMatrix = XMMatrixOrthographicLH(gEngine->GetWindowWidth() * mScale, gEngine->GetWindowHeight() * mScale, mNear, mFar);
		break;
	}

	sViewMatrix = viewMatrix;
	sProjectionMatrix = projectionMatrix;
}
