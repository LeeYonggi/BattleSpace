#include "DXUT.h"
#include "LoadScene.h"

#include "MainScene.h"

LoadScene::LoadScene()
{
}


LoadScene::~LoadScene()
{
}

void LoadScene::Init()
{
	texture = IMAGEMANAGER->AddAnimeTexture(L"Loading", L"./Resource/loading/%d.png", 1, 10);
	loadingThread = thread([&]() { Loading(); });
}

void LoadScene::Loading()
{
	//Loading
	IMAGEMANAGER->AddAnimeTexture(L"Intro", L"./Resource/intro/intro%04d.jpg", 0, 100);

	//Player
	MESHMANAGER->AddAnimeMesh("Player_Idle", L"./Resource/Player/player_idle/model%d.obj", 0, ANIME_FRAME);
	MESHMANAGER->AddAnimeMesh("Player_Move", L"./Resource/Player/player_move/model%d.obj", 0, ANIME_FRAME);
	MESHMANAGER->AddAnimeMesh("Player_Arm_Idle", L"./Resource/Player/player_arm/model%d.obj", 0, ANIME_FRAME);
	MESHMANAGER->AddAnimeMesh("Player_Arm_Attack", L"./Resource/Player/player_shooting/model%d.obj", 0, ANIME_FRAME);
	MESHMANAGER->AddAnimeMesh("Player_Idle2", L"./Resource/Player/player_upgrade_1_idle/model%d.obj", 0, ANIME_FRAME);
	MESHMANAGER->AddAnimeMesh("Player_Move2", L"./Resource/Player/player_upgrade_1_move/model%d.obj", 0, ANIME_FRAME);
	MESHMANAGER->AddAnimeMesh("Player_Move2", L"./Resource/Player/player_upgrade_1_move/model%d.obj", 0, ANIME_FRAME);
	MESHMANAGER->AddAnimeMesh("Player_Idle3", L"./Resource/Player/player_upgrade_2_idle/model%d.obj", 0, ANIME_FRAME);
	MESHMANAGER->AddAnimeMesh("Player_Move3", L"./Resource/Player/player_upgarde_2_move/model%d.obj", 0, ANIME_FRAME);
	MESHMANAGER->AddAnimeMesh("Player_Move3", L"./Resource/Player/player_upgarde_2_move/model%d.obj", 0, ANIME_FRAME);

	//Ground
	MESHMANAGER->AddMesh("Map1", L"./Resource/Map/map_1.obj");
	MESHMANAGER->AddMesh("Map2", L"./Resource/Map2/map_2.obj");
	IMAGEMANAGER->AddTexture(L"Minimap1_1", L"./Resource/Map/MiniMap/minimap_side.png");
	IMAGEMANAGER->AddTexture(L"Minimap1_2", L"./Resource/Map/MiniMap/minimap_top.png");
	IMAGEMANAGER->AddTexture(L"Minimap2_1", L"./Resource/Map2/MiniMap/side.png");
	IMAGEMANAGER->AddTexture(L"Minimap2_2", L"./Resource/Map2/MiniMap/top.png");

	//Bullet
	MESHMANAGER->AddMesh("120MM", L"./Resource/Bullet/120MM/120mm.obj");
	IMAGEMANAGER->AddTexture(L"88MM", L"./Resource/Bullet/88MM/attack.png");
	MESHMANAGER->AddAnimeMesh("EnemyBullet", L"./Resource/Bullet/enemy_attack/model%d.obj", 0, 10);

	//Effect
	MESHMANAGER->AddMesh("plane", L"./Resource/Effect/plane/plane.obj");
	IMAGEMANAGER->AddAnimeTexture(L"dust", L"./Resource/Effect/dust/%d.png", 1, 5);
	IMAGEMANAGER->AddAnimeTexture(L"DamageEffect", L"./Resource/Effect/damage_effect/%d.png", 1, 5);
	IMAGEMANAGER->AddAnimeTexture(L"Bomb", L"./Resource/Effect/bomb/%d.png", 1, 6);
	MESHMANAGER->AddMesh("speed_upModel", L"./Resource/Effect/speed_up/speed_up.obj");

	//Enemy
	MESHMANAGER->AddMesh("Enemy1", L"./Resource/Enemy/enemy_1/enemy_1.obj");
	MESHMANAGER->AddAnimeMesh("stone", L"./Resource/Enemy/stone/model%d.obj", 0, 10);
	MESHMANAGER->AddMesh("Enemy2", L"./Resource/Enemy/enemy_2/enemy_2.obj");
	MESHMANAGER->AddMesh("Enemy1_2", L"./Resource/Enemy/enemy_1_2/enemy_1.obj");
	MESHMANAGER->AddMesh("Enemy2_2", L"./Resource/Enemy/enemy_2_2/enemy_2.obj");

	//item
	MESHMANAGER->AddMesh("double_jump", L"./Resource/item/double_jump/double_jump.obj");
	IMAGEMANAGER->AddAnimeTexture(L"Nuclear", L"./Resource/Effect/nuclear_effect/nuclear%04d.jpg", 0, 70);

	//UI
	IMAGEMANAGER->AddTexture(L"InGameUI", L"./Resource/UI/ingame_UI.png");
	IMAGEMANAGER->AddTexture(L"Life", L"./Resource/UI/life.png");
	IMAGEMANAGER->AddAnimeTexture(L"speed_up_effect", L"./Resource/Effect/speed_up_effect/%d.png", 1, 4);
	IMAGEMANAGER->AddTexture(L"trakingUI", L"./Resource/UI/traking.png");
	IMAGEMANAGER->AddTexture(L"save_pointUI", L"./Resource/UI/save_point_effect.png");

	IMAGEMANAGER->AddTexture(L"info", L"./Resource/MainUI/info.png");
	IMAGEMANAGER->AddTexture(L"howto", L"./Resource/MainUI/how.png");
	IMAGEMANAGER->AddTexture(L"rank", L"./Resource/MainUI/rank.png");
	IMAGEMANAGER->AddTexture(L"credit", L"./Resource/MainUI/credit.png");

	//SavePoint
	MESHMANAGER->AddMesh("save_point", L"./Resource/save_point/save_point.obj");
	MESHMANAGER->AddMesh("save_point_Alpha", L"./Resource/save_point/save_point_flip/save_point_flip.obj");

	//Sound
	SOUNDMANAGER->AddSound("Destroy", L"./Sound/droid_destroyed3.wav");
	SOUNDMANAGER->AddSound("Fire", L"./Sound/ammo_fire.wav");
	SOUNDMANAGER->AddSound("InGame2", L"./Sound/XACTGameGroove2.wav");
	SOUNDMANAGER->AddSound("InGame", L"./Sound/XACTGameGroove1.wav"); 

	isLoadingEnd = true;
}

void LoadScene::Update()
{
	if (isLoadingEnd)
	{
		if (loadingThread.joinable())
			loadingThread.join();

		SCENEMANAGER->AddScene(new MainScene());
	}
}

void LoadScene::Render()
{
	frame += 0.2f;
	int count = int(frame) % texture.size();
	IMAGEMANAGER->DrawTexture(texture[count], {640, 360});
}

void LoadScene::Release()
{
}
