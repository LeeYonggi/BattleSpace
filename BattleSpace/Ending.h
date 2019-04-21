#pragma once
#include "Scene.h"
class Ending :
	public Scene
{
public:
	Ending(bool isHappy);
	virtual ~Ending();

private:
	string name;
	bool isHappy;
	float alpha = 0.0f;
	vector<Texture*> vTex;
	Texture *score;
	float frame = 0.0f;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

