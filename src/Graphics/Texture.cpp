#include "Texture.h"

Texture* Texture::s_Instance = nullptr;

bool Texture::Load( std::string id, std::string path )
{
    SDL_Surface* surface = IMG_Load( path.c_str() );
    if ( surface == nullptr )
    {
        SDL_Log( "Failed to load surface %s, Error: %s", path.c_str(), IMG_GetError() );
        return false;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface( Engine::Instance()->GetRenderer(), surface );
    if ( texture == nullptr )
    {
        SDL_Log( "Failed to load texture %s, Error: %s", path.c_str(), SDL_GetError() );
        return false;
    }

    m_TextureMap[id] = texture;

    return true;
}

bool Texture::ParseTextures( std::string src )
{
    TiXmlDocument xml;
    xml.LoadFile( src );
    if ( xml.Error() )
    {
        SDL_Log( "Failed to load file: %s", src.c_str() );
        return false;     
    }

    TiXmlElement* root = xml.RootElement();
    for ( TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement() )
    {
        if ( e->Value() == std::string( "texture" ) )
        {
            std::string id = e->Attribute( "id" );
			std::string src = e->Attribute( "source" );
			Load(id, src);
        }
    }
    return true;
}

void Texture::Draw( std::string id, int x, int y, int width, int height, float scrollRatio, float scaleX,
    float scaleY, double angle, SDL_RendererFlip flip )
{
    m_Dimension[id].first = width * scaleX;
    m_Dimension[id].second = height * scaleY;

    SDL_Rect src = { 0, 0, width, height };
    SDL_Rect dst = { x, y, (int)( width * scaleX ), (int)( height * scaleY ) }; 
    SDL_RenderCopyEx( Engine::Instance()->GetRenderer(), m_TextureMap[id], &src, &dst, angle, nullptr, flip );
}

void Texture::DrawFrame( std::string id, int x, int y, int width, int height, int row, int frame, int scaleX, 
    int scaleY, SDL_RendererFlip flip )
{
    m_Dimension[id].first = width * scaleX;
    m_Dimension[id].second = height * scaleY;

	SDL_Rect srcRect = { width * frame, height * row, width, height };
	SDL_Rect destRect = { x, y, (int)( width * scaleX ), (int)( height * scaleY ) };
	SDL_RenderCopyEx( Engine::Instance()->GetRenderer(), m_TextureMap[id], &srcRect, &destRect, 0.0, nullptr, flip );
}

const int Texture::GetWidth( std::string id )
{
    return m_Dimension[id].first;
}

const int Texture::GetHeight( std::string id )
{
    return m_Dimension[id].second;
}

void Texture::Drop( std::string id )
{
    SDL_DestroyTexture( m_TextureMap[id] );
    m_TextureMap.erase( id );
}

void Texture::Clean()
{
    std::map<std::string, SDL_Texture*>::iterator iterator;
    for ( iterator = m_TextureMap.begin(); iterator != m_TextureMap.end(); iterator++ )
    {
        SDL_DestroyTexture( iterator->second );
    }
    m_TextureMap.clear();
}
