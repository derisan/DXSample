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
public:
	Camera();
	virtual ~Camera();

	virtual void FinalUpdate() override;
	
	//const matrix& GetViewMatrix() const { return mViewMatrix; }
	//const matrix& GetProjectionMatrix() const { return mProjectionMatrix; }

private:
	PROJECTION_TYPE mType = PROJECTION_TYPE::PERSPECTIVE;

	float mNear = 0.3f;
	float mFar = 1000.0f;
	float mFOV = 90.0f;
	float mScale = 1.0f;

public:
	static matrix sViewMatrix;
	static matrix sProjectionMatrix;
};

