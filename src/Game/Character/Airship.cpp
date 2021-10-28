#include "Airship.h"

#include "ObjectFactory.h"
#include "Texture.h"
#include "Input.h"
#include "Audio.h"
#include "Collision/CollisionHandler.h"

static Registrar<Airship> registrar( "airship" );

Bullets Airship::m_Bullets = {};

Airship::Airship( Props* props )
    : GameObject( props )
{
    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity( 0.0f );
    m_BulletInterval = 8.0f;
}

void Airship::Draw()
{
    Texture::Instance()->Draw( m_TextureID, m_Transform->x, m_Transform->y, m_Width, m_Height, 0.0f, 0.06f, 0.06f );
    
    for ( size_t i = 0; i < m_Bullets.size(); i++ )
        for ( size_t j = 0; j < m_Bullets[i].size(); j++)
            m_Bullets[i][j]->Draw();
}

void Airship::Update( float dt )
{
    m_RigidBody->UnSetForce();
    HandleInput( dt );

    if ( m_BulletInterval < 0 )
    {
        Audio::Instance()->Play( "shoot" );

        m_Bullets.push_back({ 
            new Bullet( "bullet_2", m_Transform->x - 15, m_Transform->y, -0.8 ), 
            new Bullet( "bullet_1", m_Transform->x - 10, m_Transform->y, -0.1 ), 
            new Bullet( "bullet_3", m_Transform->x - 5,  m_Transform->y,  0.0 ), 
            new Bullet( "bullet_2", m_Transform->x + 5,  m_Transform->y,  0.1 ),
            new Bullet( "bullet_5", m_Transform->x + 10, m_Transform->y,  0.8 ),
            new Bullet( "bullet_2", m_Transform->x + 15, m_Transform->y,  1.0 ),
        });

        m_BulletInterval = 8.0f;
    }

    for ( size_t i = 0; i < m_Bullets.size(); i++ )
    {
        for ( size_t j = 0; j < m_Bullets[i].size(); j++)
        {
            m_Bullets[i][j]->Update( dt );
            if ( m_Bullets[i][j]->GetPos()->y < -20 && i < m_Bullets.size() )
            {
                delete m_Bullets[i][j];
                m_Bullets.erase( m_Bullets.begin() + i );
            }
        }
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

void Airship::HandleInput( float dt )
{
    if ( Input::GetDirection() == "left" )
        m_RigidBody->ApplyForceX( 3.0f * BACKWARD );

    if ( Input::GetDirection() == "right" )
        m_RigidBody->ApplyForceX( 3.0f * FORWARD );

    if ( Input::GetDirection() == "up" )
        m_RigidBody->ApplyForceY( 3.0f * UPWARD );

    if ( Input::GetDirection() == "down" )
        m_RigidBody->ApplyForceY( 3.0f * DOWNWARD );

    if ( Input::GetKeyDown( SDL_SCANCODE_SPACE ) || Input::GetMouseButtonState( LEFT ) )
        m_BulletInterval -= dt;
}

Bullets* Airship::GetBullets()
{
    return &m_Bullets;
}

void Airship::Clean()
{
    m_Bullets.clear();
    delete m_RigidBody; 
    Texture::Instance()->Clean();
}
