#include "DXUT.h"
#include "Effect.h"


Effect::Effect(vector<Texture*> effectAnime, Vector3 pos, Vector3 _moveVector, float scale, bool isLoop, float endTime, float animeSpeed)
{
	animeTexture.push_back(effectAnime);
	this->scale = scale;
	this->pos = pos;
	this->isLoop = isLoop;
	this->moveVector = moveVector;
	this->endTime = endTime;
	this->animeSpeed = animeSpeed;
}


Effect::~Effect()
{
}

void Effect::Init()
{
	mesh = MESHMANAGER->AddMesh("plane", L"./Resource/Effect/plane/plane.obj");
}

void Effect::Update()
{
	frame += ELTIME;
	if (isLoop)
	{
		if (frame > endTime)
		{
			isDestroy = true;
			isActive = true;
		}
	}
	else
	{
		if (frame * animeSpeed >= animeTexture[0].size())
		{
			isDestroy = true;
			isActive = false;
		}
	}
	pos += moveVector * ELTIME;
}

void Effect::Render()
{
	int count = int(frame * animeSpeed) % animeTexture[0].size();
	matR = GetBillboardToCamera(pos, CAMERAMANAGER->mainCamera->eye);
	MESHMANAGER->DrawEffect(mesh, animeTexture[0][count], pos, matR, scale);
}

void Effect::Release()
{
}
