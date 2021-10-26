#pragma once

#include "Object.h"
#include <SDL.h>

#include <string>
#include "Vector2D.h"

struct Props
{
public:
    Props( std::string textureID, float x, float y, int width, int height, 
        SDL_RendererFlip flip = SDL_FLIP_NONE )
    {
        TextureID = textureID;
        X = x;
        Y = y;
        Width = width;
        Height = height;
        Flip = flip;
    }

public:
    int Width, Height;
    float X, Y;
    std::string TextureID;
    SDL_RendererFlip Flip;
};

class GameObject : public Object
{
public:
    GameObject() {}
    GameObject( Props* props )
    {
        m_Transform = new Vector2D( props->X, props->Y );
        m_Width = props->Width;
        m_Height = props->Height;
        m_Flip = props->Flip;
        m_TextureID = props->TextureID;
    }

    virtual void Update( float dt ) = 0;
    virtual void Draw() = 0;
    virtual void Clean() = 0;

protected:
    Vector2D* m_Transform;
    int m_Width, m_Height;
    std::string m_TextureID;
    SDL_RendererFlip m_Flip;
};
