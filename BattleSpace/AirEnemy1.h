#pragma once
#include "Enemy.h"

class AirEnemy1 :
	public Enemy
{
public:
	AirEnemy1(Player *player, Vector3 pos, STAGE_KIND stage);
	virtual ~AirEnemy1();

private:
	STAGE_KIND stage;

public:
	void Init()		override;
	void Update()	override;
	void Render()	override;
	void Release()	override;
};

