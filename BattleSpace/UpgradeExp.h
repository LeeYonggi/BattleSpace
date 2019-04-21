#pragma once
#include "Object.h"

class Player;
class UpgradeExp :
	public Object
{
public:
	UpgradeExp(Player *player, Vector3 pos);
	virtual ~UpgradeExp();

private:
	Player *player;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

