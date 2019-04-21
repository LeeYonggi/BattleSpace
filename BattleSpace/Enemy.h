#pragma once
#include "Object.h"

#include "CharacterAttack.h"

enum ENEMY_STATE
{
	ENEMY_MOVE,
	ENEMY_ATTACK,
	ENEMY_DIE
};
class Player;
class Enemy :
	public Object
{
	using EnemyFunc = void(Enemy::*)(void);
public:
	Enemy(Player *player, Vector3 pos);
	virtual ~Enemy();

protected:
	Player *player;
	EnemyFunc enemyFunc[3];
	Vector3 velocity = { 0, 0, 0 };
	float speed = 1.0f;
	ENEMY_STATE state = ENEMY_MOVE;
	float attakedFrame = 0.0f;
	CharacterAttack attack;

public:
	int hp = 400;

public:
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

public:
	void AirEnemyMove();
	void AirEnemyAttack();
	void EnemyAttacked();
	void AirEnemyDie();
	void RockMove();
	void RockDie();
	bool IsInScreen();
};

