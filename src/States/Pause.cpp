#include "Pause.h"

#include <memory>
#include "UserInterface/Button.h"
#include "Menu.h"

Button* btn;

Pause::Pause()
{
    // Init text renderer
    m_Text["paused"] = new Text( "algerian_86" );
    m_Text["continue"] = new Text( "calibri_16" );
    btn = new Button( "arial_18" );
}

bool Pause::Init()
{
    return true;
}

void Pause::Render()
{
    Texture::Instance()->Draw( "background", 0, 0, 1500, 1000 );

    m_Text["paused"]->SetColor( 0xFFFFFFFF );
    m_Text["paused"]->Draw(
        "PAUSED",
        SDL_Point{
            SCREEEN_WIDTH / 2 - m_Text["paused"]->GetWidth() / 2,
            SCREEEN_HEIGHT / 2 - m_Text["paused"]->GetHeight() / 2
        }
    );

    m_Text["continue"]->Draw(
        "Press any key to continue...",
        SDL_Point{
            SCREEEN_WIDTH / 2 - m_Text["continue"]->GetWidth() / 2,
            SCREEEN_HEIGHT / 2 - m_Text["paused"]->GetHeight() / 2 + 90
        }
    );

    btn->RenderX( "Main Menu", 20, 10, 35, 20 );
}

void Pause::Update()
{
    if ( Input::GetKeyDown( SDL_SCANCODE_P ) )
        Engine::Instance()->PopState();

    if ( btn->IsClicked() )
        Engine::Instance()->ChangeState( new Menu() );
}

bool Pause::Exit()
{   
    std::map<std::string, Text*>::iterator iterator;
    for ( iterator = m_Text.begin(); iterator != m_Text.end(); iterator++ )
        delete iterator->second;
    m_Text.clear();
    delete btn;

    return true;
}
