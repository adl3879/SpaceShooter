#include "Airship.h"

#include "ObjectFactory.h"
#include "Texture.h"
#include "Input.h"
#include "Audio.h"
#include "Collision/CollisionHandler.h"

static Registrar<Airship> registrar( "airship" );
int curr = 0;

Airship::Airship( Props* props )
    : GameObject( props )
{
    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity( 0.0f );
    m_BulletSpeed = 10.0f;
}

void Airship::Draw()
{
    Texture::Instance()->Draw( m_TextureID, m_Transform->x, m_Transform->y, m_Width, m_Height, 0.0f, 0.06f, 0.06f );
    
    for ( int i = 0; i < curr; i++ )
    {
        m_Bullets[i][0].Draw();
        m_Bullets[i][1].Draw();
    }
}

void Airship::Update( float dt )
{
    m_RigidBody->UnSetForce();

    if ( Input::GetDirection() == "left" )
        m_RigidBody->ApplyForceX( 2.0f * BACKWARD );

    if ( Input::GetDirection() == "right" )
        m_RigidBody->ApplyForceX( 2.0f * FORWARD );

    if ( Input::GetDirection() == "up" )
        m_RigidBody->ApplyForceY( 2.0f * UPWARD );

    if ( Input::GetDirection() == "down" )
        m_RigidBody->ApplyForceY( 2.0f * DOWNWARD );

    if ( Input::GetKeyDown( SDL_SCANCODE_SPACE ) || Input::GetMouseButtonState( LEFT ) )
        m_BulletSpeed -= dt;

    if ( m_BulletSpeed < 0 )
    {
        Audio::Instance()->Play( "shoot" );

        m_Bullets[curr][0].Shoot( "bullet_2", m_Transform->x - 10, m_Transform->y );
        m_Bullets[curr][1].Shoot( "bullet_2", m_Transform->x + 15, m_Transform->y );

        curr++;
        if ( curr > 99 ) curr = 0;
        m_BulletSpeed = 10.0f;
    }

    for ( int i = 0; i < curr; i++ )
    {
        m_Bullets[i][0].Update( dt );
        m_Bullets[i][1].Update( dt );
    }

    m_RigidBody->Update( dt );
    m_LastSafePos = *m_Transform;
    m_RigidBody->Move( *m_Transform );
    if ( CollisionHandler::Instance()->CheckBoundary( *m_Transform ) ) 
    {
        m_Transform->x = m_LastSafePos.x;
        m_Transform->y = m_LastSafePos.y;
    }

    Input::ResetDirection();
}

void Airship::Clean()
{
    // m_Bullets.clear();
    delete m_RigidBody;
    
    Texture::Instance()->Clean();
}
