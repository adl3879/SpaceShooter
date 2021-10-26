#pragma once

#include "GameState.h"
#include "Engine.h"
#include "UserInterface/Button.h"

class Menu : public GameState
{
public:
    Menu();

    virtual bool Init() override;
    virtual bool Exit() override;
    virtual void Update() override;
    virtual void Render() override;

private:
    Button* m_PlayBtn;
    Button* m_ExitBtn;
    Button* m_SettingsBtn;
    
};
