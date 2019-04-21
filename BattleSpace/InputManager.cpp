#include "DXUT.h"
#include "InputManager.h"


InputManager::InputManager()
{
	Init();
}


InputManager::~InputManager()
{
}

void InputManager::Init()
{
	memset(nowKey, false, sizeof(nowKey));
	memset(pastKey, false, sizeof(pastKey));

}

void InputManager::Update()
{
	memcpy(pastKey, nowKey, sizeof(nowKey));

	for (int i = 0; i < MAX_KEY; i++)
		nowKey[i] = GetAsyncKeyState(i);

	GetCursorPos(&mouse);
	ScreenToClient(DXUTGetHWND(), &mouse);
}
