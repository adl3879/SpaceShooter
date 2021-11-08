#pragma once

#include "Vector2D.h"
#include "Engine.h"

#include <math.h>
#include <string>

#define PI 3.14159265359
#define DEG_2_RAD( angle ) \
    angle * PI / 180

class Particle
{
public:
    Particle();
    virtual ~Particle();

    void Init( char* textureId, const Vector2D& pos, float startSpeed, float endSpeed, float angle, double rotSpeed, float startSize, float endSize, 
        int life, SDL_Rect textureRect, SDL_Color startColor, SDL_Color endColor, SDL_BlendMode blendMode, bool vortexSensitive );

    bool Update( float dt );
    void Draw();

    bool InUse() const;
    Particle* GetNext() const;
    void SetNext( Particle* next );

    SDL_Color RgbInterpolation( SDL_Color startColor, float timeStep, SDL_Color endColor );
    float InterpolateBetweenRange( float min, float timeStep, float max );
    void AddVortex( Vector2D position, float speed, float scale );
    void CalculateParticlePos( float dt );

private:
    int m_Life;

    struct Vortex
    {
        Vector2D Position;
        float Speed = 0.0f;
        float Scale = 0.0f;
    } m_Vortex;

    union ParticleUnion
    {
        struct ParticleState
        {
            unsigned int StartLife;
            Vector2D Position;
            Vector2D StartVelocity, CurrentVelocity, EndVelocity;
            float CurrentSize, StartSize, EndSize;
            float TimeStep;
            double StartRotSpeed, CurrentRotSpeed;
            float Angle;
            SDL_Rect RectSize;
            SDL_Rect Rect;
            SDL_Color StartColor, EndColor;
            SDL_BlendMode BlendMode;
            bool VortexSensitive;
            char* TextureID;

            ParticleState() {}
        } Live;
        
        Particle* Next;

        ParticleUnion() {}
    } m_State;
};
