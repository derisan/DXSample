#pragma once

#include "Component.h"

enum class PROJECTION_TYPE
{
	PERSPECTIVE,
	ORTHOGRAPHIC
};

class Camera
	: public Component
{
	struct ViewProjMat
	{
		matrix View;
		matrix Proj;
	};

public:
	Camera();
	virtual ~Camera();

	virtual void FinalUpdate() override;
	void Render();
	
	//const matrix& GetViewMatrix() const { return mViewMatrix; }
	//const matrix& GetProjectionMatrix() const { return mProjectionMatrix; }

private:
	PROJECTION_TYPE mType = PROJECTION_TYPE::PERSPECTIVE;

	float mNear = 0.3f;
	float mFar = 1000.0f;
	float mFOV = 45.0f;
	float mScale = 1.0f;

	ViewProjMat mViewProj = {};

	UploadBuffer<ViewProjMat> mUploadBuffer;

public:
	static matrix sViewMatrix;
	static matrix sProjectionMatrix;
};

