#include "DXUT.h"
#include "Particle.h"

#include "Effect.h"

Particle::Particle(vector<Texture*> effectAnime, float particleDelay)
{
	animeTexture.push_back(effectAnime);
	delay = particleDelay;
}


Particle::~Particle()
{
}

void Particle::Init()
{
}

void Particle::Update()
{
	frame += ELTIME;
	if (frame > delay)
	{
		OBJECTMANAGER->AddObject(OBJ_KINDS::OBJ_EFFECT, new Effect(animeTexture[0], 
			pos, moveVector, scale, isLoop, endTime, animeSpeed));
		frame = 0;
	}
}

void Particle::Render()
{
}

void Particle::Release()
{
}

void Particle::ParticleInit(Vector3 pos, Vector3 moveVector, float scale, bool isLoop, float endTime, float animeSpeed)
{
	this->pos = pos;
	this->moveVector = moveVector;
	this->scale = scale;
	this->isLoop = isLoop;
	this->endTime = endTime;
	this->animeSpeed = animeSpeed;
}
