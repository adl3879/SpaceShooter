#pragma once

#include <SDL.h>
#include "Engine.h"
#include "Vector2D.h"

class CollisionHandler
{
public:
    static CollisionHandler* Instance()
    {
        return s_Instance = ( s_Instance != nullptr ) ? s_Instance : new CollisionHandler();
    }

    /**
     * Checks if two boxes overlap
     * @param a dimension and position of first box
     * @param b dimension and position of second box
    */
    bool CheckBoxCollision( SDL_Rect a, SDL_Rect b ) const;

    bool CheckBoundary( const Vector2D& pos ) const;

private:
    CollisionHandler() {}

    static CollisionHandler* s_Instance;

};
