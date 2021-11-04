#include "Enemy.h"

#include "Collision/CollisionHandler.h"
#include "Airship.h"
#include "Audio.h"

std::unordered_map<std::string, std::function<Enemy*( enemy::Props* props, float x, float y )>> Enemy::m_EnemyMap = {};
std::unordered_map<std::string, enemy::Props*> Enemy::m_PropsMap = {};

Enemy::Enemy( enemy::Props* props, float x, float y )
    : m_Props( props )
{
    m_IsAlive = true;
    m_Health = m_Props->Health;
    m_InitialPosition.x = x;
    m_InitialPosition.y = y;
    m_Position = m_InitialPosition;

    m_RigidBody = new RigidBody();
    m_Collider = new BoxCollider();
    m_Collider->SetBuffer( -15, -10, 0, 0 );
}

Enemy::~Enemy()
{
    delete m_RigidBody;
    delete m_Collider;
}

void Enemy::Draw()
{
    Texture::Instance()->DrawFrame( m_Props->TextureID, m_Position.x, m_Position.y, m_Props->SpriteWidth, m_Props->SpriteHeight, m_Props->SpriteRow,
        m_Props->SpriteColumn, m_Props->Scale, m_Props->Scale, SDL_FLIP_VERTICAL );
}

void Enemy::Update( float dt )
{
    if ( m_Health <= 0 ) 
        m_IsAlive = false;

    m_Collider->Set( m_Position.x, m_Position.y, 20, 30 );

    for ( size_t i = 0; i < Airship::GetBullets()->size(); i++ )
    {
        for ( size_t j = 0; j < Airship::GetBullets()->at(i).size(); j++ )
        {
            if ( CollisionHandler::Instance()->CheckBoxCollision(m_Collider->Get(), Airship::GetBullets()->at(i).at(j)->GetCollider() ) )
            {
                m_Health -= 4;
                Airship::GetBullets()->at(i).at(j)->SetCollided();
            }
        }
    }
}

bool Enemy::IsDead()
{
    return !m_IsAlive;
}

void Enemy::Parse( const std::string& path )
{
    TiXmlDocument xml;
    xml.LoadFile( path );
    if ( xml.Error() )
        SDL_Log( "Failed to load file ", path.c_str() );

    TiXmlElement* root = xml.RootElement();
    for ( TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement() )
    {   
        if ( e->Value() == std::string( "enemy" ) )
        {
            std::string textureId, bulletTexture, type;
            int spriteWidth, spriteHeight, spriteColumn, spriteRow, health, firePower, bulletSpeed;
            int flip;
            double scale;
            
            textureId = e->Attribute( "textureId" );
            bulletTexture = e->Attribute( "bulletTexture" );
            type = e->Attribute( "type" );
            e->Attribute( "spriteWidth", &spriteWidth );
            e->Attribute( "spriteHeight", &spriteHeight );
            e->Attribute( "spriteColumn", &spriteColumn );
            e->Attribute( "spriteRow", &spriteRow );
            e->Attribute( "health", &health );
            e->Attribute( "firePower", &firePower );
            e->Attribute( "bulletSpeed", &bulletSpeed );
            e->Attribute( "flip", &flip );
            e->Attribute( "scale", &scale );

            SDL_RendererFlip flip_;
            if ( flip == 0 ) flip_ = SDL_FLIP_NONE;
            else if ( flip == 1 ) flip_ = SDL_FLIP_HORIZONTAL;
            else if ( flip == 2 ) flip_ = SDL_FLIP_VERTICAL;

            // Store both the properties and constructor functions in different unordered maps
            enemy::Props* props = new enemy::Props( type, textureId, spriteWidth, spriteHeight, spriteRow, spriteColumn, flip_,
                scale, health, firePower, bulletTexture, bulletSpeed );
            RegisterProps( type, props );
            RegisterType( type, []( enemy::Props* props, float x, float y )->Enemy* {
                return new Enemy( props, x, y );
            });
        }
    }
}

Enemy* Enemy::New( const std::string& type, float x, float y )
{
    Enemy* lvl = nullptr;
    auto it = m_EnemyMap.find( type );
    if ( it != m_EnemyMap.end() )
    {
        enemy::Props* props = m_PropsMap[type];
        lvl = it->second( props, x, y );
    }
        
    return lvl;
}

void Enemy::RegisterType( std::string type, std::function<Enemy*( enemy::Props* props, float x, float y )> etype)
{
    m_EnemyMap[type] = etype;
}

void Enemy::RegisterProps( std::string type, enemy::Props* props )
{
    m_PropsMap[type] = props;
}

void Enemy::SetPosition( float x, float y)
{
    m_Position.x = x;
    m_Position.y = y;
}

void Enemy::Move( float x, float y )
{
    SetPosition( GetPosition().x + x, GetPosition().y + y );    
}
