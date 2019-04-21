#pragma once
#include "Singleton.h"
class SceneManager :
	public Singleton<SceneManager>
{
public:
	SceneManager();
	virtual ~SceneManager();

private:
	Scene *nowScene		= nullptr;
	Scene *nextScene	= nullptr;
	bool isSceneChage	= false;

public:
	void AddScene(Scene *scene);
	void Update();
	void Render();
	void Release();

};

#define SCENEMANAGER SceneManager::GetInstance()