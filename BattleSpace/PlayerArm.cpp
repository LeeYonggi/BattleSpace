#include "DXUT.h"
#include "PlayerArm.h"

#include "Bullet.h"

PlayerArm::PlayerArm(Player *_player)
	: player(_player)
{

}


PlayerArm::~PlayerArm()
{
}

void PlayerArm::Init()
{
	animeMesh.push_back(MESHMANAGER->AddAnimeMesh("Player_Arm_Idle", L"./Resource/Player/player_arm/model%d.obj", 0, ANIME_FRAME));
	animeMesh.push_back(MESHMANAGER->AddAnimeMesh("Player_Arm_Idle", L"./Resource/Player/player_arm/model%d.obj", 0, ANIME_FRAME));
	animeMesh.push_back(MESHMANAGER->AddAnimeMesh("Player_Arm_Attack", L"./Resource/Player/player_shooting/model%d.obj", 0, ANIME_FRAME));

	armFunc[PLAYER_IDLE] = &PlayerArm::ArmIdle;
	armFunc[PLAYER_MOVE] = &PlayerArm::ArmMove;
	armFunc[PLAYER_ATTACK] = &PlayerArm::ArmAttack;

	for(int i = 0; i < 2; i++)
		vAttack.push_back(CharacterAttack());
}

void PlayerArm::Update()
{
	pos = player->pos;
	scale = player->scale;
	moveVector = { player->moveVector.x, player->moveVector.y + upDistance, player->moveVector.z };
	RotateLerp({0, 0, 0}, moveVector, &matR);

	if (INPUTMANAGER->KeyDown('A'))
	{
		if (upDistance == 0)
			upDistance = 0.5f;
		else if (upDistance == 0.5f)
			upDistance = 4;
		else if (upDistance == 4)
			upDistance = 0;
	}
	if (INPUTMANAGER->KeyDown('S'))
	{
		if (upDistance == 0)
			upDistance = 4;
		else if (upDistance == 0.5f)
			upDistance = 0;
		else if (upDistance == 4)
			upDistance = 0.5f;
	}

	for (int i = 0; i < vAttack.size(); i++)
	{
		vAttack[i].AttackUpdate();
	}

	if(player->hp > 0)
		(this->*armFunc[state])();
}

void PlayerArm::Render()
{
	int count = int(frame * 12) % animeMesh[state].size();
	MESHMANAGER->DrawMesh(animeMesh[state][count], pos, matR, scale);
}

void PlayerArm::Release()
{
}

void PlayerArm::ArmIdle()
{
	if (INPUTMANAGER->KeyDown('W'))
		state = PLAYER_ATTACK;
}

void PlayerArm::ArmMove()
{
	if (INPUTMANAGER->KeyDown('W'))
		state = PLAYER_ATTACK;
}

void PlayerArm::ArmAttack()
{
	for (int i = 0; i < vAttack.size(); i++)
	{
		Vector3 vector = { 0, 0, 1 };
		D3DXVec3TransformCoord(&vector, &vector, &matR);

		Vector3 distance = {0, 0, 1};
		Matrix mat;
		D3DXMatrixRotationY(&mat, D3DXToRadian(-30 + i * 60));
		mat *= matR;
		D3DXVec3TransformNormal(&distance, &distance, &mat);

		if (vAttack[i].isAttack == false)
			SOUNDMANAGER->DuplicatePlay("Fire");
		vAttack[i].Attack(OBJ_KINDS::OBJ_PBULLET, BULLET_STATE::BULLET_88MM, pos + distance * 3, vector, 0.35f, 0, 0);
	}
	if (INPUTMANAGER->KeyDown('W'))
		state = PLAYER_IDLE;
}
