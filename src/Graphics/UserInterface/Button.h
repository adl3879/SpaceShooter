#pragma once

#include "Engine.h"
#include "Text.h"

class Button
{
public:
    Button() {};
    Button( const std::string& id );
    virtual ~Button();

    void Render( std::string label, int x, int y, int width, int height );
    void RenderX( std::string label, int x, int y, int paddingX = 10, int paddingY = 6 );

    void SetColor( SDL_Color bkg, SDL_Color text );
    void SetHoverColor( SDL_Color bkg, SDL_Color text );
    void SetActiveColor( SDL_Color bkg, SDL_Color text );
    void SetDisabledColor( SDL_Color bkg, SDL_Color text );

    void SetActive();
    void SetDisabled();

    bool IsClicked() const;

private:
    void CheckEvents();
    const SDL_Color& GetBkgColor() const;
    const SDL_Color& GetTextColor() const;
    void Draw( std::string label );

private:
    Text* m_Label;
    bool m_Active, m_Hover, m_Disabled, m_Clicked;
    SDL_Color m_BkgColor, m_TextColor;
    SDL_Color m_HoverBkgColor, m_HoverTextColor;
    SDL_Color m_ActiveBkgColor, m_ActiveTextColor;
    SDL_Color m_DisabledBkgColor, m_DisabledTextColor;
    int m_Width, m_Height;
    int m_PosX, m_PosY;
};
