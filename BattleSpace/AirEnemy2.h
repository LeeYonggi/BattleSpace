#pragma once
#include "Enemy.h"
class AirEnemy2 :
	public Enemy
{
public:
	AirEnemy2(Player *player, Vector3 pos, Vector3 direction, STAGE_KIND stage);
	virtual ~AirEnemy2();

private:
	STAGE_KIND stage;
public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

