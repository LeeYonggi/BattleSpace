#include "DXUT.h"
#include "SceneManager.h"


SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

void SceneManager::AddScene(Scene * scene)
{
	nextScene = scene;
	isSceneChage = true;
}

void SceneManager::Update()
{
	if (isSceneChage)
	{
		if (nowScene)
		{
			SAFE_RELEASE(nowScene);
			SAFE_DELETE(nowScene);
			OBJECTMANAGER->Release();
			OBJECTMANAGER->Init();
		}
		nowScene = nextScene;
		nextScene = nullptr;
		nowScene->Init();
		isSceneChage = false;
	}
	if (nowScene)
		nowScene->Update();
}

void SceneManager::Render()
{
	if (nowScene)
		nowScene->Render();
}

void SceneManager::Release()
{
	SAFE_RELEASE(nowScene);
	SAFE_DELETE(nowScene);
	SAFE_RELEASE(nextScene);
	SAFE_DELETE(nextScene);
}
