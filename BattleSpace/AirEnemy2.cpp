#include "DXUT.h"
#include "AirEnemy2.h"

#include "Player.h"
#include "Bullet.h"
#include "UpgradeExp.h"

AirEnemy2::AirEnemy2(Player *player, Vector3 pos, Vector3 direction, STAGE_KIND stage)
	: Enemy(player, pos)
{
	moveVector = direction;
	this->stage = stage;
}


AirEnemy2::~AirEnemy2()
{
}

void AirEnemy2::Init()
{
	scale = 0.07;
	switch (stage)
	{
	case STAGE_1:
		mesh = MESHMANAGER->AddMesh("Enemy2", L"./Resource/Enemy/enemy_2/enemy_2.obj");
		hp = 500;
		break;
	case STAGE_2:
		mesh = MESHMANAGER->AddMesh("Enemy2_2", L"./Resource/Enemy/enemy_2_2/enemy_2.obj");
		hp = 600;
		break;
	default:
		break;
	}


	radius = 6.0f;
	speed = 0.2f;
}

void AirEnemy2::Update()
{
	if (!IsInScreen()) return;
	if (hp < 1)
		AirEnemyDie();
	else
		EnemyAttacked();

	attack.AttackUpdate();
	attack.Attack(OBJ_KINDS::OBJ_EBULLET, BULLET_STATE::BULLET_ENEMY, pos, moveVector, 3.0f, 0, 0);

	RotateLerp({ 0, 0, 0 }, moveVector, &matR);
	if (isDestroy == true)
		DATAMANAGER->point += 150;
}

void AirEnemy2::Render()
{
	if (attakedFrame > 0)
		MESHMANAGER->DrawMesh(mesh, pos, matR, scale, D3DXCOLOR(1, 0, 0, 1));
	else
		MESHMANAGER->DrawMesh(mesh, pos, matR, scale);
}

void AirEnemy2::Release()
{
	OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_EFFECT, new UpgradeExp(player, pos));
}
