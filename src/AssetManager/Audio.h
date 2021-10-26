#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <tinyxml.h>

#include <string>
#include <map>

class Audio
{
public:
    static Audio* Instance()
    {
        return s_Instance = ( s_Instance != nullptr ) ? s_Instance : new Audio();
    }

    void Play( std::string id );
    void PlayMusic( std::string id );

    bool Parse( std::string source );
    void Drop( std::string id );
    void Clean();

private:
    Audio() {}
    void LoadMusic( std::string id, std::string path );
    void LoadSound( std::string id, std::string path );

    std::map<std::string, Mix_Music*> m_Music;
    std::map<std::string, Mix_Chunk*> m_Sounds;

    static Audio* s_Instance;
};
