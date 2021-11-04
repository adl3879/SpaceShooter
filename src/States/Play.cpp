#include "Play.h"

#include "Pause.h"
#include "ObjectFactory.h"
#include "Text.h"
#include "Audio.h"
#include "Menu.h"
#include "Character/Enemy.h"

std::string Play::m_LevelID = "";

Play::Play()
{
    ObjectFactory::Instance()->Parse( "../res/gfx/objects.xml", m_GameObjects );
    m_LevelID = "one";

    Enemy::Parse( "../res/gfx/enemies.xml" );
    m_Level = LevelFactory::Instance()->GetLevel( m_LevelID );
}

bool Play::Init()
{
    m_Ctx = Engine::Instance()->GetRenderer();

    return true;
}

void Play::Render()
{
    Texture::Instance()->Draw( "background", 0, 0, 1500, 1000 );

    if ( m_GameObjects.size() > 0 )
        for ( auto& obj : m_GameObjects ) 
            obj->Draw();

    m_Level->Draw();
}

void Play::Update()
{
    float dt = Timer::Instance()->GetDeltaTime();
    if ( m_GameObjects.size() > 0 )
        for ( auto& obj : m_GameObjects )
            obj->Update( dt );

    m_Level->Update( dt );

    if ( Input::GetKeyDown( SDL_SCANCODE_ESCAPE ) )
        PauseGame();
    
    if ( Input::GetKeyDown( SDL_SCANCODE_X ) )
        Engine::Instance()->PushState( new Menu() );
}

bool Play::Exit()
{
    if ( m_GameObjects.size() > 0 )
        for ( auto& obj : m_GameObjects )
            obj->Clean();

    m_Level->Clean();

    Texture::Instance()->Clean();
    Audio::Instance()->Clean();

    return true;
}

void Play::SetLevel( const std::string& id )
{
    m_LevelID = id;
}

void Play::OpenMenu()
{
    //
}

void Play::PauseGame()
{
    Engine::Instance()->PushState( new Pause() );
}
