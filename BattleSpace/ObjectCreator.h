#pragma once
#include "Object.h"


class ObjectCreator :
	public Object
{
public:
	ObjectCreator(STAGE_KIND stage);
	virtual ~ObjectCreator();

private:
	STAGE_KIND stage;
	vector<string> talk;
	vector<string> talk1;
	vector<string> talk2;
	int nowTalk = 0;
	float takingScale = 4.0f;
	bool isTalking = false;
	bool isGameStart = false;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

