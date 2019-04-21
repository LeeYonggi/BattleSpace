#include "DXUT.h"
#include "PlayerUI.h"

#include "Player.h"

PlayerUI::PlayerUI(Player *player, STAGE_KIND stage)
{
	this->stage = stage;
	this->player = player;
}


PlayerUI::~PlayerUI()
{
}

void PlayerUI::Init()
{
	texture = IMAGEMANAGER->AddTexture(L"InGameUI", L"./Resource/UI/ingame_UI.png");
	heart = IMAGEMANAGER->AddTexture(L"Life", L"./Resource/UI/life.png");
	exp = IMAGEMANAGER->AddTexture(L"exp", L"./Resource/UI/gage_1.png");
	expGage = IMAGEMANAGER->AddTexture(L"expgage", L"./Resource/UI/gage_2.png");
	IMAGEMANAGER->AddTexture(L"miniPlayer", L"./Resource/UI/minimap_player.png");
	uiPos = {640, 360};
}

void PlayerUI::Update()
{

}

void PlayerUI::Render()
{
	IMAGEMANAGER->DrawTexture(texture, uiPos);
	for (int i = 0; i < player->totalHp; i++)
	{
		IMAGEMANAGER->DrawTexture(heart, {150.0f + i * 80, 68});
	}
	for (int i = 0; i < 6; i++)
	{
		IMAGEMANAGER->DrawFont(to_string(player->itemCount[i]), {76 + 108.0f * i, 665 }, 50);
	}
	CHAR cstr[16];
	sprintf(cstr, "%04d", DATAMANAGER->point);
	IMAGEMANAGER->DrawFont(cstr, {1000, 25}, 100);
	//1210 800 410
	switch (stage)
	{
	case STAGE_1:
	{
		float maxDistance = GetDistance(Vector3(800, -74, 0), Vector3( 0, 0, 0 ));
		float distance = GetDistance(Vector3(800, -74, 0), player->pos);
		IMAGEMANAGER->DrawTexture(L"miniPlayer", { 1014 + 200 - (distance / maxDistance) * 200, 176 });
	}
		break;
	case STAGE_2:
	{
		float maxDistance = GetDistance(Vector3(835, -90, 0), Vector3(0, 0, 0));
		float distance = GetDistance(Vector3(835, -90, 0), player->pos);
		IMAGEMANAGER->DrawTexture(L"miniPlayer", { 1014 + 200 - (distance / maxDistance) * 200, 176 });
	}
		break;
	default:
		break;
	}
	
	IMAGEMANAGER->DrawTexture(expGage, { 1150, 325 }, 0, 1, {1, (float)player->upgradeGage / 5.0f});
	IMAGEMANAGER->DrawTexture(exp, { 1150, 325 });
	
	IMAGEMANAGER->DrawFont(to_string(max(player->hp, 1)), {910, 570}, 120);
}

void PlayerUI::Release()
{

}
