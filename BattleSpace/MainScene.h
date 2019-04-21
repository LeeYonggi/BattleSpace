#pragma once
#include "Scene.h"

struct Acount
{
	string name;
	int point;
	Acount(string str, int i)
		: name(str), point(i)
	{

	}
	Acount() { }
};
class ScreenUI;
class Button;
class MainScene :
	public Scene
{
public:
	MainScene();
	virtual ~MainScene();

private:
	ScreenUI *intro;
	vector<Button*> buttonUI;
	bool isRank = false;
	bool isInfo = false;
	bool isHowto = false;
	bool isCredit = false;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

