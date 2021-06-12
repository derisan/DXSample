#include "CorePch.h"
#include "Timer.h"

void Timer::Init()
{
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&mFrequency));
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&mPrevCount));
}

void Timer::Update()
{
	uint64 currentCount = 0;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));

	mDeltaTime = (currentCount - mPrevCount) / static_cast<float>(mFrequency);
	mPrevCount = currentCount;

	mFrameCount++;
	mFrameTime += mDeltaTime;

	if (mFrameTime > 1.0f)
	{
		mFPS = static_cast<uint32>(mFrameCount / mFrameTime);

		mFrameTime = 0.0f;
		mFrameCount = 0;
	}
}
