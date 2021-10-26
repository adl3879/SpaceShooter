#include "Audio.h"

Audio* Audio::s_Instance = nullptr;

void Audio::LoadMusic( std::string id, std::string path )
{
    Mix_Music* music = Mix_LoadMUS( path.c_str() );
    if ( music == nullptr )
        SDL_Log( "Failed to load music %s. error: ", path.c_str(), Mix_GetError() );

    m_Music[id] = music;  
}

void Audio::LoadSound( std::string id, std::string path )
{
    Mix_Chunk* sound = Mix_LoadWAV( path.c_str() );
    if ( sound == nullptr )
        SDL_Log( "Failed to load sound %s. error: ", path.c_str(), Mix_GetError() );

    m_Sounds[id] = sound;
}

bool Audio::Parse( std::string source )
{
    TiXmlDocument xml;
    xml.LoadFile( source );
    if ( xml.Error() )
    {
        SDL_Log( "Failed to load %s", source.c_str() );
        return false;
    }
    
    TiXmlElement* root;
    root = xml.RootElement();
    for ( TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement() )
    {
        std::string id, path;

        if ( e->Value() )
        {
            id = e->Attribute( "id" );
            path = e->Attribute( "source" );

            if ( e->Value() == std::string( "music" ) )
                LoadMusic( id, path );
            else if ( e->Value() == std::string( "sound" ) )
                LoadSound( id, path );
        }
    }

    return true;
}

void Audio::Play( std::string id )
{
    if ( Mix_PlayChannel( -1, m_Sounds[id], 0 ) == -1 )
        SDL_Log( "Failed to play sound!" );
}

void Audio::PlayMusic( std::string id )
{
    if ( Mix_PlayingMusic() == 0 )
    {
        if ( Mix_PlayMusic( m_Music[id], -1 ) == -1 )
        SDL_Log( "Failed to play music!" );
    }
}

void Audio::Clean()
{
    std::map<std::string, Mix_Chunk*>::iterator it;
    for ( it = m_Sounds.begin(); it != m_Sounds.end(); it++ )
    {
        Mix_FreeChunk( it->second );
        delete it->second;
    }
    
    std::map<std::string, Mix_Music*>::iterator it2;
    for ( it2 = m_Music.begin(); it2 != m_Music.end(); it2++ )
    {
        Mix_FreeMusic( it2->second );
        delete it->second;
    }
    m_Music.clear();
    m_Sounds.clear();

    Mix_CloseAudio();
}
