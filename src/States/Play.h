#pragma once

#include "GameState.h"
#include "Engine.h"

class Play : public GameState
{
public:
    Play();
    
    virtual bool Init() override;
    virtual bool Exit() override;
    virtual void Update() override;
    virtual void Render() override;

private:
    static void OpenMenu();
    static void PauseGame();

private:
    std::vector<GameObject*> m_GameObjects;
    SDL_Renderer* m_Ctx;

};
