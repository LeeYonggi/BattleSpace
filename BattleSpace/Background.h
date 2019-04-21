#pragma once
#include "Object.h"


class Background :
	public Object
{
public:
	Background(STAGE_KIND _stage);
	virtual ~Background();

public:
	STAGE_KIND stage;

public:
	Texture *minimap1;
	Texture *minimap2;


public:
	void Init()		override;
	void Update()	override;
	void Render()	override;
	void Release()	override;
};

