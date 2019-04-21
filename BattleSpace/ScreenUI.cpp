#include "DXUT.h"
#include "ScreenUI.h"




ScreenUI::ScreenUI(vector<Texture*> vTexture, Vector2 pos, bool isLoop, bool isElaps, float animeFrame)
{
	animeTexture.push_back(vTexture);
	uiPos = pos;
	this->isLoop = isLoop;
	this->isElaps = isElaps;
	this->animeFrame = animeFrame;
}

ScreenUI::ScreenUI(Texture * tex, Vector2 pos, bool isLerp, Vector2 direction, float endTime)
{
	texture = tex;
	uiPos = pos;
	this->isLerp = isLerp;
	this->direction = direction;
	isElaps = true;
	this->endTime = endTime;
}

ScreenUI::~ScreenUI()
{
}

void ScreenUI::Init()
{

}

void ScreenUI::Update()
{
	if (isElaps)
	{
		frame += DXUTGetElapsedTime();
	}
	else
	{
		frame += animeFrame;
	}

	if (isElaps && isLerp == false)
	{
		if (frame * animeFrame >= animeTexture[0].size())
		{
			if (isLoop)
			{
				frame = 0;
			}
			else
			{
				isActive = false;
				frame = 0;
			}
		}
	}
	else if(isLerp == false)
	{
		if (frame >= animeTexture[0].size())
		{
			if (isLoop)
			{
				frame = 0;
			}
			else
			{
				isActive = false;
				frame = 0;
			}
		}
	}

	if (isLerp)
	{
		uiPos = Lerp(uiPos, direction, 0.05f);
		if (frame > endTime)
		{
			isDestroy = true;
		}
	}

}

void ScreenUI::Render()
{
	if(isLerp)
		IMAGEMANAGER->DrawTexture(texture, uiPos);
	else
	{
		if (isElaps)
		{
			int count = int(frame * animeFrame) % animeTexture[0].size();
			IMAGEMANAGER->DrawTexture(animeTexture[0][count], uiPos, 0, scale);
		}
		else
			IMAGEMANAGER->DrawTexture(animeTexture[0][(int)frame], uiPos, 0, scale);
	}
}

void ScreenUI::Release()
{
}
