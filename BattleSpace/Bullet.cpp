#include "DXUT.h"
#include "Bullet.h"

#include "Background.h"
#include "Particle.h"
#include "Effect.h"


Bullet::Bullet(BULLET_STATE _state, Vector3 _pos, Vector3 _moveVector, float _velocity, float _gravity)
	: state(_state)
{
	pos = _pos;
	moveVector = _moveVector;
	velocity = _velocity;
	gravity = _gravity;
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	bulletFunc[BULLET_120MM] = &Bullet::Bullet120MM;
	bulletFunc[BULLET_88MM] = &Bullet::Bullet88MM;
	bulletFunc[BULLET_ENEMY] = &Bullet::BulletEnemy;

	(this->*bulletFunc[state])(BULLET_INIT);
}

void Bullet::Update()
{
	(this->*bulletFunc[state])(BULLET_UPDATE);
	auto iter = OBJECTMANAGER->GetObjectList(OBJ_BACKGROUND);
	Background *back = (Background*)(*iter->begin());
	if (GetPixelCollision(Vector2(pos.x, pos.y) * 5, back->minimap1) ||
		pos.x < -100 || pos.x > 1100 || pos.z > 300 || pos.z < -300 || pos.y > 100 || pos.y < -400)
	{
		isDestroy = true;
	}
}

void Bullet::Render()
{
	(this->*bulletFunc[state])(BULLET_RENDER);
}

void Bullet::Release()
{
	(this->*bulletFunc[state])(BULLET_RELEASE);
}

void Bullet::Bullet120MM(BULLET_FUNC_STATE _state)
{
	switch (_state)
	{
	case BULLET_INIT:
	{
		mesh = MESHMANAGER->AddMesh("120MM", L"./Resource/Bullet/120MM/120mm.obj");
		speed = 50.0f;
		D3DXMatrixLookAtLH(&matR, &Vector3(0, 0, 0), &moveVector, &Vector3(0, 1, 0));
		D3DXMatrixTranspose(&matR, &matR);

		scale = 0.04;
		damage = 250;

		vector<Texture*> vTexture = IMAGEMANAGER->AddAnimeTexture(L"dust", L"./Resource/Effect/dust/%d.png", 1, 5);
		vParticle.push_back(OBJECTMANAGER->AddObject(OBJ_EFFECT, new Particle(vTexture, 0.05f)));

		radius = 3.0f;
	}
		break;
	case BULLET_UPDATE:
	{
		Vector3 pastPos = pos;
		velocity -= gravity;
		pos += moveVector * ELTIME * speed;
		pos.y += velocity;

		Vector3 temp = pos - pastPos;
		D3DXMatrixLookAtLH(&matR, &Vector3(0, 0, 0), &temp, &Vector3(0, 1, 0));
		D3DXMatrixTranspose(&matR, &matR);

		float n = GetRandomNumber(30, 80);
		vParticle[0]->ParticleInit(pos, -temp * 4, n * 0.001f, false, 0.0f, 12.0f); //RandÇØ
	}
		break;
	case BULLET_RENDER:
		MESHMANAGER->DrawMesh(mesh, pos, matR, scale);
		break;
	case BULLET_RELEASE:
	{
		vector<Texture*> effect = IMAGEMANAGER->AddAnimeTexture(L"Bomb", L"./Resource/Effect/bomb/%d.png", 1, 6);
		OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_EFFECT, new Effect(effect, pos, { 0, 0, 0 }, 0.3f, false, 0.0f, 10));
		vParticle[0]->isActive = false;
	}
		break;
	default:
		break;
	}
}

void Bullet::Bullet88MM(BULLET_FUNC_STATE _state)
{
	switch (_state)
	{
	case BULLET_INIT:
		mesh = MESHMANAGER->AddMesh("plane", L"./Resource/Effect/plane/plane.obj");
		texture = IMAGEMANAGER->AddTexture(L"88MM", L"./Resource/Bullet/88MM/attack.png");

		speed = 70.0f;
		scale = 0.025f;
		damage = 50;

		break;
	case BULLET_UPDATE:
		pos += moveVector * speed * ELTIME;
		break;
	case BULLET_RENDER:
		matR = GetBillboardToCamera(pos, CAMERAMANAGER->mainCamera->eye);
		MESHMANAGER->DrawEffect(mesh, texture, pos, matR, scale);
		break;
	case BULLET_RELEASE:
	{
		vector<Texture*> effect = IMAGEMANAGER->AddAnimeTexture(L"DamageEffect", L"./Resource/Effect/damage_effect/%d.png", 1, 5);
		OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_EFFECT, new Effect(effect, pos, { 0, 0, 0 }, 0.1f, false, 0.0f, 10));
	}
		break;
	default:
		break;
	}
}

void Bullet::BulletEnemy(BULLET_FUNC_STATE _state)
{
	switch (_state)
	{
	case BULLET_INIT:
		animeMesh.push_back(MESHMANAGER->AddAnimeMesh("EnemyBullet", L"./Resource/Bullet/enemy_attack/model%d.obj", 0, 10));

		speed = 20;

		scale = 0.05f;
		break;
	case BULLET_UPDATE:
	{
		auto iter = OBJECTMANAGER->GetObjectList(OBJ_KINDS::OBJ_PBULLET);

		for (auto obj = iter->begin(); obj != iter->end(); obj++)
		{
			if (((Bullet*)(*obj))->state == BULLET_120MM && GetCircleCollision((*obj)->pos, pos, (*obj)->radius, radius))
			{
				(*obj)->isDestroy = true;
				isDestroy = true;
			}
		}
		pos += moveVector * ELTIME * speed;
	}
		break;
	case BULLET_RENDER:
	{
		int count = int(frame * 12) % animeMesh[0].size();
		MESHMANAGER->DrawAlphaMesh(animeMesh[0][count], pos, matR, scale);
	}
		break;
	case BULLET_RELEASE:
	{
		vector<Texture*> effect = IMAGEMANAGER->AddAnimeTexture(L"DamageEffect", L"./Resource/Effect/damage_effect/%d.png", 1, 5);
		OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_EFFECT, new Effect(effect, pos, { 0, 0, 0 }, 0.2f, false, 0.0f, 10));
	}
		break;
	default:
		break;
	}
}
