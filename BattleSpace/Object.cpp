#include "DXUT.h"
#include "Object.h"

#include "Particle.h"

Object::Object()
{
	D3DXMatrixIdentity(&matR);
	D3DXQuaternionIdentity(&quaternion);
}


Object::~Object()
{
	animeTexture.clear();
	animeMesh.clear();
	for (auto iter : vParticle)
		iter->isDestroy = true;
	vParticle.clear();
}

void Object::RotateLerp(Vector3 eye, Vector3 at, Matrix * mat)
{
	Matrix tempMat;
	D3DXMatrixLookAtLH(&tempMat, &eye, &at, &Vector3(0, 1, 0));
	D3DXMatrixTranspose(&tempMat, &tempMat);

	D3DXQUATERNION tempQuater;
	D3DXQuaternionRotationMatrix(&tempQuater, &tempMat);
	D3DXQuaternionSlerp(&quaternion, &quaternion, &tempQuater, 0.1f);
	D3DXMatrixRotationQuaternion(mat, &quaternion);
}

bool Object::GetPixelCollision(Vector2 p1, Texture * tex)
{
	bool isCollision = false;

	D3DLOCKED_RECT lockRect;
	tex->tex->LockRect(0, &lockRect, nullptr, D3DLOCK_DISCARD);

	int x = p1.x;
	int y = (tex->info.Height * 0.5f) - p1.y;

	if (x < 0 || x > tex->info.Width ||
		y < 0 || y > tex->info.Height)
	{
		tex->tex->UnlockRect(0);
		return false;
	}

	DWORD *color = (DWORD*)lockRect.pBits;

	if (color[(tex->info.Width * y) + x] == D3DXCOLOR(1, 0, 1, 1))
	{
		isCollision = true;
	}

	tex->tex->UnlockRect(0);
	return isCollision;
}

Vector3 Object::GetTargetVec3(Vector3 p1, Vector3 p2)
{
	Vector3 temp = p2 - p1;
	D3DXVec3Normalize(&temp, &temp);
	return temp;
}

Vector2 Object::GetTargetVec2(Vector2 p1, Vector2 p2)
{
	Vector2 temp = p2 - p1;
	D3DXVec2Normalize(&temp, &temp);
	return temp;
}

Matrix Object::GetBillboardToCamera(Vector3 p1, Vector3 camera)
{
	Matrix mat, tempMatRotate;
	Vector3 temp = camera - p1;
	D3DXVec3Normalize(&temp, &temp);
	D3DXMatrixLookAtLH(&mat, &Vector3(0, 0, 0), &temp, &Vector3(0, 1, 0));
	D3DXMatrixTranspose(&mat, &mat);
	D3DXMatrixRotationX(&tempMatRotate, D3DXToRadian(90));
	tempMatRotate *= mat;
	return tempMatRotate;
}

bool Object::GetCircleCollision(Vector3 p1, Vector3 p2, float r1, float r2)
{
	Vector3 temp = p2 - p1;
	float length = temp.x * temp.x + temp.y * temp.y;
	float d = length + temp.z * temp.z;
	return (sqrt(d) < r1 + r2);
}

float Object::GetDistance(Vector3 p1, Vector3 p2)
{
	Vector3 temp = p2 - p1;
	float length = temp.x * temp.x + temp.y * temp.y;
	float d = length + temp.z * temp.z;
	return sqrt(d);
}
