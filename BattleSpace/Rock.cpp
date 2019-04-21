#include "DXUT.h"
#include "Rock.h"

#include "Particle.h"
#include "Item.h"
#include "Player.h"

Rock::Rock(Player *player, Vector3 pos)
	: Enemy(player, pos)
{
	radius = 12.0f;

	hp = 600;
}


Rock::~Rock()
{
}

void Rock::Init()
{
	animeMesh.push_back(MESHMANAGER->AddAnimeMesh("stone", L"./Resource/Enemy/stone/model%d.obj", 0, 10));
	scale = 0.3f;

}

void Rock::Update()
{
	if (!IsInScreen()) return;
	if (GetCircleCollision(player->pos, pos, radius, 1) && hp > 0)
	{
		hp = 0;
		if(player->isSpeedUp == false && player->isUltra == false)
			player->hp -= 1;
	}
	EnemyAttacked();
	if (hp < 1)
	{
		Vector3 tempPos;
		tempPos.x = GetRandomNumber(-6, 6);
		tempPos.y = GetRandomNumber(-6, 6);
		tempPos.z = GetRandomNumber(-6, 6);
		float n = GetRandomNumber(40, 70);
		vParticle[0]->ParticleInit(pos + tempPos, { 0, 0, 0}, n * 0.01f, false, 0.0, 12);
		vParticle[0]->isActive = true;
		frame += ELTIME;
		if (frame * 12 >= animeMesh[0].size())
		{
			isActive = false;
			isDestroy = true;
			int itemNumber = GetRandomNumber(0, 5);
			OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_ITEM, new Item(player, pos, (ITEM_KINDS)itemNumber));
			SOUNDMANAGER->DuplicatePlay("Destroy");
		}
	}
}

void Rock::Render()
{
	int count = int(frame * 12) % animeMesh[0].size();
	MESHMANAGER->DrawMesh(animeMesh[0][count], pos, matR, scale);
}

void Rock::Release()
{
}
