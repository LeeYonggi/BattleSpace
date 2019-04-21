#include "DXUT.h"
#include "StageClear.h"

#include "Button.h"
#include "IngameScene.h"

StageClear::StageClear()
{
}


StageClear::~StageClear()
{
}

void StageClear::Init()
{
	Texture *tex = IMAGEMANAGER->AddTexture(L"score", L"./Resource/UI/score.png");
	OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_UI, new Button(tex, tex,
		{ 640, 560 }, { 1280, 720 }, [&]() {SCENEMANAGER->AddScene(new IngameScene(STAGE_2)); }));

	animeTexture.push_back(IMAGEMANAGER->AddAnimeTexture(L"StageClear", L"./Resource/stage_clear/%d.png", 1, 9));
}

void StageClear::Update()
{
	frame += ELTIME;
}

void StageClear::Render()
{
	int count = int(frame * 12) % animeTexture[0].size();
	IMAGEMANAGER->DrawTexture(animeTexture[0][count], {640, 360});

	CHAR ctr[16];
	sprintf(ctr, "%04d", DATAMANAGER->point);
	IMAGEMANAGER->DrawFont(ctr, {540, 500}, 70);

}

void StageClear::Release()
{
}
