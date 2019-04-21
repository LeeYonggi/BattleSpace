#include "DXUT.h"
#include "SavePoint.h"

#include "Player.h"
#include "ScreenUI.h"
#include "Button.h"
#include "StageClear.h"
#include "Ending.h"


SavePoint::SavePoint(Player * player, Vector3 pos, bool isLast, STAGE_KIND stage)
{
	this->player = player;
	this->pos = pos;
	this->isLast = isLast;
	this->stage = stage;
}

SavePoint::~SavePoint()
{
}

void SavePoint::Init()
{
	mesh = MESHMANAGER->AddMesh("save_point", L"./Resource/save_point/save_point.obj");
	down = MESHMANAGER->AddMesh("save_point_Alpha", L"./Resource/save_point/save_point_flip/save_point_flip.obj");
	scale = 0.23f;
}

void SavePoint::Update()
{
	if (GetCircleCollision(pos, player->pos, player->radius, 10))
	{
		if (isLast)
		{
			switch (stage)
			{
			case STAGE_1:
			{
				OBJECTMANAGER->AddObject(OBJ_FRONTUI, new StageClear());
			}
				break;
			case STAGE_2:
				SCENEMANAGER->AddScene(new Ending(true));
				break;
			default:
				break;
			}
		}
		else if (isDown == false)
		{
			Texture *temp = IMAGEMANAGER->AddTexture(L"save_pointUI", L"./Resource/UI/save_point_effect.png");
			OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_BACKUI, new ScreenUI(temp, { 640, 170 }, true, { 640, 130 }, 0.8f));
			DATAMANAGER->savePoint = pos;
			isDown = true;
		}
		isDown = true;
	}
	else
	{
		isDown = false;
	}
}

void SavePoint::Render()
{
	if(isDown)
		MESHMANAGER->DrawAlphaMesh(down, pos, matR, scale);
	else
		MESHMANAGER->DrawMesh(mesh, pos, matR, scale);
}

void SavePoint::Release()
{
}
