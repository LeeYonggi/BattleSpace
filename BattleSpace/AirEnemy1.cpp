#include "DXUT.h"
#include "AirEnemy1.h"

#include "Player.h"
#include "UpgradeExp.h"


AirEnemy1::AirEnemy1(Player *player, Vector3 pos, STAGE_KIND stage)
	: Enemy(player, pos)
{
	this->stage = stage;
}


AirEnemy1::~AirEnemy1()
{
}

void AirEnemy1::Init()
{
	scale = 0.06f;
	switch (stage)
	{
	case STAGE_1:
		mesh = MESHMANAGER->AddMesh("Enemy1", L"./Resource/Enemy/enemy_1/enemy_1.obj");
		hp = 400;
		break;
	case STAGE_2:
		mesh = MESHMANAGER->AddMesh("Enemy1_2", L"./Resource/Enemy/enemy_1_2/enemy_1.obj");
		hp = 500;
		break;
	default:
		break;
	}

	enemyFunc[ENEMY_MOVE] = &Enemy::AirEnemyMove;
	enemyFunc[ENEMY_ATTACK] = &Enemy::AirEnemyAttack;
	enemyFunc[ENEMY_DIE] = &Enemy::AirEnemyDie;
	radius = 6.0f;

	speed = 0.5f;
}

void AirEnemy1::Update()
{
	if (!IsInScreen()) return;
	(this->*enemyFunc[state])();
	EnemyAttacked();
	RotateLerp({ 0, 0, 0 }, moveVector, &matR);
	if(isDestroy == true)
		DATAMANAGER->point += 150;
}

void AirEnemy1::Render()
{
	if(attakedFrame > 0)
		MESHMANAGER->DrawMesh(mesh, pos, matR, scale, D3DXCOLOR(1, 0, 0, 1));
	else
		MESHMANAGER->DrawMesh(mesh, pos, matR, scale);
}

void AirEnemy1::Release()
{
	OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_EFFECT, new UpgradeExp(player, pos));

}
