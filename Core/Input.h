#pragma once

enum class KEY_TYPE
{
	UP = VK_UP,
	DOWN = VK_DOWN,
	LEFT = VK_LEFT,
	RIGHT = VK_RIGHT,

	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',
};

enum class KEY_STATE
{
	NONE,
	HOLD,
	PRESSED,
	RELEASED,
	END
};

enum
{
	KEY_TYPE_COUNT = static_cast<int32>(UINT8_MAX) + 1,
	KEY_STATE_COUNT = static_cast<int32>(KEY_STATE::END),
};

class Input
{
public:
	void Init(HWND hWnd);
	void Update();

	bool IsButtonHold(KEY_TYPE key) { return GetState(key) == KEY_STATE::HOLD; }
	bool IsButtonPressed(KEY_TYPE key) { return GetState(key) == KEY_STATE::PRESSED; }
	bool IsButtonReleased(KEY_TYPE key) { return GetState(key) == KEY_STATE::RELEASED; }

private:
	inline KEY_STATE GetState(KEY_TYPE key) { return mKeyStates[static_cast<uint8>(key)]; }

private:
	HWND mhWnd;
	std::array<KEY_STATE, KEY_TYPE_COUNT> mKeyStates;
};

