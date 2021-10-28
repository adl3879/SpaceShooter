#include "Play.h"

#include "Pause.h"
#include "ObjectFactory.h"
#include "Text.h"
#include "Audio.h"
#include "Menu.h"

Play::Play()
{
    ObjectFactory::Instance()->Parse( "../res/gfx/objects.xml", m_GameObjects );
    m_LevelID = "one";
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

    LevelFactory::Instance()->GetLevel( m_LevelID )->Draw();
}

void Play::Update()
{
    float dt = Timer::Instance()->GetDeltaTime();
    if ( m_GameObjects.size() > 0 )
        for ( auto& obj : m_GameObjects )
            obj->Update( dt );

    LevelFactory::Instance()->GetLevel( m_LevelID )->Update( dt );

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

    LevelFactory::Instance()->GetLevel( m_LevelID )->Clean();

    Texture::Instance()->Clean();
    Audio::Instance()->Clean();

    return true;
}

void Play::OpenMenu()
{
    //
}

void Play::PauseGame()
{
    Engine::Instance()->PushState( new Pause() );
}
