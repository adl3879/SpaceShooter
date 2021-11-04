#include "ParticlePool.h"
#include <assert.h>

ParticlePool::ParticlePool( Emitter* emitter )
{
    m_PoolSize = emitter->GetPoolSize();
    m_ParticleArray = new Particle[m_PoolSize];

    m_FirstAvailable = &m_ParticleArray[0];

    // Eact particle point to the next
    for ( size_t i = 0; i < m_PoolSize; i++ )
        m_ParticleArray[i].SetNext( &m_ParticleArray[i + 1] );

    // The last one terminates the list
    m_ParticleArray[m_PoolSize - 1].SetNext( nullptr );
}

void ParticlePool::Create( const Vector2D& pos, float startSpeed, float endSpeed, float angle, double rotSpeed, float startSize, float endSize, 
    int life, SDL_Rect textureRect, SDL_Color startColor, SDL_Color endColor, SDL_BlendMode blendMode, bool vortexSensitive )
{
    assert( m_FirstAvailable != nullptr );

    // Remove it from the available list
    Particle* newParticle = m_FirstAvailable;
    m_FirstAvailable = newParticle->GetNext();

    newParticle->Init( pos, startSpeed, endSpeed, angle, rotSpeed, startSize, endSize, life, textureRect, startColor, endColor, 
        blendMode, vortexSensitive );
}

void ParticlePool::Update( float dt )
{
    for ( size_t i = 0; i < m_PoolSize; i++ )
    {
        if ( m_ParticleArray[i].InUse() )
        {
            m_ParticleArray[i].Update( dt );
        } 
        else
        {
            m_ParticleArray[i].SetNext( m_FirstAvailable );
            m_FirstAvailable = &m_ParticleArray[i];
        }
    }
}

void ParticlePool::Draw()
{
    for ( size_t i = 0; i < m_PoolSize; i++ )
        m_ParticleArray[i].Draw();
}
