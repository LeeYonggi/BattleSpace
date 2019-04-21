#include "DXUT.h"
#include "CameraManager.h"


CameraManager::CameraManager()
{
}


CameraManager::~CameraManager()
{
	Release();
}

Camera * CameraManager::AddCamera(string str, Camera * camera)
{
	auto iter = m_Camera.find(str);
	if (iter != m_Camera.end()) return iter->second;

	m_Camera.insert(make_pair(str, camera));
	camera->isActive = false;
	return camera;
}

void CameraManager::ChangeCamera(string str)
{
	auto iter = m_Camera.find(str);
	if (iter == m_Camera.end()) return;

	if (mainCamera)
	{
		Vector3 eye = mainCamera->eye;
		Vector3 at = mainCamera->at;

		iter->second->eye = eye;
		iter->second->at = at;
		mainCamera->isActive = false;
	}
	mainCamera = iter->second;
	mainCamera->Init();
	mainCamera->isActive = true;
}

void CameraManager::CameraShake(float frame)
{
	mainCamera->shakeFrame = frame;
}

void CameraManager::Release()
{
	m_Camera.clear();
	mainCamera = nullptr;
}
