#pragma once

class Timer
{
public:
	void Init();
	void Update();

	uint32 GetFPS() const { return mFPS; }
	float GetDeltaTime() const { return mDeltaTime; }

private:
	uint64	mFrequency = 0;
	uint64	mPrevCount = 0;
	uint32	mFrameCount = 0;
	uint32	mFPS = 0;
	float	mDeltaTime = 0.0f;
	float	mFrameTime = 0.0f;
};

