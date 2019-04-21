#pragma once
#include "Singleton.h"

#define MAX_KEY 256
class InputManager :
	public Singleton<InputManager>
{
public:
	InputManager();
	virtual ~InputManager();

private:
	bool nowKey[MAX_KEY];
	bool pastKey[MAX_KEY];
	POINT mouse = {0, 0};

public:
	void Init();
	void Update();

public:
	bool KeyDown(int key) { return (pastKey[key] == false && nowKey[key] == true); }
	bool KeyPress(int key) { return (pastKey[key] == true && nowKey[key] == true); }
	bool KeyUp(int key) { return (pastKey[key] == true && nowKey[key] == false); }

	POINT GetMouse() { return mouse; }
};

#define INPUTMANAGER InputManager::GetInstance()