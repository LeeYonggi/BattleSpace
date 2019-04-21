#pragma once
#include "Object.h"

#include "CharacterAttack.h"
#define PLAYER_SPEED 0.4f

enum PLAYER_STATE
{
	PLAYER_IDLE,
	PLAYER_MOVE,
	PLAYER_ATTACK
};

class ScreenUI;
class Background;
class Player :
	public Object
{
	using PlayerFunc = void(Player::*)(void);
public:
	Player(Background *_back);
	virtual ~Player();

private:
	bool isControl = false;
	float speed = PLAYER_SPEED;
	float velocity = 0.0f;
	float gravity = GRAVITY_BASIC;
	float groundDistance = 4.0f;

	Vector2 frontPoint = { 0, 0 };
	Vector2 backPoint = { 0, 0 };

	Background *back;

	ScreenUI *speedUpUI = nullptr;
	ScreenUI *nuclearUI = nullptr;
	ScreenUI *trakingUI = nullptr;
	ScreenUI *respawnUI = nullptr;

	bool isNuclear = false;

	CMeshLoader *speedMesh;
private:
	bool isJump = false;
	int jumpCount = 1;
	bool isDie = false;
public:
	bool isUltra = false;

public:
	PLAYER_STATE state = PLAYER_IDLE;
	PlayerFunc playerFunc[3];
	vector<CharacterAttack> playerAttack;

public:
	int itemCount[6];
	bool isSpeedUp = false;
	
private:
	float lengthFrame = 0.0f;
	float thirdFrame = 0.0f;
	float trakingFrame = 0.0f;

public:
	int hp = 1;
	int totalHp = 3;
	int upgradeGage = 0;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

public:
	Vector3 PlayerControl(bool *control);
	void PlayerRigidbody();
	void PlayerIdle();
	void PlayerMove();
	void PlayerAttack();
	void PlayerRotateToPoint();
	bool PlayePointCollision(Vector2 *p1, Texture *map);
	bool PlayerAttackCheck();
	void PlayerJump();
	void PlayerItem();
	void PlayerAttaked();
};

