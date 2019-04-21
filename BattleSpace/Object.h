#pragma once

#define GRAVITY_BASIC 0.02f
class Particle;
class Object
{
public:
	Object();
	virtual ~Object();

public:
	Vector3 pos = { 0, 0, 0 };
	float scale = 1.0f;
	Matrix matR;
	D3DXQUATERNION quaternion;
	bool isDestroy = false;
	bool isActive = true;
	float frame = 0.0f;
	float radius = 1.0f;
	Vector3 moveVector = { 1, 0, 0 };

protected:
	vector<vector<Texture*>> animeTexture;
	vector<vector<CMeshLoader*>> animeMesh;
	vector<Particle*> vParticle;
	CMeshLoader *mesh = nullptr;
	Texture *texture = nullptr;

public:
	virtual void Init()		PURE;
	virtual void Update()	PURE;
	virtual void Render()	PURE;
	virtual void Release()	PURE;

public:
	void RotateLerp(Vector3 eye, Vector3 at, Matrix *mat);
	bool GetPixelCollision(Vector2 p1, Texture *tex);
	Vector3 GetTargetVec3(Vector3 p1, Vector3 p2);
	Vector2 GetTargetVec2(Vector2 p1, Vector2 p2);
	Matrix GetBillboardToCamera(Vector3 p1, Vector3 camera);
	bool GetCircleCollision(Vector3 p1, Vector3 p2, float r1, float r2);
	float GetDistance(Vector3 p1, Vector3 p2);

};

