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
    SDL_Rect dst = { x, y, static_cast<int>( width * scaleX ), static_cast<int>( height * scaleY ) }; 
    SDL_RenderCopyEx( Engine::Instance()->GetRenderer(), m_TextureMap[id], &src, &dst, angle, nullptr, flip );
}

void Texture::DrawFrame( std::string id, int x, int y, int width, int height, int row, int frame, float scaleX, 
    float scaleY, double angle, SDL_RendererFlip flip )
{
    m_Dimension[id].first = width * scaleX;
    m_Dimension[id].second = height * scaleY;

	SDL_Rect src = { width * frame, height * row, width, height };
	SDL_Rect dst = { x, y, static_cast<int>( width * scaleX ), static_cast<int>( height * scaleY ) };
	SDL_RenderCopyEx( Engine::Instance()->GetRenderer(), m_TextureMap[id], &src, &dst, angle, nullptr, flip );
}

bool Texture::BlitParticle( std::string id, int x, int y, const SDL_Rect* section, const SDL_Rect* rectSize, SDL_Color color,
    SDL_BlendMode blenMode, float speed, double angle, int pivotX, int pivotY )
{
    // unsigned int scale = 

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;

    if ( rectSize != nullptr )
    {
        rect.w = rectSize->w;
        rect.h = rectSize->h;
    }
    else if ( section != nullptr )
    {
        rect.w = section->w;
        rect.h = section->h;
    }
    else
    {
        SDL_QueryTexture( m_TextureMap[id], nullptr, nullptr, &rect.w, &rect.h );
    }

    int px = rect.w / 2;
    int py = rect.h / 2;

    // rect.w *= scale
    // rect.h *= scale

    SDL_Point* p = nullptr;
    SDL_Point pivot;
    pivot.x = px;
    pivot.y = py;
    p = &pivot;

    if ( SDL_SetTextureColorMod( m_TextureMap[id], color.r, color.g, color.b ) != 0 );
        // SDL_Log( "Cannot set texture color mode. Error: %s", SDL_GetError() );

    if ( SDL_SetTextureAlphaMod( m_TextureMap[id], color.a ) != 0 )
        SDL_Log( "Cannot set texture alpha mode. Error: %s", SDL_GetError() );

    if ( SDL_SetTextureBlendMode( m_TextureMap[id], blenMode ) != 0 )
        SDL_Log( "Cannot set texture blend mode. Error: %s", SDL_GetError() );

    if ( SDL_RenderCopyEx( Engine::Instance()->GetRenderer(), m_TextureMap[id], section, &rect, angle, nullptr, SDL_FLIP_NONE ) != 0 )
    {
        SDL_Log( "Cannot set texture alpha mode. Error: %s", SDL_GetError() );
        return true;
    }

    return false;    
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
