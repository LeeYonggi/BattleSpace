#include "DXUT.h"
#include "CharacterAttack.h"

#include "Bullet.h"

CharacterAttack::CharacterAttack()
{
}


CharacterAttack::~CharacterAttack()
{
}

void CharacterAttack::AttackUpdate()
{
	if (isAttack)
	{
		frame += ELTIME;
		if (frame > delay)
		{
			frame = 0;
			isAttack = false;
		}
	}
}

void CharacterAttack::Attack(OBJ_KINDS objKind, BULLET_STATE bulletState, Vector3 pos, Vector3 moveVector, float delay, float velocity, float gravity)
{
	if (isAttack) return;

	isAttack = true;
	OBJECTMANAGER->AddObject(objKind, new Bullet(bulletState, pos, moveVector, velocity, gravity));
	this->delay = delay;
}
