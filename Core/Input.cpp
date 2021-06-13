#include "CorePch.h"
#include "Input.h"

void Input::Init(HWND hWnd)
{
	mhWnd = hWnd;

	for (auto& keyState : mKeyStates)
	{
		keyState = KEY_STATE::NONE;
	}
}

void Input::Update()
{
	HWND hwnd = ::GetActiveWindow();
	if (mhWnd != hwnd)
	{
		for (uint32 key = 0; key < KEY_TYPE_COUNT; key++)
			mKeyStates[key] = KEY_STATE::NONE;

		return;
	}

	BYTE keys[KEY_TYPE_COUNT] = {};
	::GetKeyboardState(keys);

	for (uint32 key = 0; key < KEY_TYPE_COUNT; key++)
	{
		if (keys[key] & 0x80)
		{
			KEY_STATE& state = mKeyStates[key];

			if (state == KEY_STATE::HOLD || state == KEY_STATE::PRESSED)
			{
				state = KEY_STATE::HOLD;
			}
			else
			{
				state = KEY_STATE::PRESSED;
			}
		}

		else
		{
			KEY_STATE& state = mKeyStates[key];

			if (state == KEY_STATE::HOLD || state == KEY_STATE::PRESSED)
			{
				state = KEY_STATE::RELEASED;
			}
			else
			{
				state = KEY_STATE::NONE;
			}
		}
	}
}
