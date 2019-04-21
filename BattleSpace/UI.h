#pragma once
#include "Object.h"

#include <functional>
class UI :
	public Object
{
public:
	UI();
	virtual ~UI();

protected:
	Vector2 uiPos = { 0, 0 };

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

