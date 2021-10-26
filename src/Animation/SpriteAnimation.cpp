#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation( bool repeat )
    : Animation( repeat )
{}

void SpriteAnimation::Update( float dt )
{
    m_SpriteFrame = ( SDL_GetTicks() / m_Speed ) % m_FrameCount;
}

void SpriteAnimation::Draw( float x, float y, int spriteWidth, int spriteHeight, float xScale, float yScale, 
    SDL_RendererFlip flip )
{
	Texture::Instance()->DrawFrame( m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_SpriteFrame, 
        xScale, yScale, flip );
}

void SpriteAnimation::SetProps(std::string textureID, int spriteRow, int frameCount, int speed)
{
	m_TextureID = textureID;
	m_SpriteRow = spriteRow;
	m_FrameCount = frameCount;
	m_Speed = speed;
}

int SpriteAnimation::GetCurrentSpriteRow() const
{
    return m_SpriteRow;
}

void SpriteAnimation::SetSpriteRow( int row )
{
    m_SpriteRow = row;
}

void SpriteAnimation::IncrSpriteRow()
{
    m_SpriteRow++;
}

void SpriteAnimation::DecrSpriteRow()
{
    m_SpriteRow--;
}
