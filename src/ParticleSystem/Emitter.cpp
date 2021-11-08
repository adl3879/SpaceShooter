#include "Emitter.h"

#include <time.h>

Emitter::Emitter( Vector2D position, EmitterData data )
{
    srand( time( nullptr ) );

    m_TextureID = data.TextureID;
    m_Position = position;
    m_StartSpeed = data.StartSpeed;
    m_EndSpeed = data.EndSpeed;
    m_StartSize = data.StartSize;
    m_EndSize = data.EndSize;
    m_RotSpeed = data.RotSpeed;
    m_AngleRange = data.AngleRange;

    m_TextureRect = data.TextureRect;
    m_StartColor = data.StartColor,
    m_EndColor = data.EndColor;
    m_BlendMode = data.BlendMode;
    m_VortexSensitive = data.VortexSensitive;

    m_EmitNumber = data.EmitNumber;
    m_EmitVariance = data.EmitVariance;
    m_MaxParticleLife = data.MaxParticleLife;
    m_MaxParticlesPerFrame = data.EmitNumber + data.EmitVariance;

    m_PoolSize = m_MaxParticlesPerFrame * ( m_MaxParticleLife + 1 );
    m_EmitterPool = new ParticlePool( this );

    m_Active = true;
    m_LifeTime = data.LifeTime;

    m_RotSpeedRand = data.RotSpeedRand;
    m_StartSpeedRand = data.StartSpeedRand;
    m_EndSpeedRand = data.EndSpeedRand;
    m_EmitVarianceRand = data.EmitVarianceRand;
    m_LifeRand = data.LifeRand;
    m_StartSizeRand = data.StartSizeRand;
    m_EndSizeRand = data.EndSizeRand;

    m_TimeStep = 1.0f / static_cast<float>( m_MaxParticleLife );

    if ( m_LifeTime != -1.0f && m_LifeTime > 0.0f )
        m_LifeTimer.Start();
}

Emitter::~Emitter()
{
    delete m_EmitterPool;
    m_EmitterPool = nullptr;
}

void Emitter::Update( float dt )
{
    if ( m_Active )
    {
        m_EmissionRate = static_cast<int>( m_EmitNumber + m_EmitVariance * RangeRandomNum( m_EmitVarianceRand.x, m_EmitVarianceRand.y ) );

        for ( size_t i = 1; i <= m_EmissionRate; i++ )
        {
            float tmpStartSpeed = m_StartSpeed * RangeRandomNum( m_StartSpeedRand.x, m_StartSpeedRand.y );
            float tmpEndSpeed = m_EndSpeed * RangeRandomNum( m_EndSpeedRand.x, m_EndSpeedRand.y );
            float randAngle = RangeRandomNum( m_AngleRange.x, m_AngleRange.y );
            float randStart = m_StartSize * RangeRandomNum( m_StartSizeRand.x, m_StartSizeRand.y );
            float randEnd = m_StartSize * RangeRandomNum( m_StartSizeRand.x, m_StartSizeRand.y );
            float randRadius = RangeRandomNum( randStart, randEnd );
            double randRotSpeed = m_RotSpeed * RangeRandomNum( m_RotSpeedRand.x, m_RotSpeedRand.y );

            m_EmitterPool->Create( m_TextureID.c_str(), m_Position, tmpStartSpeed, tmpEndSpeed, randAngle, randRotSpeed, randRadius, 
                m_EndSize, m_MaxParticleLife, m_TextureRect, m_StartColor, m_EndColor, m_BlendMode, m_VortexSensitive );
            m_TimeStep += m_TimeStep;
        }
    }

    if ( m_StopTime > 0.0f )
    {
        m_StopTime = 0.0f;
        if ( m_EmissionTimer.ReadMs() >= m_EmissionTime )
        {
            m_Active = false;
            m_EmissionTime = 0.0f;
        }
    }

    if ( m_EmissionTime > 0.0f )
	{
		m_StopTime = 0.0f;
		if ( m_EmissionTimer.ReadMs() >= m_EmissionTime )
		{
			m_Active = false;
			m_EmissionTime = 0.0f;
		}
	}

    if ( m_LifeTime == 0.0f )
    {
        if ( m_LifeTimer.ReadMs() >= m_LifeTime )
        {
            m_Active = false;
            m_LifeTime = 0.0f;
        }
    }

    m_LifeTime--;
}

bool Emitter::Draw( float dt )
{
    if ( m_EmitterPool->Update(dt) == ParticleState::PARTICLE_DEAD && m_LifeTime <= -30.0f )
		ParticleSystem::Instance()->RemoveEmitter( this );
	else if ( m_EmitterPool->Update(dt) == ParticleState::PARTICLE_ALIVE_NOT_DRAWN )
		return false;

    return true;
}

float Emitter::RangeRandomNum( float min, float max )
{
    float random = static_cast<float>( rand() ) / static_cast<float>( RAND_MAX );
    float diff = max - min;
    float r = random * diff;

    return min + r;
}

int Emitter::GetPoolSize() const
{
    return m_PoolSize;
}

void Emitter::StartEmission( double timer )
{
    if ( !m_Active )
    {
        m_Active = false;
        m_StopTime = timer;
        m_StopTimer.Start();
    }
}

void Emitter::StopEmission( double timer )
{
    if ( m_Active )
    {
        m_Active = false;   
        m_StopTime = timer;
        m_StopTimer.Start();
    }
}

void Emitter::MoveEmitter( Vector2D newPosition )
{
    m_Position = newPosition;
}

const Vector2D& Emitter::GetEmitterPosition() const
{
    return m_Position;
}

void Emitter::VortexSensitive( bool sensitive )
{
    m_VortexSensitive = sensitive;
}
