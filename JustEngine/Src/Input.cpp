#include "Input.h"
#include "GameCore.h"

#include <XInput.h>
#pragma comment(lib, "xinput9_1_0.lib")

#include <dinput.h>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

namespace GameCore
{
	extern HWND g_hWnd;
}

namespace GameCore
{
	#define NumInputs  static_cast<Input::KEY_TYPE>(InputKey::NumInputs)
	bool sButton[ 2 ][ NumInputs ];
	float sHoldDuration[ NumInputs ];

	IDirectInput8A* sDI;
	IDirectInputDevice8A* sKeyboard;
	IDirectInputDevice8A* sMouse;

	_DIMOUSESTATE2 sMouseState;
	unsigned char sKeybuffer[ 256 ];
	unsigned char sDXKeyMapping[ static_cast<Input::KEY_TYPE>(InputKey::NumKeys) ];

	bool Input::IsAnyPressed()
	{
		return sButton[0][0];
	}

	bool Input::IsPressed(InputKey key)
	{
		return sButton[0][ static_cast<Input::KEY_TYPE>(key) ];
	}

	void Input::Update() {

	}
}