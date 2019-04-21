#pragma once
#include "UI.h"
class StageClear :
	public UI
{
public:
	StageClear();
	virtual ~StageClear();

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

