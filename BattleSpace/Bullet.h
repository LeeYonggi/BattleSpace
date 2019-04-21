#pragma once
#include "Object.h"

enum BULLET_STATE
{
	BULLET_120MM,
	BULLET_88MM,
	BULLET_ENEMY
};

enum BULLET_FUNC_STATE
{
	BULLET_INIT,
	BULLET_UPDATE,
	BULLET_RENDER,
	BULLET_RELEASE
};
class Bullet :
	public Object
{
	using BulletFunc = void(Bullet::*)(BULLET_FUNC_STATE);
public:
	Bullet(BULLET_STATE _state, Vector3 _pos, Vector3 _moveVector, float _velocity, float _gravity);
	virtual ~Bullet();

private:
	BULLET_STATE state;
	BulletFunc bulletFunc[3];

	float velocity = 0.0f;
	float gravity = 0.0f;
	float speed = 1.0f;

public:
	int damage = 1;
public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

public:
	void Bullet120MM(BULLET_FUNC_STATE _state);
	void Bullet88MM(BULLET_FUNC_STATE _state);
	void BulletEnemy(BULLET_FUNC_STATE _state);

};

