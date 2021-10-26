#pragma once

#include <SDL.h>

#include "Texture.h"

class Animation
{
public:
    /**
     * Constructor sets m_Repeat to given param and m_IsEnded to false (animation is just started)
     * @param repeat If the animation is to be repeated or not
    */
    Animation( bool repeat = true ): m_Repeat( repeat ) { m_IsEnded = false; }

    /**
     * Pure virtual
     * Draws a sprite to the screen after each frame
     * @param dt Delta time ( time passed after each frame )
    */
    virtual void Update( float dt ) = 0;

    // Getter function for m_IsEnded
    inline bool IsEnded() const { return m_IsEnded; }

protected:
    int m_CurrentFrame;
    bool m_IsEnded;
    bool m_Repeat;
};
