#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <tinyxml.h>
#include "Engine.h"

#include <string>
#include <map>

class Texture
{
public:
    static Texture* Instance()
    {
        return s_Instance = ( s_Instance != nullptr ) ? s_Instance : new Texture();
    }

    /**
     * Loads the texture from the file path and stores it in the map with a unique id
     * @returns true if its successful and false if not
    */
    bool Load( std::string id, std::string path );

    /**
     * Loads the textures from an xml file using tinyxml and stores them in the map
     * Calls the Load() function on each texture path
     * @returns true if its successful and false if not
    */
    bool ParseTextures( std::string src );

    // Remove a texture from tha map
    void Drop( std::string id );

    // Delete all textures
    void Clean(); 

    /**
	 * Draws the texture using the specified transformation with the params.
	*/
    void Draw( std::string id, int x, int y, int width, int height, float scrollRatio = 0.0f, float scaleX = 1,
        float scaleY = 1, double angle = 0.0, SDL_RendererFlip flip = SDL_FLIP_NONE );

    void DrawFrame( std::string id, int x, int y, int width, int height, int row, int frame, float scaleX = 1, 
        float scaleY = 1, double angle = 0.0, SDL_RendererFlip flip = SDL_FLIP_NONE );

    bool BlitParticle( std::string id, int x, int y, const SDL_Rect* section, const SDL_Rect* rectSize, SDL_Color color,
        SDL_BlendMode blenMode, float speed, double angle = 0.0, int pivotX = INT_MAX, int pivotY = INT_MAX );

    // Get dimensions
    const int GetHeight( std::string id );
    const int GetWidth( std::string id );

private:
    Texture() {};

    static Texture* s_Instance;
    std::map<std::string, SDL_Texture*> m_TextureMap;
    std::map<std::string, std::pair<int, int>> m_Dimension;
};
