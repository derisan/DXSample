#pragma once

#include "MonoBehaviour.h"

class TestCameraScript
	: public MonoBehaviour
{
public:
	TestCameraScript();
	~TestCameraScript();

	virtual void Update() override;

private:
	float mSpeed = 2.0f;
};

