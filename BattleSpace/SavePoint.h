#pragma once
#include "Object.h"

class Player;
class SavePoint :
	public Object
{
public:
	SavePoint(Player *player, Vector3 pos, bool isLast, STAGE_KIND stage);
	virtual ~SavePoint();

private:
	Player *player;
	CMeshLoader *down;
	bool isSave = false;
	bool isDown = false;
	bool isLast = false;
	STAGE_KIND stage = STAGE_1;


public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

