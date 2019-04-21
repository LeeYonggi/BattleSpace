#pragma once
#include "Singleton.h"

struct Texture
{
	D3DXIMAGE_INFO info;
	LPDIRECT3DTEXTURE9 tex;
};

class ImageManager :
	public Singleton<ImageManager>
{
public:
	ImageManager();
	virtual ~ImageManager();

private:
	map<wstring, Texture*> m_Texture;
	LPD3DXSPRITE sprite;

public:
	Texture *AddTexture(wstring str, wstring fileName);
	vector<Texture*> AddAnimeTexture(wstring str, wstring fileName, int low, int high);
	void DrawTexture(wstring str, Vector2 pos, float rotate = 0, float scale = 1, Vector2 length = {1, 1}, D3DXCOLOR color = { 1, 1, 1, 1 });
	void DrawTexture(Texture *tex, Vector2 pos, float rotate = 0, float scale = 1, Vector2 length = { 1, 1 }, D3DXCOLOR color = { 1, 1, 1, 1 });
	void DrawFont(string str, Vector2 pos, float scale, D3DXCOLOR color = {1, 1, 1, 1});

	void Release();
};

#define IMAGEMANAGER ImageManager::GetInstance()