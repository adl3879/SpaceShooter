#pragma once

#include "GameState.h"
#include "Engine.h"
#include "Levels/Level.h"
#include "Levels/LevelFactory.h"

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
    std::string m_LevelID;

};
