#pragma once

#include <tinyxml.h>
#include "Engine.h"
#include "Vector2D.h"
#include "Emitter.h"

#include <string>
#include <list>
#include <unordered_map>

class Emitter;

struct EmitterData
{
    float StartSpeed = 0.0f, EndSpeed = 0.0f;
    float StartSize = 0.0f, EndSize = 0.0f;
    unsigned int EmitNumber = 0u;
    unsigned int EmitVariance = 0u;
    unsigned int MaxParticleLife = 0u;
    unsigned int MaxParticlesPerFrame = 0u;
    double RotSpeed = 0.0f;
    Vector2D AngleRange;
    SDL_Rect TextureRect = { 0, 0 };
    SDL_Color StartColor = { 0, 0, 0, 0 };
    SDL_Color EndColor = { 0, 0, 0, 0 };
    SDL_BlendMode BlendMode = SDL_BlendMode::SDL_BLENDMODE_NONE;
    std::string TextureID;
    double LifeTime = -1.0f;
    float TimeStep = 0.0f;

    double StopTime = 0.0f;
    double EmissionTime = 0.0f;

    SDL_FPoint RotSpeedRand;
    SDL_FPoint StartSpeedRand;
    SDL_FPoint EndSpeedRand;
    SDL_FPoint EmitVarianceRand;
    SDL_FPoint LifeRand;
    SDL_FPoint StartSizeRand;
    SDL_FPoint EndSizeRand;
    SDL_FPoint MaxParticleLifeRand;

    bool VortexSensitive = false;
};

class ParticleSystem
{
public:
    static ParticleSystem* Instance();

    bool Parse( const std::string& path );
    bool Start();
    bool PreUpdate();
    bool Update( float dt );
    bool PostUpdate();
    bool CleanUp();

    // Emitter methods
    Emitter* AddEmitter( const std::string& id, Vector2D position );
    bool RemoveEmitter( Emitter* emitter );
    bool RemoveAllEmitters();

private:
    ParticleSystem();

    std::unordered_map<std::string, EmitterData> m_EmitterMap;
    std::list<Emitter*> m_EmittersList;
    std::list<Emitter*> m_EmittersToDestroy;
};
