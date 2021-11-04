#include "Bullet.h"
#include "Texture.h"

Bullet::Bullet( std::string type, float x, float y, float angle, Direction direction, float speed )
{
    m_RigidBody = new RigidBody();
    m_Pos = new Vector2D( x, y );
    m_RigidBody->SetGravity( 0.0f );
    m_Collider = new BoxCollider();
    m_Collider->SetBuffer( -16, 0, 0, 0 );
    m_Collided = false;

    m_Type = type;
    m_Angle = angle;
    m_Speed = speed;
    m_Direction = direction;

    m_IsFired = true;
}

Bullet::~Bullet()
{
    delete m_RigidBody;
    delete m_Collider;
}

void Bullet::Draw()
{
    Texture::Instance()->Draw( m_Type, (int)m_Pos->x, (int)m_Pos->y, 120, 120, 0.0f, 0.3f, 0.3f, 270.0 );
    // m_Collider->Draw();
}

void Bullet::Update( float dt )
{
    if ( m_IsFired )
    {    
        m_RigidBody->UnSetForce();
        m_RigidBody->ApplyForceY( m_Speed * m_Direction );
        m_RigidBody->ApplyForceX( m_Angle );
        m_RigidBody->Update( dt );
        m_RigidBody->Move( *m_Pos );

        m_Collider->Set( m_Pos->x, m_Pos->y, 4, 10 );
    }
}

SDL_Rect Bullet::GetCollider() const
{
    return m_Collider->Get();
}
