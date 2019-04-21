#pragma once
#include "Scene.h"

enum STAGE_KIND
{
	STAGE_1,
	STAGE_2
};
class IngameScene :
	public Scene
{
public:
	IngameScene(STAGE_KIND _stage);
	virtual ~IngameScene();

private:
	STAGE_KIND stage;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

