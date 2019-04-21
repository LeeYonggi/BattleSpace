#include "DXUT.h"
#include "Ending.h"

#include "MainScene.h"
#include <fstream>

Ending::Ending(bool isHappy)
{
	this->isHappy = isHappy;
}


Ending::~Ending()
{
}

void Ending::Init()
{
	if (isHappy)
	{
		vTex = (IMAGEMANAGER->AddAnimeTexture(L"happy_ending", L"./Resource/UI/happy_ending/%d.png", 1, 2));
	}
	else
	{
		vTex = (IMAGEMANAGER->AddAnimeTexture(L"bad_ending", L"./Resource/UI/bad_ending.png", 0, 0));
	}
	score = IMAGEMANAGER->AddTexture(L"score", L"./Resource/UI/score.png");
}

void Ending::Update()
{
	for (int i = 0; i < MAX_KEY; i++)
	{
		if (INPUTMANAGER->KeyDown(VK_RETURN))
		{
			fstream fs;
			fs.open(L"./Data/Rank.txt", ios::app);

			fs << name << "\t" << DATAMANAGER->point << endl;

			fs.close();
			SCENEMANAGER->AddScene(new MainScene());
			break;
		}
		else if (INPUTMANAGER->KeyDown(i))
		{
			name.push_back(i);
		}
	}
	frame += ELTIME;
}

void Ending::Render()
{
	int count = int(frame * 5) % vTex.size();
	IMAGEMANAGER->DrawTexture(vTex[count], { 640, 360 }, 0, 1, {1, 1}, D3DXCOLOR(1, 1, 1, frame));
	IMAGEMANAGER->DrawTexture(score, {200, 200});
	CHAR cstr[128];
	sprintf(cstr, "%04d", DATAMANAGER->point);
	IMAGEMANAGER->DrawFont(cstr, {140, 160}, 70, D3DXCOLOR(1, 1, 1, frame));
	IMAGEMANAGER->DrawFont(name, {180, 310}, 40, D3DXCOLOR(1, 1, 1, frame));
}

void Ending::Release()
{
}
