#include "DXUT.h"
#include "Button.h"



Button::Button(Texture * idle, Texture * down, Vector2 pos, Vector2 size, function<void()> func)
{
	this->idle = idle;
	this->down = down;
	this->uiPos = pos;
	this->size.x = size.x;
	this->size.y = size.y;
	this->func = func;
}

Button::~Button()
{
}

void Button::Init()
{
}

void Button::Update()
{
	if (IsRectCollision({ (int)uiPos.x, (int)uiPos.y }, size))
	{
		if (INPUTMANAGER->KeyDown(VK_LBUTTON))
		{
			func();
		}
		isDown = true;
	}
	else
	{
		isDown = false;
	}
}

void Button::Render()
{
	if (isDown)
	{
		IMAGEMANAGER->DrawTexture(down, uiPos);
	}
	else
	{
		IMAGEMANAGER->DrawTexture(idle, uiPos);
	}
}

void Button::Release()
{
}

bool Button::IsRectCollision(POINT pos, POINT size)
{
	RECT empty = { 0 };
	RECT re = { pos.x - size.x * 0.5, pos.y - size.y * 0.5,
	pos.x + size.x * 0.5, pos.y + size.y * 0.5 };
	RECT mouse = { INPUTMANAGER->GetMouse().x, INPUTMANAGER->GetMouse().y,
	INPUTMANAGER->GetMouse().x + 1, INPUTMANAGER->GetMouse().y + 1};
	return IntersectRect(&empty, &re, &mouse);
}
