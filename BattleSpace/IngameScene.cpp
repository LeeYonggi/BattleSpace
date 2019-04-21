#include "DXUT.h"
#include "IngameScene.h"

#include "ObjectCreator.h"

IngameScene::IngameScene(STAGE_KIND _stage)
{
	stage = _stage;
}


IngameScene::~IngameScene()
{
}

void IngameScene::Init()
{
	OBJECTMANAGER->AddObject(OBJ_CREATOR, new ObjectCreator(stage));
}

void IngameScene::Update()
{

}

void IngameScene::Render()
{
}

void IngameScene::Release()
{
}
