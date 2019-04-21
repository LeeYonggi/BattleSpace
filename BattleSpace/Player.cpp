#include "DXUT.h"
#include "Player.h"

#include "Background.h"
#include "Bullet.h"
#include "Particle.h"
#include "Item.h"
#include "Enemy.h"
#include "PlayerUI.h"
#include "ScreenUI.h"
#include "Effect.h"
#include "SavePoint.h"
#include "Ending.h"


Player::Player(Background *_back)
	: back(_back)
{
}


Player::~Player()
{
}

void Player::Init()
{
	mesh = MESHMANAGER->AddMesh("Player", L"./Resource/Player/player_idle/model0.obj");
	animeMesh.push_back(MESHMANAGER->AddAnimeMesh("Player_Idle", L"./Resource/Player/player_idle/model%d.obj", 0, ANIME_FRAME));
	animeMesh.push_back(MESHMANAGER->AddAnimeMesh("Player_Move", L"./Resource/Player/player_move/model%d.obj", 0, ANIME_FRAME));
	animeMesh.push_back(MESHMANAGER->AddAnimeMesh("Player_Move", L"./Resource/Player/player_move/model%d.obj", 0, ANIME_FRAME));
	animeMesh.push_back(MESHMANAGER->AddAnimeMesh("Player_Idle2", L"./Resource/Player/player_upgrade_1_idle/model%d.obj", 0, ANIME_FRAME));
	animeMesh.push_back(MESHMANAGER->AddAnimeMesh("Player_Move2", L"./Resource/Player/player_upgrade_1_move/model%d.obj", 0, ANIME_FRAME));
	animeMesh.push_back(MESHMANAGER->AddAnimeMesh("Player_Move2", L"./Resource/Player/player_upgrade_1_move/model%d.obj", 0, ANIME_FRAME));
	animeMesh.push_back(MESHMANAGER->AddAnimeMesh("Player_Idle3", L"./Resource/Player/player_upgrade_2_idle/model%d.obj", 0, ANIME_FRAME));
	animeMesh.push_back(MESHMANAGER->AddAnimeMesh("Player_Move3", L"./Resource/Player/player_upgarde_2_move/model%d.obj", 0, ANIME_FRAME));
	animeMesh.push_back(MESHMANAGER->AddAnimeMesh("Player_Move3", L"./Resource/Player/player_upgarde_2_move/model%d.obj", 0, ANIME_FRAME));

	pos = { 10, groundDistance, -5 }; 
	scale = 0.02f;

	playerFunc[PLAYER_IDLE] = &Player::PlayerIdle;
	playerFunc[PLAYER_MOVE] = &Player::PlayerMove;
	playerFunc[PLAYER_ATTACK] = &Player::PlayerAttack;

	vector<Texture*> temp = IMAGEMANAGER->AddAnimeTexture(L"dust", L"./Resource/Effect/dust/%d.png", 1, 5);
	vParticle.push_back(OBJECTMANAGER->AddObject(OBJ_EFFECT, new Particle(temp, 0.06f)));
	vParticle[0]->isActive = false;

	for (int i = 0; i < 6; i++)
		itemCount[i] = 1;
	radius = 2.0f;

	for(int i = 0; i < 3; i++)
		playerAttack.push_back(CharacterAttack());

	OBJECTMANAGER->AddObject(OBJ_UI, new PlayerUI(this, back->stage));

	temp = IMAGEMANAGER->AddAnimeTexture(L"speed_up_effect", L"./Resource/Effect/speed_up_effect/%d.png", 1, 4);
	speedUpUI = OBJECTMANAGER->AddObject(OBJ_BACKUI, new ScreenUI(temp, {640, 360}, true, true, 9.0f));
	speedUpUI->isActive = false;

	temp = IMAGEMANAGER->AddAnimeTexture(L"Nuclear", L"./Resource/Effect/nuclear_effect/nuclear%04d.jpg", 0, 70);
	nuclearUI = OBJECTMANAGER->AddObject(OBJ_FRONTUI, new ScreenUI(temp, {640, 360}, false, false, 0.3f));
	nuclearUI->isActive = false;

	temp = IMAGEMANAGER->AddAnimeTexture(L"trakingUI", L"./Resource/UI/traking.png", 0, 0);
	trakingUI = OBJECTMANAGER->AddObject(OBJ_BACKUI, new ScreenUI(temp, { 640, 360 }, true, true, 0.0f));
	trakingUI->isActive = false;

	temp = IMAGEMANAGER->AddAnimeTexture(L"respawn", L"./Resource/respawn/%d.png", 1, 3);
	respawnUI = OBJECTMANAGER->AddObject(OBJ_FRONTUI, new ScreenUI(temp, {640, 360}, false, true, 1.0f));
	respawnUI->isActive = false;
	
	speedMesh = MESHMANAGER->AddMesh("speed_upModel", L"./Resource/Effect/speed_up/speed_up.obj");
	isUltra = false;
}

void Player::Update()
{
	isControl = false;
	if (respawnUI->isActive == false && isDie == true)
	{
		isDie = false;
		pos = DATAMANAGER->savePoint;
		hp = 1;
		if (totalHp < 1)
			SCENEMANAGER->AddScene(new Ending(false));
	}
	if (isDie == true) return;
	PlayerRigidbody();
	if (hp == 3)
		trakingFrame = frame + 1.0f;
	if (upgradeGage >= 5 && hp < 3)
	{
		hp++;
		upgradeGage = 0;
	}
	PlayerAttackCheck();
	PlayerItem();
	PlayerJump();
	PlayerAttaked();
	(this->*playerFunc[state])();
	RotateLerp({ 0, 0, 0 }, moveVector, &matR);

	if (INPUTMANAGER->KeyDown(VK_F1))
	{
		isUltra = true;
	}
	if (INPUTMANAGER->KeyDown(VK_F2))
	{
		if (hp < 3)
			hp++;
	}
	if (INPUTMANAGER->KeyDown(VK_F3))
	{
		if (hp > 1)
			hp--;
	}

	frame += ELTIME;
}

void Player::Render()
{
	int count = int(frame * 12) % animeMesh[state + (max(hp, 1) - 1) * 3].size();
	MESHMANAGER->DrawMesh(animeMesh[state + (max(hp, 1) - 1) * 3][count], pos, matR, scale);
	if (isSpeedUp == true)
		MESHMANAGER->DrawAlphaMesh(speedMesh, pos, matR, scale);
}

void Player::Release()
{
}

Vector3 Player::PlayerControl(bool * control)
{
	Vector3 temp = { 0, 0, 0 };

	if (INPUTMANAGER->KeyPress(VK_LEFT))
	{
		temp.x += -1;
		*control = true;
	}
	if (INPUTMANAGER->KeyPress(VK_RIGHT))
	{
		temp.x += 1;
		*control = true;
	}
	if (INPUTMANAGER->KeyPress(VK_UP))
	{
		temp.z += 1;
		*control = true;
	}
	if (INPUTMANAGER->KeyPress(VK_DOWN))
	{
		temp.z += -1;
		*control = true;
	}

	return temp;
}

void Player::PlayerRigidbody()
{
	Vector3 temp = PlayerControl(&isControl);
	velocity -= gravity;
	if (isControl)
	{
		moveVector = temp;

		PlayerRotateToPoint();

		pos += moveVector * speed;
	}

	Vector2 groundCheck = {pos.x, pos.y - groundDistance};
	Vector2 topCheck = {pos.x, pos.z};
	if (PlayePointCollision(&groundCheck, back->minimap1) && GetPixelCollision(topCheck, back->minimap2))
	{
		pos.y = groundCheck.y + groundDistance;
		velocity = 0;
		if (isJump)
		{
			isJump = false;
			jumpCount++;
		}
	}
	pos.y += velocity;
}

void Player::PlayerIdle()
{
	if (isControl == true)
		state = PLAYER_MOVE;
}

void Player::PlayerMove()
{
	float n = GetRandomNumber(20, 40);
	vParticle[0]->ParticleInit({pos.x, pos.y - groundDistance + 0.7f, pos.z}, -moveVector * n * 0.1f, n * 0.001, false, 0.0f, 12);
	vParticle[0]->isActive = true;
	if (isControl == false)
	{
		state = PLAYER_IDLE;
		vParticle[0]->isActive = false;
	}
}

void Player::PlayerAttack()
{
	if (playerAttack[0].isAttack == false)
		state = PLAYER_IDLE;
	for(int i = 0; i < playerAttack.size(); i++)
		playerAttack[i].AttackUpdate();
}

void Player::PlayerRotateToPoint()
{
	frontPoint.x = pos.x + moveVector.x * 2;
	frontPoint.y = pos.y - groundDistance;

	backPoint.x = pos.x - moveVector.x * 2;
	backPoint.y = pos.y - groundDistance;

	PlayePointCollision(&frontPoint, back->minimap1);
	PlayePointCollision(&backPoint, back->minimap1);

	Vector2 temp = GetTargetVec2(backPoint, frontPoint);
	moveVector.x = temp.x;
	moveVector.y = temp.y;
}

bool Player::PlayePointCollision(Vector2 *p1, Texture *map)
{
	if (GetPixelCollision(*p1 * 5, map))
	{
		while (true)
		{
			if (GetPixelCollision(*p1 * 5, map))
				p1->y += 0.2f;
			else
			{
				p1->y -= 0.2f;
				return true;
			}
		}
	}
	else
	{
		for (int i = 0; i < 30; i++)
		{
			if (GetPixelCollision(*p1 * 5, map))
			{
				break;
			}
			else
			{
				p1->y -= 0.2f;
			}
		}
	}
	return false;
}

bool Player::PlayerAttackCheck()
{
	float bulletGravity = GRAVITY_BASIC + 0.02f;
	float bulletVelocity = 0.8f;
	if (lengthFrame > frame)
	{
		bulletVelocity = 1.2f;
	}
	if (INPUTMANAGER->KeyDown('Q'))
	{
		state = PLAYER_ATTACK;
		if(trakingFrame < frame)
			playerAttack[0].Attack(OBJ_KINDS::OBJ_PBULLET, BULLET_STATE::BULLET_120MM, pos, moveVector, 0.6f, bulletVelocity, bulletGravity);
		else
		{
			auto iter = OBJECTMANAGER->GetObjectList(OBJ_ENEMY);
			Enemy *target = nullptr;
			for (auto enemy = iter->begin(); enemy != iter->end(); enemy++)
			{
				Enemy *temp = (Enemy*)(*enemy);
				if (temp->IsInScreen())
				{
					target = temp;
					break;
				}
			}
			if (target)
			{
				Vector3 targetVec3 = GetTargetVec3(pos, target->pos);
				playerAttack[0].Attack(OBJ_KINDS::OBJ_PBULLET, BULLET_STATE::BULLET_120MM, pos, targetVec3, 0.6f, 0, 0);
			}
		}
		if (thirdFrame > frame)
		{
			playerAttack[1].Attack(OBJ_KINDS::OBJ_PBULLET, BULLET_STATE::BULLET_120MM, pos, moveVector, 0.6f, bulletVelocity + 0.5f, bulletGravity);
			playerAttack[2].Attack(OBJ_KINDS::OBJ_PBULLET, BULLET_STATE::BULLET_120MM, pos, moveVector, 0.6f, bulletVelocity + 1.0f, bulletGravity);
		}
		return true;
	}
	return false;
}

void Player::PlayerJump()
{
	if (INPUTMANAGER->KeyDown(VK_SPACE) && jumpCount > 0)
	{
		if (isJump == true && hp == 3)
			return;
		pos.y += 0.3f;
		velocity = 0.7f;
		jumpCount -= 1;
		isJump = true;
	}
}

void Player::PlayerItem()
{
	if (INPUTMANAGER->KeyDown('1') && itemCount[ITEM_KINDS::ITEM_JUMP])
	{
		jumpCount++;
		itemCount[ITEM_KINDS::ITEM_JUMP] -= 1;
	}
	if (INPUTMANAGER->KeyDown('2') && itemCount[ITEM_KINDS::ITEM_SPEEDUP])
	{
		isSpeedUp = true;
		speed = PLAYER_SPEED * 1.5f;
		speedUpUI->isActive = true;
		itemCount[ITEM_KINDS::ITEM_SPEEDUP] -= 1;
	}
	if (INPUTMANAGER->KeyDown('3') && itemCount[ITEM_KINDS::ITEM_LENGTHUP])
	{
		lengthFrame = frame + 8.0f;
		itemCount[ITEM_KINDS::ITEM_LENGTHUP] -= 1;
	}
	if (INPUTMANAGER->KeyDown('4') && itemCount[ITEM_KINDS::ITEM_THIRD])
	{
		thirdFrame = frame + 8.0f;
		itemCount[ITEM_KINDS::ITEM_THIRD] -= 1;
	}
	if (INPUTMANAGER->KeyDown('5') && itemCount[ITEM_KINDS::ITEM_TRAKING])
	{
		trakingFrame = frame + 8.0f;

		itemCount[ITEM_KINDS::ITEM_TRAKING] -= 1;
	}
	if (INPUTMANAGER->KeyDown('6') && itemCount[ITEM_KINDS::ITEM_NUCLEAR])
	{
		nuclearUI->isActive = true;
		auto iter = OBJECTMANAGER->GetObjectList(OBJ_ENEMY);
		for (auto obj = iter->begin(); obj != iter->end(); obj++)
		{
			Enemy *enemy = (Enemy*)(*obj);
			if (enemy->IsInScreen())
			{
				enemy->hp = 0;
			}
		}
		timeScale = 0;
		itemCount[ITEM_KINDS::ITEM_NUCLEAR] -= 1;
		isNuclear = true;
	}
	if (isNuclear == true && nuclearUI->isActive == false)
	{
		timeScale = 1.0f;
		isNuclear = false;
	}
	if (trakingFrame > frame)
	{
		trakingUI->isActive = true;
		trakingUI->scale = Lerp(trakingUI->scale, 1.0f, 0.05f);
	}
	else
	{
		trakingUI->isActive = false;
		trakingUI->scale = 0.5f;
	}
}

void Player::PlayerAttaked()
{
	if (!isUltra)
	{
		auto iter = OBJECTMANAGER->GetObjectList(OBJ_KINDS::OBJ_EBULLET);
		for (auto obj = iter->begin(); obj != iter->end(); obj++)
		{
			if (GetCircleCollision(pos, (*obj)->pos, radius, (*obj)->radius))
			{
				(*obj)->isDestroy = true;
				hp -= 1;
			}
		}
	}
	switch (back->stage)
	{
	case STAGE_1:
		if (pos.x < 280 && pos.y < -17)
		{
			hp = 0;
		}
		else if(pos.y < -250)
		{
			hp = 0;
		}
		break;
	case STAGE_2:
		if (pos.x < 280 && pos.y < -15)
		{
			hp = 0;
		}
		else if (pos.y < -97)
		{
			hp = 0;
		}
		break;
	default:
		break;
	}

	if (hp < 1)
	{
		vector<Texture*> effect = IMAGEMANAGER->AddAnimeTexture(L"Bomb", L"./Resource/Effect/bomb/%d.png", 1, 6);
		OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_EFFECT, new Effect(effect, pos, { 0, 0, 0 }, 0.7f, false, 0.0f, 10));
		isDie = true;
		isSpeedUp = false;
		speedUpUI->isActive = false;
		speed = PLAYER_SPEED;
		respawnUI->isActive = true;
		totalHp -= 1;
	}
}

