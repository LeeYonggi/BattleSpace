#pragma once
#include "Object.h"
class Effect :
	public Object
{
public:
	Effect(vector<Texture*> effectAnime, Vector3 pos, Vector3 _moveVector, float scale, bool isLoop, float endTime, float animeSpeed);
	virtual ~Effect();

private:
	bool isLoop = false;
	float endTime = 0.0f;
	float animeSpeed = 1.0f;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

