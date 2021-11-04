#pragma once

#include <SDL.h>
#include "Engine.h"

class BoxCollider
{
public:
    BoxCollider() {};

    void SetBuffer( int x, int y, int w, int h )
    {
        m_Buffer = { x, y, w, h };
    }

    void Set( int x, int y, int w, int h  )
    {
        m_Box = {
            x - m_Buffer.x,
            y - m_Buffer.y,
            w - m_Buffer.w,
            h - m_Buffer.h
        };
    }

    inline void Draw()
    {
        SDL_RenderDrawRect( Engine::Instance()->GetRenderer(), &m_Box );
    }

    inline SDL_Rect Get() const { return m_Box; }

private:
    SDL_Rect m_Box;
    SDL_Rect m_Buffer;
};
