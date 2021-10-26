#include "Button.h"

#include "Input.h"
#include "Text.h"

Button::Button( const std::string& id )
{
    m_Label = new Text( id );
    m_TextColor = { 255, 255, 255, 255 };
    m_BkgColor = { 80, 83, 86, 255 };
    m_HoverBkgColor = { 106, 106, 106, 255 };
    m_HoverTextColor = { 255, 255, 255, 255 };
    m_ActiveBkgColor = { 0, 100, 255, 255 };
    m_ActiveTextColor = { 255, 255, 255, 255 };
    m_DisabledBkgColor = { 80, 83, 86, 0 };
    m_DisabledTextColor = { 255, 255, 255, 30 };
    m_Disabled = false;
    m_Active = false;
    m_Hover = false;
    m_Clicked = false;
}

Button::~Button()
{
    delete m_Label;
}

void Button::Render( std::string label, int x, int y, int width, int height )
{
    m_PosX = x;
    m_PosY = y;
    m_Width = width;
    m_Height = height;

    Draw( label );
}

void Button::RenderX( std::string label, int x, int y, int paddingX, int paddingY )
{
    m_PosX = x;
    m_PosY = y;
    m_Width = m_Label->GetWidth() + paddingX;
    m_Height = m_Label->GetHeight() + paddingY;

    Draw( label );
}

void Button::Draw( std::string label )
{
    CheckEvents();
    SDL_SetRenderDrawColor( Engine::Instance()->GetRenderer(), GetBkgColor().r, GetBkgColor().g, 
        GetBkgColor().b, GetBkgColor().a );
    SDL_Rect src = { m_PosX, m_PosY, m_Width, m_Height };
    SDL_RenderFillRect( Engine::Instance()->GetRenderer(), &src );

    m_Label->SetColor( GetTextColor() );
    m_Label->Draw(
        label,
        SDL_Point{ 
            m_PosX + m_Width / 2 - m_Label->GetWidth() / 2, 
            m_PosY + m_Height / 2 - m_Label->GetHeight() / 2 
        }
    );
}

void Button::CheckEvents()
{
    int mouseX, mouseY;
    SDL_GetMouseState( &mouseX, &mouseY );

    bool xOverlap = mouseX > m_PosX && ( mouseX < m_PosX + m_Width );
    bool yOverlap = mouseY > m_PosY && ( mouseY < m_PosY + m_Height );
  
    // Hover event
    if ( xOverlap && yOverlap && !m_Disabled  )
        m_Hover = true;
    else
        m_Hover = false;

    // Click event
    if ( m_Hover && Input::GetMouseButtonState( LEFT ) )
    {
        m_Clicked = true;
        m_Active = true;
    }
    else
    {
        m_Clicked = false;
        m_Active = false;
    }
}

const SDL_Color& Button::GetBkgColor() const
{
    if ( m_Hover ) return m_HoverBkgColor;
    if ( m_Active ) return m_ActiveBkgColor;
    if ( m_Disabled ) return m_DisabledBkgColor;
    return m_BkgColor;
}

const SDL_Color& Button::GetTextColor() const
{
    if ( m_Hover ) return m_HoverTextColor;
    if ( m_Active ) return m_ActiveTextColor;
    if ( m_Disabled ) return m_DisabledTextColor;
    return m_TextColor;
}

bool Button::IsClicked() const 
{
    return m_Clicked;
}

void Button::SetColor( SDL_Color bkg, SDL_Color text )
{
    m_BkgColor = bkg;
    m_TextColor = text;
} 

void Button::SetHoverColor( SDL_Color bkg, SDL_Color text )
{
    m_HoverBkgColor = bkg;
    m_HoverTextColor = text;
}

void Button::SetActiveColor( SDL_Color bkg, SDL_Color text )
{
    m_ActiveBkgColor = bkg;
    m_ActiveTextColor = text;
}

void Button::SetDisabledColor( SDL_Color bkg, SDL_Color text )
{
    m_DisabledBkgColor = bkg;
    m_DisabledTextColor = text;
}

void Button::SetActive()
{
    m_Active = true;
}

void Button::SetDisabled()
{
    m_Disabled = true;
}
