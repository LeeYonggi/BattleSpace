#include "DXUT.h"
#include "Enemy.h"

#include "Player.h"
#include "Bullet.h"
#include "Background.h"
#include "Effect.h"
#include "Particle.h"



Enemy::Enemy(Player * player, Vector3 pos)
{
	this->player = player;
	this->pos = pos;
	radius = 5.0f;

	vector<Texture*> effect = IMAGEMANAGER->AddAnimeTexture(L"Bomb", L"./Resource/Effect/bomb/%d.png", 1, 6);
	vParticle.push_back(OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_EFFECT, new Particle(effect, 0.2f)));
	vParticle[0]->isActive = false;
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{

}

void Enemy::Render()
{
}

void Enemy::Release()
{
}

void Enemy::AirEnemyMove()
{
	moveVector = GetTargetVec3(pos, { player->pos.x, player->pos.y + 9, player->pos.z });
	velocity += moveVector;
	velocity.x = max(min(velocity.x, 30), -30);
	velocity.y = max(min(velocity.y, 3), -3);
	velocity.z = max(min(velocity.z, 30), -30);

	if (GetCircleCollision(pos, player->pos, 1, 30))
		state = ENEMY_ATTACK;

	pos += velocity * ELTIME * speed;
}

void Enemy::AirEnemyAttack()
{
	Vector3 target = GetTargetVec3(pos, { player->pos.x, player->pos.y + 9, player->pos.z });
	moveVector = GetTargetVec3(pos, player->pos);

	velocity.x = Lerp(velocity.x, 0.0f, 0.1f);
	velocity.y += target.y;
	velocity.y = max(min(velocity.y, 3), -3);
	velocity.z = Lerp(velocity.z, 0.0f, 0.1f);

	if (!GetCircleCollision(pos, player->pos, 1, 30))
		state = ENEMY_MOVE;

	attack.AttackUpdate();
	attack.Attack(OBJ_KINDS::OBJ_EBULLET, BULLET_STATE::BULLET_ENEMY, pos, moveVector, 2.0f, 0, 0);

	pos += velocity * ELTIME * speed;
}

void Enemy::EnemyAttacked()
{
	if (hp < 1)
	{
		state = ENEMY_DIE;
	}
	if (hp < 1) return;

	auto iter = OBJECTMANAGER->GetObjectList(OBJ_KINDS::OBJ_PBULLET);
	for (auto bullet = iter->begin(); bullet != iter->end(); bullet++)
	{
		if ((*bullet)->GetCircleCollision(pos, (*bullet)->pos, radius, (*bullet)->radius))
		{
			Bullet *tempBullet = (Bullet*)(*bullet);
			tempBullet->isDestroy = true;
			hp -= tempBullet->damage;
			attakedFrame = 0.2f;
		}
	}
	attakedFrame -= ELTIME;
}

void Enemy::AirEnemyDie()
{
	velocity.y -= 1.0f;

	pos += velocity * ELTIME * speed;
	
	float n = GetRandomNumber(20, 40);
	vParticle[0]->ParticleInit(pos, -moveVector * 5, n * 0.01f, false, 0.0f, 12.0f); //RandÇØ
	vParticle[0]->isActive = true;

	auto iter = OBJECTMANAGER->GetObjectList(OBJ_KINDS::OBJ_BACKGROUND);
	Background *back = (Background*)(*iter->begin());
	if (GetPixelCollision(Vector2(pos.x, pos.y) * 5, back->minimap1))
	{
		vParticle[0]->isActive = false;
		isDestroy = true;
		vector<Texture*> effect = IMAGEMANAGER->AddAnimeTexture(L"Bomb", L"./Resource/Effect/bomb/%d.png", 1, 6);
		OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_EFFECT, new Effect(effect, pos, { 0, 0, 0 }, 0.5f, false, 0.0f, 10));
		CAMERAMANAGER->CameraShake(0.4f);
	}
}

void Enemy::RockMove()
{
}

void Enemy::RockDie()
{
}


bool Enemy::IsInScreen()
{
	return (CAMERAMANAGER->mainCamera->eye.x - 50 < pos.x && CAMERAMANAGER->mainCamera->eye.x + 50 > pos.x);
}
