#pragma once

#include "Particle.h"
#include "Vector2D.h"
#include "Emitter.h"

class ParticlePool
{
public:
    ParticlePool( Emitter* emitter );
    virtual ~ParticlePool() {};

    void Create( const Vector2D& pos, float startSpeed, float endSpeed, float angle, double rotSpeed, float startSize, float endSize, 
        int life, SDL_Rect textureRect, SDL_Color startColor, SDL_Color endColor, SDL_BlendMode blendMode, bool vortexSensitive );
    void Update( float dt );
    void Draw();

private:
    int m_PoolSize = 100;
    Particle*  m_FirstAvailable;
    Particle* m_ParticleArray;
};
