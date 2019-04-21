#pragma once
#include "Scene.h"

#include <thread>

#define ANIME_FRAME 10

class LoadScene :
	public Scene
{
public:
	LoadScene();
	virtual ~LoadScene();

public:
	thread loadingThread;
	bool isLoadingEnd = false;
	vector<Texture*> texture;
	float frame = 0.0f;

public:
	void Init()		override;
	void Update()	override;
	void Render()	override;
	void Release()	override;

public:
	void Loading();
};

