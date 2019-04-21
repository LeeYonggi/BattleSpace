#include "DXUT.h"
#include "ImageManager.h"


ImageManager::ImageManager()
{
	D3DXCreateSprite(DEVICE, &sprite);
}


ImageManager::~ImageManager()
{
	Release();
}

Texture * ImageManager::AddTexture(wstring str, wstring fileName)
{
	auto iter = m_Texture.find(str);
	if (iter != m_Texture.end()) return iter->second;

	Texture *temp = new Texture;

	D3DXCreateTextureFromFileExW(DEVICE,
		fileName.c_str(), D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT,
		0,
		&temp->info,
		nullptr,
		&temp->tex);

	m_Texture.insert(make_pair(str,	temp));

	return temp;
}

vector<Texture*> ImageManager::AddAnimeTexture(wstring str, wstring fileName, int low, int high)
{
	vector<Texture*> temp;
	for (int i = low; i <= high; i++)
	{
		WCHAR wstr[128];
		wsprintf(wstr, fileName.c_str(), i);
		temp.push_back(AddTexture(str + to_wstring(i), wstr));
	}
	return temp;
}

void ImageManager::DrawTexture(wstring str, Vector2 pos, float rotate, float scale, Vector2 length, D3DXCOLOR color)
{
	auto iter = m_Texture.find(str);
	if (iter == m_Texture.end()) return;

	Matrix matW, matS, matR, matT;
	D3DXMatrixScaling(&matS, scale, scale, 1);
	D3DXMatrixRotationZ(&matR, rotate);
	D3DXMatrixTranslation(&matT, pos.x, pos.y, 0);

	matW = matS * matR * matT;

	sprite->SetTransform(&matW);

	Vector3 center = {(float)iter->second->info.Width * 0.5f, (float)iter->second->info.Height * 0.5f, 0};

	RECT rect = {0, 0, iter->second->info.Width * length.x, iter->second->info.Height * length.y };

	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(iter->second->tex, &rect, &center, nullptr, color);
	sprite->End();
}

void ImageManager::DrawTexture(Texture * tex, Vector2 pos, float rotate, float scale, Vector2 length, D3DXCOLOR color)
{
	Matrix matW, matS, matR, matT;
	D3DXMatrixScaling(&matS, scale, scale, 1);
	D3DXMatrixRotationZ(&matR, rotate);
	D3DXMatrixTranslation(&matT, pos.x, pos.y, 0);

	matW = matS * matR * matT;

	sprite->SetTransform(&matW);

	Vector3 center = { (float)tex->info.Width * 0.5f, (float)tex->info.Height * 0.5f, 0 };

	RECT rect = { 0, 0, tex->info.Width * length.x, tex->info.Height * length.y };

	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(tex->tex, &rect, &center, nullptr, color);
	sprite->End();
}

void ImageManager::DrawFont(string str, Vector2 pos, float scale, D3DXCOLOR color)
{
	LPD3DXFONT font;

	D3DXCreateFontA(DEVICE, scale, 0, FW_HEAVY, 1, false, HANGUL_CHARSET, 0, 0, 0, "¸¼Àº °íµñ", &font);

	Matrix matT;
	D3DXMatrixTranslation(&matT, pos.x, pos.y, 0);

	sprite->SetTransform(&matT);

	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT re = { 0 };

	font->DrawTextA(sprite, str.c_str(), -1, &re, DT_NOCLIP, color);

	sprite->End();

	SAFE_RELEASE(font);
}

void ImageManager::Release()
{
	for (auto iter : m_Texture)
	{
		SAFE_RELEASE(iter.second->tex);
		SAFE_DELETE(iter.second);
	}
	m_Texture.clear();

	SAFE_RELEASE(sprite);
}
