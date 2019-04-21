#include "DXUT.h"
#include "ObjectCreator.h"

#include "Player.h"
#include "TsCamera.h"
#include "Background.h"
#include "PlayerArm.h"
#include "AirEnemy1.h"
#include "Rock.h"
#include "SavePoint.h"
#include "MainScene.h"
#include "AirEnemy2.h"
#include "Ending.h"


ObjectCreator::ObjectCreator(STAGE_KIND stage)
{
	this->stage = stage;
	texture = IMAGEMANAGER->AddTexture(L"Talking", L"./Resource/UI/Talking.png");

	{
		talk1.push_back("우리는 지구를 살리기 위해 이곳에 왔어.");
		talk1.push_back("전쟁중인 우리에겐 이 임무는 아주 중요해.");
		talk1.push_back("우리의 마지막 장소까지 죽지 않고 이동해야해.");
		talk1.push_back("건투를 빌어.");
	}
	{
		talk2.push_back("개척지에 무사히 도착을 했어.");
		talk2.push_back("....");
		talk2.push_back("개척지의 상태가....?");
		talk2.push_back("우리의 개척지가 공격받고 있어.");
		talk2.push_back("개척지를 지켜내야 해!");
	}
}

ObjectCreator::~ObjectCreator()
{
}

void ObjectCreator::Init()
{
	switch (stage)
	{
	case STAGE_1:
	{
		SOUNDMANAGER->PlayWavSound("InGame", true);
		talk = talk1;
		Background *back = OBJECTMANAGER->AddObject(OBJ_BACKGROUND, new Background(stage));
		Player *player = OBJECTMANAGER->AddObject(OBJ_PLAYER, new Player(back));
		OBJECTMANAGER->AddObject(OBJ_PLAYER, new PlayerArm(player));
		float height = -207;
		int i = 0;
		for (int i = 0; i < 15; i++)
		{
			Vector3 tempPos = { 100 + i * 60.0f, 0, (float)GetRandomNumber(-10, 30)};
			if(i > 5)
				tempPos.y = height + 9;
			OBJECTMANAGER->AddObject(OBJ_ENEMY, new AirEnemy1(player, { tempPos.x, tempPos.y + 10, tempPos.z }, stage));
		}
		i = 0;
		int noCheck = 0;
		while (true)
		{
			if (i > 20)
				break;
			Vector3 tempPos;
			tempPos.x = 100 + i * 40;
			if (i > 6)
			{
				tempPos.y = height;
			}
			else
			{
				tempPos.y = 0;
			}
			tempPos.z = GetRandomNumber(-60, 50);
			if (GetPixelCollision({ tempPos.x, tempPos.z }, back->minimap2))
			{
				OBJECTMANAGER->AddObject(OBJ_ENEMY, new Rock(player, {tempPos.x, tempPos.y, tempPos.z }));
				noCheck = 0;
				i++;
			}
			else
			{
				if (noCheck > 30)
					i++;
				noCheck++;
				continue;
			}
		}
		OBJECTMANAGER->AddObject(OBJ_ENEMY, new AirEnemy2(player, { 200, 3, -115 }, { 0, 0, 1 }, stage));
		OBJECTMANAGER->AddObject(OBJ_ENEMY, new AirEnemy2(player, { 265, 3, -40 }, { 0, 0, 1 }, stage));
		OBJECTMANAGER->AddObject(OBJ_ENEMY, new AirEnemy2(player, { 470, height + 3, -55 }, { 0, 0, 1 }, stage));
		OBJECTMANAGER->AddObject(OBJ_ENEMY, new AirEnemy2(player, { 500, height + 3, 20 }, { 0, 0, -1 }, stage));
		OBJECTMANAGER->AddObject(OBJ_ENEMY, new AirEnemy2(player, { 640, height + 3, 0 }, { -1, 0, 0 }, stage));

		OBJECTMANAGER->AddObject(OBJ_SAVEPOINT, new SavePoint(player, { 60, 0, -10 }, false, stage));
		OBJECTMANAGER->AddObject(OBJ_SAVEPOINT, new SavePoint(player, {320, height, -10}, false, stage));
		OBJECTMANAGER->AddObject(OBJ_SAVEPOINT, new SavePoint(player, { 790, height, -10 }, false, stage));
		OBJECTMANAGER->AddObject(OBJ_SAVEPOINT, new SavePoint(player, { 790, -76, -10 }, true, stage));

		DATAMANAGER->savePoint = { 10, 0, -5 };
		CAMERAMANAGER->AddCamera("TsCamera", OBJECTMANAGER->AddObject(OBJ_CAMERA, new TsCamera(player)));
		CAMERAMANAGER->ChangeCamera("TsCamera");
	}
		break;
	case STAGE_2:
	{
		SOUNDMANAGER->PlayWavSound("InGame2", true);
		talk = talk2;
		Background *back = OBJECTMANAGER->AddObject(OBJ_BACKGROUND, new Background(stage));
		Player *player = OBJECTMANAGER->AddObject(OBJ_PLAYER, new Player(back));
		OBJECTMANAGER->AddObject(OBJ_PLAYER, new PlayerArm(player));
		float height = -85;
		int i = 0;
		for (int i = 0; i < 20; i++)
		{
			Vector3 tempPos = { 60 + i * 45.0f, 0, (float)GetRandomNumber(-10, 100) };
			if (i > 7)
				tempPos.y = height + 9;
			OBJECTMANAGER->AddObject(OBJ_ENEMY, new AirEnemy1(player, { tempPos.x, tempPos.y + 10, tempPos.z }, stage));
		}
		i = 0;
		int noCheck = 0;
		while (true)
		{
			if (i > 20)
				break;
			Vector3 tempPos;
			tempPos.x = 50 + i * 40;
			if (i > 7)
			{
				tempPos.y = height;
			}
			else
			{
				tempPos.y = 0;
			}
			tempPos.z = GetRandomNumber(-10, 110);
			if (GetPixelCollision({ tempPos.x, tempPos.z }, back->minimap2))
			{
				OBJECTMANAGER->AddObject(OBJ_ENEMY, new Rock(player, { tempPos.x, tempPos.y, tempPos.z }));
				noCheck = 0;
				i++;
			}
			else
			{
				if (noCheck > 30)
					i++;
				noCheck++;
				continue;
			}
		}
		OBJECTMANAGER->AddObject(OBJ_ENEMY, new AirEnemy2(player, { 150, 3, 40 }, { 0, 0, -1 }, stage));
		OBJECTMANAGER->AddObject(OBJ_ENEMY, new AirEnemy2(player, { 220, 3, 40 }, { 0, 0, -1 }, stage));
		OBJECTMANAGER->AddObject(OBJ_ENEMY, new AirEnemy2(player, { 280, height + 3, 40 }, { 0, 0,  1 }, stage));
		OBJECTMANAGER->AddObject(OBJ_ENEMY, new AirEnemy2(player, { 520, height + 3, 60 }, { -1, 0, 0 }, stage));
		OBJECTMANAGER->AddObject(OBJ_ENEMY, new AirEnemy2(player, { 550, height + 3, 10 }, { 0, 0, 1 }, stage));

		OBJECTMANAGER->AddObject(OBJ_SAVEPOINT, new SavePoint(player, { 150, 0, 0 }, false, stage));
		OBJECTMANAGER->AddObject(OBJ_SAVEPOINT, new SavePoint(player, { 300, height, 55 }, false, stage));
		OBJECTMANAGER->AddObject(OBJ_SAVEPOINT, new SavePoint(player, { 545, height, 50 }, false, stage));
		OBJECTMANAGER->AddObject(OBJ_SAVEPOINT, new SavePoint(player, { 835, height - 5, -30 }, true, stage));

		DATAMANAGER->savePoint = {10, 0, 0 };
		CAMERAMANAGER->AddCamera("TsCamera", OBJECTMANAGER->AddObject(OBJ_CAMERA, new TsCamera(player)));
		CAMERAMANAGER->ChangeCamera("TsCamera");
	}
		break;
	default:
		break;
	}
	isTalking = true;
}

void ObjectCreator::Update()
{
	if (INPUTMANAGER->KeyDown(VK_F4))
	{
		SCENEMANAGER->AddScene(new MainScene());
	}
	if (INPUTMANAGER->KeyDown(VK_F5))
	{
		SCENEMANAGER->AddScene(new IngameScene(STAGE_1));
	}
	if (INPUTMANAGER->KeyDown(VK_F6))
	{
		SCENEMANAGER->AddScene(new IngameScene(STAGE_2));
	}
	if (INPUTMANAGER->KeyDown(VK_F7))
	{
		SCENEMANAGER->AddScene(new Ending(true));
	}
	if (INPUTMANAGER->KeyDown(VK_F8))
	{
		SCENEMANAGER->AddScene(new Ending(false));
	}
	if (INPUTMANAGER->KeyDown(VK_LBUTTON))
	{
		if (nowTalk < talk.size() - 1)
			nowTalk++;
		else
			isTalking = false;
	}
	if (isTalking)
	{
		takingScale = Lerp(takingScale, 1.0f, 0.1f);
		timeScale = 0;
	}
	else
	{
		if (!isGameStart)
		{
			takingScale = Lerp(takingScale, 4.0f, 0.1f);
			timeScale = 1;
			if (takingScale > 3.6f)
				isGameStart = true;
		}
	}
}

void ObjectCreator::Render()
{
	if (isTalking)
	{
		IMAGEMANAGER->DrawTexture(texture, { 640, 360 }, 0, takingScale);
		if(takingScale < 1.1f)
			IMAGEMANAGER->DrawFont(talk[nowTalk], {460, 540}, 30);
	}
}

void ObjectCreator::Release()
{
	CAMERAMANAGER->Release();
	switch (stage)
	{
	case STAGE_1:
		SOUNDMANAGER->Stop("InGame");
		break;
	case STAGE_2:
		SOUNDMANAGER->Stop("InGame2");
		break;
	default:
		break;
	}
}
