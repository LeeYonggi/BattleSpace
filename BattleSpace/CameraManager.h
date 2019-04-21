#pragma once
#include "Singleton.h"


class CameraManager :
	public Singleton<CameraManager>
{
public:
	CameraManager();
	virtual ~CameraManager();

private:
	map<string, Camera*> m_Camera;

public:
	Camera *mainCamera = nullptr;

public:
	Camera *AddCamera(string str, Camera *camera);
	void ChangeCamera(string str);
	void CameraShake(float frame);
	void Release();
};

#define CAMERAMANAGER CameraManager::GetInstance()