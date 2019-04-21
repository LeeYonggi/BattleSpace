#pragma once


namespace d3d
{
	D3DLIGHT9 GetDirectionalLight(Vector3 *dir, D3DXCOLOR *color);
}

template<class T>
T Lerp(T p1, T p2, float d)
{
	return p1 + (p2 - p1) * d;
}

int GetRandomNumber(int low, int high);