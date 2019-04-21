#pragma once
#include "Object.h"
class Particle :
	public Object
{
public:
	Particle(vector<Texture*> effectAnime, float particleDelay);
	virtual ~Particle();

private:
	float delay = 0.0f;
	bool isLoop = false;
	float endTime = 0.0f;
	float animeSpeed;

public:
	virtual void Init()		override;
	virtual void Update()	override;
	virtual void Render()	override;
	virtual void Release()	override;

public:
	void ParticleInit(Vector3 pos, Vector3 moveVector, float scale, bool isLoop, float endTime, float animeSpeed);
};

