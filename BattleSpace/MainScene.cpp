#include "DXUT.h"
#include "MainScene.h"

#include "ScreenUI.h"
#include "Button.h"
#include <fstream>

MainScene::MainScene()
{
}


MainScene::~MainScene()
{
}

void MainScene::Init()
{
	SOUNDMANAGER->AddSound("MainSong", L"./Sound/song1.wav");
	SOUNDMANAGER->PlayWavSound("MainSong", true);
	DATAMANAGER->point = 0;
	vector<Texture*> temp = IMAGEMANAGER->AddAnimeTexture(L"Intro", L"./Resource/intro/intro%04d.jpg", 0, 100);
	intro = OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_BACKUI, new ScreenUI(temp, {640, 360}, false, false, 0.2f));

	Texture *idle = IMAGEMANAGER->AddTexture(L"start_no_click", L"./Resource/MainUI/start_no_click.png");
	Texture *down = IMAGEMANAGER->AddTexture(L"start_click", L"./Resource/MainUI/start_click.png");
	buttonUI.push_back(OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_UI, new Button(idle, down, 
		{ 640, 340 }, { 342, 131 }, [&]() {SCENEMANAGER->AddScene(new IngameScene(STAGE_1)); })));

	idle = IMAGEMANAGER->AddTexture(L"title", L"./Resource/MainUI/title.png");
	down = IMAGEMANAGER->AddTexture(L"title", L"./Resource/MainUI/title.png");
	buttonUI.push_back(OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_UI, new Button(idle, down,
		{ 640, 150 }, { 342, 131 }, [&]() { isInfo = true; })));

	idle = IMAGEMANAGER->AddTexture(L"info_no_click", L"./Resource/MainUI/info_no_click.png");
	down = IMAGEMANAGER->AddTexture(L"info_click", L"./Resource/MainUI/info_click.png");
	buttonUI.push_back(OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_UI, new Button(idle, down,
		{ 640, 480 }, { 342, 131 }, [&]() { isInfo = true; })));

	idle = IMAGEMANAGER->AddTexture(L"how_no_click", L"./Resource/MainUI/how_no_click.png");
	down = IMAGEMANAGER->AddTexture(L"how_click", L"./Resource/MainUI/how_click.png");
	buttonUI.push_back(OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_UI, new Button(idle, down,
		{ 640, 620 }, { 342, 131 }, [&]() { isHowto = true; })));

	idle = IMAGEMANAGER->AddTexture(L"ranking_no_click", L"./Resource/MainUI/ranking_no_click.png");
	down = IMAGEMANAGER->AddTexture(L"ranking_click", L"./Resource/MainUI/ranking_click.png");
	buttonUI.push_back(OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_UI, new Button(idle, down,
		{ 1228, 668 }, { 105, 101 }, [&]() { isRank = true; })));

	idle = IMAGEMANAGER->AddTexture(L"credit_no_click", L"./Resource/MainUI/credit_no_click.png");
	down = IMAGEMANAGER->AddTexture(L"credit_click", L"./Resource/MainUI/credit_click.png");
	buttonUI.push_back(OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_UI, new Button(idle, down,
		{ 1230, 50 }, { 105, 101 }, [&]() { isCredit = true; })));

	for (int i = 0; i < buttonUI.size(); i++)
		buttonUI[i]->isActive = false;

	IMAGEMANAGER->AddTexture(L"info", L"./Resource/MainUI/info.png");
	IMAGEMANAGER->AddTexture(L"howto", L"./Resource/MainUI/how.png");
	IMAGEMANAGER->AddTexture(L"rank", L"./Resource/MainUI/rank.png");
	IMAGEMANAGER->AddTexture(L"credit", L"./Resource/MainUI/credit.png");
}

void MainScene::Update()
{
	if (intro->isActive == false)
	{
		for (int i = 0; i < buttonUI.size(); i++)
			buttonUI[i]->isActive = true;

		intro->isActive = true;
	}
}

bool operator <(const Acount &p1, const Acount &p2)
{
	return (p1.point > p2.point);
}
void MainScene::Render()
{
	if (isInfo)
	{
		IMAGEMANAGER->DrawTexture(L"info", {640, 360});
	}
	if (isHowto)
	{
		IMAGEMANAGER->DrawTexture(L"howto", { 640, 360 });
	}
	if (isRank)
	{
		IMAGEMANAGER->DrawTexture(L"rank", { 640, 360 });

		fstream fs;

		fs.open(L"./Data/Rank.txt");

		vector<Acount> acount;
		while (!fs.eof())
		{
			string name;
			int point;
			fs >> name >> point;
			acount.push_back(Acount(name, point));
		}
		acount.pop_back();
		sort(acount.begin(), acount.end());

		for (int i = 0; i < acount.size(); i++)
		{
			IMAGEMANAGER->DrawFont(acount[i].name, {300, 150 + i * 160.0f}, 60);
			IMAGEMANAGER->DrawFont(to_string(acount[i].point), { 300 + 300, 150 + i * 160.0f }, 60);
			if (i >= 3)
				break;
		}
		fs.close();
	}
	if (isCredit)
	{
		IMAGEMANAGER->DrawTexture(L"credit", {640, 360});
	}
	if (INPUTMANAGER->KeyDown(VK_LBUTTON))
	{
		isInfo = false;
		isRank = false;
		isHowto = false;
		isCredit = false;
	}
}

void MainScene::Release()
{
	SOUNDMANAGER->Stop("MainSong");
}
