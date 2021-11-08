#include "Particle.h"

Particle::Particle()
{
    m_Life = 0;
}

Particle::~Particle()
{
    //
}

void Particle::Init( char* textureId, const Vector2D& pos, float startSpeed, float endSpeed, float angle, double rotSpeed, float startSize, float endSize, 
    int life, SDL_Rect textureRect, SDL_Color startColor, SDL_Color endColor, SDL_BlendMode blendMode, bool vortexSensitive )
{
    // Movement properties
	m_State.Live.Position = pos;
	m_State.Live.StartVelocity.x = startSpeed * cos( DEG_2_RAD( angle ) );
	m_State.Live.StartVelocity.y = -startSpeed * sin( DEG_2_RAD( angle ) );
	m_State.Live.EndVelocity.x = endSpeed * cos( DEG_2_RAD( angle ) );
	m_State.Live.EndVelocity.y = -endSpeed * sin( DEG_2_RAD( angle ) );
	m_State.Live.StartRotSpeed = rotSpeed;
	m_State.Live.CurrentRotSpeed = rotSpeed;

	// Life properties
	m_Life = m_State.Live.StartLife = life;
	m_State.Live.CurrentSize = m_State.Live.StartSize = startSize;
	m_State.Live.EndSize = endSize;
	m_State.Live.TimeStep = 0.0f;

	// Color properties
	m_State.Live.StartColor = startColor;
	m_State.Live.EndColor = endColor;
	m_State.Live.BlendMode = blendMode;
	m_State.Live.Rect = m_State.Live.RectSize = textureRect;
    m_State.Live.TextureID = textureId;

	// Vortex
	m_State.Live.VortexSensitive = vortexSensitive;

	// Add vortex to the system (optional and only one is allowed)
	if ( m_State.Live.VortexSensitive )
		AddVortex( Vector2D( 250.0f, 200.0f ), 10.0f, 30.0f );
}

void Particle::Draw()
{
    SDL_Rect tmpRect = { static_cast<int>( m_State.Live.StartSize ), static_cast<int> ( m_State.Live.StartSize ) };
    float centerX = m_State.Live.Position.x + ( ( tmpRect.w - m_State.Live.RectSize.w ) / 2.0f );
    float centerY = m_State.Live.Position.y + ( ( tmpRect.h - m_State.Live.RectSize.h ) / 2.0f );

    SDL_Color resColor;

    if ( m_State.Live.StartLife > 15 )
        resColor = RgbInterpolation( m_State.Live.StartColor, m_State.Live.TimeStep, m_State.Live.EndColor );

    // Blit particle on screen
    Texture::Instance()->BlitParticle( m_State.Live.TextureID, static_cast<int>( centerX ), static_cast<int>( centerY ), 
        &m_State.Live.Rect, &m_State.Live.RectSize, resColor, m_State.Live.BlendMode, 1.0f, m_State.Live.CurrentRotSpeed );

    m_State.Live.CurrentRotSpeed += m_State.Live.StartRotSpeed;
    m_State.Live.TimeStep += ( 1.0f / static_cast<float>( m_State.Live.StartLife ) );

    if ( m_State.Live.TimeStep >= 1.0f )
        m_State.Live.TimeStep = 0.0f;
}

bool Particle::Update( float dt )
{
    if ( !m_State.Live.VortexSensitive && m_Vortex.Scale != 0 && m_Vortex.Speed != 0 )
        AddVortex( Vector2D( 0.0f, 0.0f ), 0.0f, 0.0f );

    // Particle size interpolation
    m_State.Live.CurrentSize = InterpolateBetweenRange( m_State.Live.StartSize, m_State.Live.TimeStep, m_State.Live.EndSize );

    // Particle speed interpolation
    m_State.Live.CurrentVelocity.x = InterpolateBetweenRange( m_State.Live.StartVelocity.x, m_State.Live.TimeStep, m_State.Live.EndVelocity.x );
    m_State.Live.CurrentVelocity.y = InterpolateBetweenRange( m_State.Live.StartVelocity.y, m_State.Live.TimeStep, m_State.Live.EndVelocity.y );

    // Assign new size to particle rect
    m_State.Live.RectSize.w = m_State.Live.RectSize.h = m_State.Live.CurrentSize;

    CalculateParticlePos( dt );

    m_Life--;
    return m_Life == 0;
}

bool Particle::InUse() const
{
    return m_Life > 0;
}

Particle* Particle::GetNext() const
{
    return m_State.Next;
}

void Particle::SetNext( Particle* next )
{
    m_State.Next = next;
}

SDL_Color Particle::RgbInterpolation( SDL_Color startColor, float timeStep, SDL_Color endColor )
{
    SDL_Color finalColor;

    finalColor.r = startColor.r + ( endColor.r - startColor.r ) * timeStep;
    finalColor.g = startColor.g + ( endColor.g - startColor.g ) * timeStep;
    finalColor.b = startColor.b + ( endColor.b - startColor.b ) * timeStep;
    finalColor.a = startColor.a + ( endColor.a - startColor.a ) * timeStep;

    return finalColor;
}

float Particle::InterpolateBetweenRange( float min, float timeStep, float max )
{
    return min + ( max - min ) * timeStep;
}

void Particle::AddVortex( Vector2D position, float speed, float scale )
{
    m_Vortex.Position = position;
    m_Vortex.Speed = speed;
    m_Vortex.Scale = scale;
}

void Particle::CalculateParticlePos( float dt )
{
    float dx = m_State.Live.Position.x - m_Vortex.Position.x;
    float dy = m_State.Live.Position.y - m_Vortex.Position.y;
    float vx = -dy * m_Vortex.Speed;
    float vy = dx * m_Vortex.Speed;
    float factor = 1.0f / ( 1.0f + ( dx * dx + dy * dy ) / m_Vortex.Scale );

    m_State.Live.Position.x += ( vx - m_State.Live.CurrentVelocity.x ) * factor + m_State.Live.CurrentVelocity.x * dt;
    m_State.Live.Position.y += ( vy - m_State.Live.CurrentVelocity.y ) * factor + m_State.Live.CurrentVelocity.y * dt;
}
