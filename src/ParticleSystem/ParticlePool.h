#pragma once

#include "Particle.h"
#include "Vector2D.h"
#include "Emitter.h"

class Emitter;

enum class ParticleState
{
	PARTICLE_STATE_NOT_DEF,
	PARTICLE_ALIVE_DRAWN,
	PARTICLE_ALIVE_NOT_DRAWN,
	PARTICLE_DEAD
};

class ParticlePool
{
public:
    ParticlePool( Emitter* emitter );
    virtual ~ParticlePool() {};

    void Create( const char* textureId, const Vector2D& pos, float startSpeed, float endSpeed, float angle, double rotSpeed, float startSize, float endSize, 
        int life, SDL_Rect textureRect, SDL_Color startColor, SDL_Color endColor, SDL_BlendMode blendMode, bool vortexSensitive );
    ParticleState Update( float dt );

private:
    int m_PoolSize = 100;
    Particle*  m_FirstAvailable;
    Particle* m_ParticleArray;
};
