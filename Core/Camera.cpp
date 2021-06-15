#include "CorePch.h"
#include "Camera.h"
#include "Transform.h"
#include "Engine.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "MeshRenderer.h"

matrix Camera::sViewMatrix;
matrix Camera::sProjectionMatrix;

Camera::Camera()
	: Component(COMPONENT_TYPE::CAMERA)
	, mUploadBuffer(DEVICE.Get(), 1, true)
{

}

Camera::~Camera()
{

}

void Camera::FinalUpdate()
{
	switch (mType)
	{
	case PROJECTION_TYPE::PERSPECTIVE:
		mViewProj.View = GetTransform()->GetLocalToWorldMatrix().Invert();
		mViewProj.Proj = XMMatrixPerspectiveFovLH(XMConvertToRadians(mFOV), ASPECT_RATIO, mNear, mFar);
		break;

	case PROJECTION_TYPE::ORTHOGRAPHIC:
		mViewProj.View = matrix::Identity;
		mViewProj.Proj = XMMatrixOrthographicLH(gEngine->GetWindowWidth() * mScale, gEngine->GetWindowHeight() * mScale, mNear, mFar);
		break;
	}

	mUploadBuffer.CopyData(0, mViewProj);
}

void Camera::Render()
{
	auto scene = GET_SINGLETON(SceneManager)->GetActiveScene();

	const auto& objs = scene->GetGameObjects();


	CMD_LIST->SetGraphicsRootConstantBufferView(RootParamIndex::ROOT_PARAM_VIEWPROJ, mUploadBuffer.Resource()->GetGPUVirtualAddress());

	for (auto& obj : objs)
	{
		auto meshRenderer = obj->GetMeshRenderer();

		if (meshRenderer == nullptr)
		{
			continue;
		}

		meshRenderer->Render();
	}
}
