#pragma once

enum BULLET_STATE;
class CharacterAttack
{
public:
	CharacterAttack();
	virtual ~CharacterAttack();

public:
	float delay = 0.0f;
	float frame = 0.0f;
	bool isAttack = false;

public:
	void AttackUpdate();
	void Attack(OBJ_KINDS objKind, BULLET_STATE bulletState, Vector3 pos, Vector3 moveVector, float delay, float velocity, float gravity);
};

