#include "DXUT.h"
#include "UpgradeExp.h"

#include "Player.h"

UpgradeExp::UpgradeExp(Player *player, Vector3 pos)
{
	this->player = player;
	this->pos = pos;
}


UpgradeExp::~UpgradeExp()
{
}

void UpgradeExp::Init()
{
	mesh = MESHMANAGER->AddMesh("plane", L"./Resource/Effect/plane/plane.obj");
	texture = IMAGEMANAGER->AddTexture(L"Exp", L"./Resource/Effect/exp.png");
	scale = 0.05f;
}

void UpgradeExp::Update()
{
	moveVector = GetTargetVec3(pos, player->pos);
	if (GetCircleCollision(player->pos, pos, player->radius, radius))
	{
		player->upgradeGage += 1;
		isDestroy = true;
	}
	pos += moveVector * ELTIME * 100;
}

void UpgradeExp::Render()
{
	matR = GetBillboardToCamera(pos, CAMERAMANAGER->mainCamera->eye);
	MESHMANAGER->DrawEffect(mesh, texture, pos, matR, scale);
}

void UpgradeExp::Release()
{
}
