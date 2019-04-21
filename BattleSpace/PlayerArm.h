#pragma once
#include "Object.h"
#include "Player.h"
#include "CharacterAttack.h"

class Player;
class PlayerArm :
	public Object
{
	using PlayerArmFunc = void(PlayerArm::*)(void);
public:
	PlayerArm(Player *_player);
	virtual ~PlayerArm();

private:
	Player *player;
	PLAYER_STATE state = PLAYER_STATE::PLAYER_IDLE;
	PlayerArmFunc armFunc[3];
	vector<CharacterAttack> vAttack;
	float upDistance = 0.0f;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

public:
	void ArmIdle();
	void ArmMove();
	void ArmAttack();
};

