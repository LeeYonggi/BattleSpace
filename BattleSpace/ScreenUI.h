#pragma once
#include "UI.h"
class ScreenUI :
	public UI
{
public:
	ScreenUI(vector<Texture*> vTexture, Vector2 pos, bool isLoop, bool isElaps, float animeFrame);
	ScreenUI(Texture *tex, Vector2 pos, bool isLerp, Vector2 direction, float endTime);
	virtual ~ScreenUI();

private:
	bool isLoop = false;
	bool isLerp = false;
	float animeFrame = 1.0f;
	bool isElaps = false;
	float endTime = 0.0f;
	Vector2 direction = { 0, 0 };

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

