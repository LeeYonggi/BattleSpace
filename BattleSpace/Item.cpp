#include "DXUT.h"
#include "Item.h"

#include "Player.h"
#include "Effect.h"

#include "ScreenUI.h"
Item::Item(Player * player, Vector3 pos, ITEM_KINDS kind)
{
	this->player = player;
	this->pos = pos;
	this->kind = kind;
	pos.y += 2.0f;
	radius = 3.0f;
}

Item::~Item()
{
}

void Item::Init()
{
	switch (kind)
	{
	case ITEM_JUMP:
		mesh = MESHMANAGER->AddMesh("double_jump", L"./Resource/item/double_jump/double_jump.obj");
		break;
	case ITEM_SPEEDUP:
		mesh = MESHMANAGER->AddMesh("speed_up", L"./Resource/item/speed_up/speed_up.obj");
		break;
	case ITEM_LENGTHUP:
		mesh = MESHMANAGER->AddMesh("range_up", L"./Resource/item/range_up/range_up.obj");
		break;
	case ITEM_THIRD:
		mesh = MESHMANAGER->AddMesh("3_direction", L"./Resource/item/3_direction/3_direction.obj");
		break;
	case ITEM_TRAKING:
		mesh = MESHMANAGER->AddMesh("homing_missile", L"./Resource/item/homing_missile/homing_missile.obj");
		break;
	case ITEM_NUCLEAR:
		mesh = MESHMANAGER->AddMesh("nuclear", L"./Resource/item/nuclear/nuclear.obj");
		break;
	default:
		break;
	}
	scale = 0.1f;
}

void Item::Update()
{
	pos.y += sin(frame * 2) * 5 * ELTIME;

	frame += ELTIME;

	if (GetCircleCollision(pos, player->pos, radius, player->radius))
	{
		player->itemCount[kind] += 1;
		isDestroy = true;
		Texture *tex = nullptr;
		switch (kind)
		{
		case ITEM_JUMP:
			tex = IMAGEMANAGER->AddTexture(L"double_jumpUI", L"./Resource/item/item_effect/double_jump.png");
			break;
		case ITEM_SPEEDUP:
			tex = IMAGEMANAGER->AddTexture(L"speed_upUI", L"./Resource/item/item_effect/speed_up.png");
			break;
		case ITEM_LENGTHUP:
			tex = IMAGEMANAGER->AddTexture(L"range_upUI", L"./Resource/item/item_effect/range_up.png");
			break;
		case ITEM_THIRD:
			tex = IMAGEMANAGER->AddTexture(L"3_directionUI", L"./Resource/item/item_effect/3_direction.png");
			break;
		case ITEM_TRAKING:
			tex = IMAGEMANAGER->AddTexture(L"homing_missileUI", L"./Resource/item/item_effect/homing_missile.png");
			break;
		case ITEM_NUCLEAR:
			tex = IMAGEMANAGER->AddTexture(L"nuclearUI", L"./Resource/item/item_effect/nuclear.png");
			if (player->itemCount[ITEM_KINDS::ITEM_NUCLEAR] > 2)
				player->itemCount[ITEM_KINDS::ITEM_NUCLEAR] = 2;
			break;
		default:
			break;
		}

		OBJECTMANAGER->AddObject(OBJ_UI, new ScreenUI(tex, { 640, 170 }, true, { 640, 130}, 0.8f));
	}
}

void Item::Render()
{
	MESHMANAGER->DrawMesh(mesh, pos, matR, scale);
}

void Item::Release()
{
	vector<Texture*> effect = IMAGEMANAGER->AddAnimeTexture(L"DamageEffect", L"./Resource/Effect/damage_effect/%d.png", 1, 5);
	OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_EFFECT, new Effect(effect, pos, { 0, 0, 0 }, 0.7f, false, 0.0f, 10));
}
