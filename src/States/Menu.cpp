#include "Menu.h"

#include "Texture.h"
#include "Input.h"
#include "Play.h"
#include "Text.h"

Menu::Menu()
{
    m_PlayBtn = new Button( "arial_18" );
    m_ExitBtn = new Button( "arial_18" );
    m_SettingsBtn = new Button( "arial_18" );
}

bool Menu::Init()
{
    return true;
}

void Menu::Render()
{
    Texture::Instance()->Draw( "menu_background", 0, 0, 1500, 1000 );

    int xpos = SCREEEN_WIDTH / 2 - 250 / 2;

    m_PlayBtn->Render( "Start", xpos, 200, 250, 50 );
    m_SettingsBtn->Render( "Settings", xpos, 270, 250, 50 );
    m_SettingsBtn->SetDisabled();
    m_ExitBtn->Render( "Exit", xpos, 340, 250, 50 );
}

void Menu::Update()
{    
    if ( m_PlayBtn->IsClicked() )
        Engine::Instance()->ChangeState( new Play() );

    if ( m_ExitBtn->IsClicked() )
        Engine::Instance()->Quit();
}

bool Menu::Exit()
{
    delete m_PlayBtn;
    delete m_ExitBtn;
    delete m_SettingsBtn;

    return true;
}
