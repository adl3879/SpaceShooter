#include "Engine.h"

#include <iostream>
#include "SpriteAnimation.h"
#include "Vector2D.h"
#include "ObjectFactory.h"
#include "Character/Airship.h"
#include "Text.h"
#include "Audio.h"
#include "Pause.h"
#include "Menu.h"
#include "ParticleSystem.h"
#include "Emitter.h"
#include "Timer.h"

Engine* Engine::s_Instance = nullptr;
Input* m_Input = nullptr;
Emitter* emitter;

Engine::Engine() {}

void Engine::LibInit()
{
    // Initialize SDL2
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
        std::cout << "Failed to Initialize SDL. Error: " << SDL_GetError() << std::endl;
    
    // Initialize SDL2_image
    if ( !IMG_Init( IMG_INIT_PNG ) )
        std::cout << "Failed to Initialize SDL_image. Error: " << IMG_GetError() << std::endl;

    // Initialize TTF
    if ( TTF_Init() != 0 )
        std::cout << "Failed to Initialize SDL_ttf. Error: " << TTF_GetError() << std::endl;

    // Initialize mixer
    if ( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4095 ) == -1 )
        std::cout << "Failed to Initialize SDL_mixer. Error: " << Mix_GetError() << std::endl;

    // Window
    // flag makes window resizable | fullscreen
	SDL_WindowFlags window_flags = ( SDL_WindowFlags )( SDL_WINDOW_ALLOW_HIGHDPI );
    m_Window = SDL_CreateWindow(
		"2D Engine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEEN_WIDTH,
		SCREEEN_HEIGHT,
		window_flags
	);
    if ( m_Window == nullptr )
        std::cout << "Failed to create window. Error: " << SDL_GetError() << std::endl;

    // Renderer
    m_Renderer = SDL_CreateRenderer( m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if ( m_Renderer == nullptr )
        std::cout << "Failed to create renderer. Error: " << SDL_GetError() << std::endl;
}

void Engine::Init()
{
    LibInit();

    if ( !Texture::Instance()->ParseTextures( "../res/gfx/textures.xml" ) )
        SDL_Log( "Failed to load textures from xml file" );

    if ( !Audio::Instance()->Parse( "../res/sfx/audio.xml" ) )
        SDL_Log( "Failed to load sounds from xml file" );

    if ( !Text::Parse( "../res/font/fonts.xml" ) )
        SDL_Log( "Failed to load fonts from xml file" );

    ParticleSystem::Instance()->Parse( "../res/gfx/emitters.xml" );
        
    for ( auto& gameState : m_GameStates )
        gameState->Init();

    m_GameStates.push_back( new Menu() );

    m_IsRunning = true;
}

void Engine::Render()
{
    SDL_SetRenderDrawColor( m_Renderer, 255, 255, 255, 255 );
    SDL_RenderClear( m_Renderer );
    
    // Render stuff here
    m_GameStates.back()->Render();

    ParticleSystem::Instance()->PostUpdate();

    SDL_RenderPresent( m_Renderer );
}

void Engine::Update()
{
    float dt = Timer::Instance()->GetDeltaTime();
    m_GameStates.back()->Update();

    if ( Input::GetMouseButtonState( LEFT ) && Input::GetKeyDown( SDL_SCANCODE_0 ) )
    {
        int x = Input::GetMouseX();
        int y = Input::GetMouseY();
        emitter = ParticleSystem::Instance()->AddEmitter( "fire", Vector2D( x, y ) );
    }

    ParticleSystem::Instance()->Update( dt );
}

void Engine::Events()
{
    m_Input->Listen();
    Timer::Instance()->Tick();
}

void Engine::Clean()
{
    SDL_DestroyRenderer( m_Renderer );
    SDL_DestroyWindow( m_Window );
    delete m_Input;

    for ( auto& gameStates : m_GameStates )
        gameStates->Exit();

    ParticleSystem::Instance()->CleanUp();

    IMG_Quit();
    SDL_Quit();
}

void Engine::PopState()
{
    m_GameStates.back()->Exit();
    delete m_GameStates.back();
    m_GameStates.pop_back();
}

void Engine::PushState( GameState* current )
{
    m_GameStates.push_back( current );
}

void Engine::ChangeState( GameState* target )
{
    m_GameStates.back()->Exit();
    delete m_GameStates.back();
    m_GameStates.back() = target;
}
