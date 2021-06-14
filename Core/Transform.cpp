#include "CorePch.h"
#include "Transform.h"

Transform::Transform()
	: Component(COMPONENT_TYPE::TRANSFORM)
{

}

Transform::~Transform()
{

}

void Transform::FinalUpdate()
{
	matrix scaleMat = matrix::CreateScale(mLocalScale);
	matrix rotationMat = matrix::CreateRotationX(XMConvertToRadians(mLocalRotation.x));
	rotationMat *= matrix::CreateRotationY(XMConvertToRadians(mLocalRotation.y));
	rotationMat *= matrix::CreateRotationX(XMConvertToRadians(mLocalRotation.z));
	matrix translationMat = matrix::CreateTranslation(mLocalPosition);

	mLocalMatrix = scaleMat * rotationMat * translationMat;
	mWorldMatrix = mLocalMatrix;

	auto parent = GetParent().lock();
	if (parent != nullptr)
	{
		mWorldMatrix *= parent->GetLocalToWorldMatrix();
	}
}
