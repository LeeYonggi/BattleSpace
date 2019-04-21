#include "DXUT.h"
#include "Camera.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::Init()
{
}

void Camera::Update()
{
	if (shakeFrame > 0)
	{
		eye.x += GetRandomNumber(-20, 20) * 0.1f;
		eye.y += GetRandomNumber(-20, 20) * 0.1f;
		eye.z += GetRandomNumber(-20, 20) * 0.1f;
		shakeFrame -= ELTIME;
	}
}

void Camera::Render()
{
	Matrix mat, proj;
	D3DXMatrixLookAtLH(&mat, &eye, &at, &up);

	DEVICE->SetTransform(D3DTS_VIEW, &mat);
	D3DXMatrixPerspectiveFovLH(&proj, D3DXToRadian(60), (float)SCREEN_X / (float)SCREEN_Y, 1, 1000000.0f);
	DEVICE->SetTransform(D3DTS_PROJECTION, &proj);
}

void Camera::Release()
{
}
