#include "DXUT.h"
#include "TsCamera.h"

#include "Player.h"

TsCamera::TsCamera(Player *_player)
{
	player = _player;
}


TsCamera::~TsCamera()
{
}

void TsCamera::Init()
{
}

void TsCamera::Update()
{
	Camera::Update();
	Vector3 temp = player->pos;
	at = player->pos;
	temp.z -= 30;
	temp.y += 10;
	//if (player->state == PLAYER_MOVE)
	//{
	//	temp.x -= player->moveVector.x * 15;
	//	temp.z += player->moveVector.z * 10;
	//}
	eye = Lerp(eye, temp, 0.1f);

}

void TsCamera::Release()
{
}
