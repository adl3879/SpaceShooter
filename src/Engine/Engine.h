#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>

#include "Timer.h"
#include "Input.h"
#include "Texture.h"
#include "GameObject.h"
#include "GameState.h"
#include "Play.h"

// screen size
const int SCREEEN_WIDTH = 700;
const int SCREEEN_HEIGHT = 650; 

class Engine
{
public:
    // creates a singleton class
    static Engine* Instance()
    {
        return s_Instance = ( s_Instance != nullptr ) ? s_Instance : new Engine();
    }

    /**
     * Initializes the SDL and SDL_image library and checks for errors
     * Creates window and renderer
    */
    void Init();

    /**
     * Renders ( Draws ) graphics to the screen
    */
    void Render();
    void Clean();
    void Update();
    void Events();

    void PopState();
    void PushState( GameState* current );
    void ChangeState( GameState* target );

    inline bool IsRunning() const { return m_IsRunning; }
    inline void Quit() { m_IsRunning = false; }
    inline SDL_Renderer* GetRenderer() const { return m_Renderer; }

private:
    Engine();
    void LibInit();

    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    std::vector<GameState*> m_GameStates;
    bool m_IsRunning;

    static Engine* s_Instance;
};
