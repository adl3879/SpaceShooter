#include "Bullet.h"
#include "Texture.h"

Bullet::Bullet()
{
    //
}

void Bullet::Draw()
{
    Texture::Instance()->Draw( m_Type, (int)m_Pos->x + 10, (int)m_Pos->y - 5, 120, 120, 0.0f, 0.3f, 0.3f, 270.0 );
}

void Bullet::Update( float dt )
{
    if ( m_IsFired )
    {    
        m_RigidBody->UnSetForce();
        m_RigidBody->ApplyForceY( 5.0f * UPWARD );
        m_RigidBody->Update( dt );
        m_RigidBody->Move( *m_Pos );
    }
}

void Bullet::Shoot( std::string type, float x, float y )
{
    m_Pos = new Vector2D( x, y );
    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity( 0.0f );
    m_Type = type;

    m_IsFired = true;
}
