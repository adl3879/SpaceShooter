#pragma once

#include "Vector2D.h"
#include "Engine.h"
#include "ParticlePool.h"
#include "PerfTimer.h"
#include "ParticleSystem.h"

struct EmitterData;

class Emitter
{
public:
    Emitter( Vector2D position, EmitterData data );
    virtual ~Emitter();

    void Update( float dt );
    void Draw();

    float RangeRandomNum( float min = -1.0f, float max = 1.0f );
    int GetPoolSize() const;

    void StartEmission( double timer = -1.0f );
    void StopEmission( double timer = 0.0f );
    void MoveEmitter( Vector2D newPosition );
    const Vector2D& GetEmitterPosition() const;
    
    void VortexSensitive( bool sensitive );

private:
    // unsigned int m_StartLife;
    Vector2D m_Position;
    float m_StartSpeed, m_EndSpeed;
    float m_StartSize, m_EndSize;
    double m_RotSpeed;
    Vector2D m_AngleRange;
    SDL_Rect m_TextureRect;
    SDL_Color m_StartColor, m_EndColor;
    SDL_BlendMode m_BlendMode;
    float m_TimeStep = 0.0f;

    PerfTimer m_StopTimer;
    PerfTimer m_EmissionTimer;
    PerfTimer m_LifeTimer;
    double m_StopTime = 0.0f;
    double m_EmissionTime = 0.0f;
    double m_LifeTime = -1.0f;

    ParticlePool* m_EmitterPool = nullptr;
    int m_PoolSize = 0;

    int m_EmissionRate = 0;
    unsigned int m_EmitNumber= 0u;
    unsigned int m_MaxParticleLife = 0u;
    unsigned int m_MaxParticlesPerFrame = 0u;
    unsigned int m_EmitVariance = 0u;

    bool m_Active = false;
    bool m_VortexSensitive = false;

    Vector2D m_RotSpeedRand;
    Vector2D m_StartSpeedRand;
    Vector2D m_EndSpeedRand;
    Vector2D m_EmitVarianceRand;
    Vector2D m_LifeRand;
    Vector2D m_StartSizeRand;
    Vector2D m_EndSizeRand;
};