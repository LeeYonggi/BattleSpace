#pragma once
#include "UI.h"
class Button :
	public UI
{
public:
	Button(Texture *idle, Texture *down, Vector2 pos, Vector2 size, function<void()> func);
	virtual ~Button();

private:
	function<void()> func;
	Texture *idle	= nullptr;
	Texture *down	= nullptr;
	POINT size = { 0, 0 };
	bool isDown = false;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

public:
	bool IsRectCollision(POINT pos, POINT size);
};

