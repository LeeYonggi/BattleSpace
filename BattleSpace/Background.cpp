#include "DXUT.h"
#include "Background.h"



Background::Background(STAGE_KIND _stage)
{
	stage = _stage;
}

Background::~Background()
{
}

void Background::Init()
{
	switch (stage)
	{
	case STAGE_1:
		mesh = MESHMANAGER->AddMesh("Map1", L"./Resource/Map/map_1.obj");
		minimap1 = IMAGEMANAGER->AddTexture(L"Minimap1_1", L"./Resource/Map/MiniMap/minimap_side.png");
		minimap2 = IMAGEMANAGER->AddTexture(L"Minimap1_2", L"./Resource/Map/MiniMap/minimap_top.png");
		pos = { 0, 0, 0 };
		scale = 1;
		break;
	case STAGE_2:
		mesh = MESHMANAGER->AddMesh("Map2", L"./Resource/Map2/map_2.obj");
		minimap1 = IMAGEMANAGER->AddTexture(L"Minimap2_1", L"./Resource/Map2/MiniMap/side.png");
		minimap2 = IMAGEMANAGER->AddTexture(L"Minimap2_2", L"./Resource/Map2/MiniMap/top.png");
		pos = { 0, -3, 0 };
		break;
	default:
		break;
	}
}

void Background::Update()
{
}

void Background::Render()
{
	MESHMANAGER->DrawMesh(mesh, pos, matR, scale);
}

void Background::Release()
{
}
