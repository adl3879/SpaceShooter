#pragma once

#include "Animation.h"

#include <string>

class SpriteAnimation : public Animation
{
public:
    /**
     * Constructor
     * @param repeat If the animation is to be repeated or not
    */
    SpriteAnimation( bool repeat = true );

    /**
     * Draws a sprite to the screen after each frame
     * @param dt Delta time ( time passed after each frame )
    */
    virtual void Update( float dt );

    // Draw Animation sprites to screen
    void Draw( float x, float y, int spriteWidth, int spriteHeight, float xScale = 1.0f, float yScale = 1.0f, 
        double angle = 0.0, SDL_RendererFlip flip = SDL_FLIP_NONE );

    /**
     * Sets properties required for animation
    */
	void SetProps( std::string textureID, int spriteRow, int frameCount, int speed );

	int GetCurrentSpriteRow() const;
	void SetSpriteRow( int row );
	void IncrSpriteRow();
	void DecrSpriteRow();

private:
    int m_Speed;
    int m_SpriteRow;
    int m_FrameCount;
	int m_SpriteFrame;
	std::string m_TextureID;
};
