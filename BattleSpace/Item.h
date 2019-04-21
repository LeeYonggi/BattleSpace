#pragma once

#include "Object.h"

enum ITEM_KINDS
{
	ITEM_JUMP,
	ITEM_SPEEDUP,
	ITEM_LENGTHUP,
	ITEM_THIRD,
	ITEM_TRAKING,
	ITEM_NUCLEAR
};
class Player;
class Item
	: public Object
{
public:
	Item(Player *player, Vector3 pos, ITEM_KINDS kind);
	virtual ~Item();

private:
	Player *player;
	ITEM_KINDS kind;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;
};

