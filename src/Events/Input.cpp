#include "Input.h"

const Uint8* Input::m_KeyState = SDL_GetKeyboardState( nullptr );
bool Input::m_MouseButtonStates[3] = { false, false, false };
std::string Input::m_Direction = "";
int Input::m_MouseX = 0;
int Input::m_MouseY = 0;

Input::Input()
{
    //
}

void Input::Listen()
{
    // GetMouseStates;
    SDL_GetMouseState( &m_MouseX, &m_MouseY );

    SDL_Event event;

    while ( SDL_PollEvent( &event ) )
    {
        switch ( event.type )
        {
        case SDL_QUIT:
            Engine::Instance()->Quit();
        break;

        case SDL_MOUSEBUTTONDOWN:
            if ( event.button.button == SDL_BUTTON_LEFT )
                m_MouseButtonStates[LEFT] = true;
            if ( event.button.button == SDL_BUTTON_MIDDLE )
                m_MouseButtonStates[MIDDLE] = true;
            if ( event.button.button == SDL_BUTTON_RIGHT )
                m_MouseButtonStates[RIGHT] = true;
        break;

        case SDL_MOUSEBUTTONUP:
            if ( event.button.button == SDL_BUTTON_LEFT )
                m_MouseButtonStates[LEFT] = false;
            if ( event.button.button == SDL_BUTTON_MIDDLE )
                m_MouseButtonStates[MIDDLE] = false;
            if ( event.button.button == SDL_BUTTON_RIGHT )
                m_MouseButtonStates[RIGHT] = false;
        break;
        }
    }
}

bool Input::GetKeyDown( SDL_Scancode key )
{
    return m_KeyState[key] == 1;
}

void Input::KeyDown()
{
    m_KeyState = SDL_GetKeyboardState( nullptr );
}

void Input::KeyUp()
{
    m_KeyState = SDL_GetKeyboardState( nullptr );
}

// return 1 or -1 according to the direction of the key pressed or 0 if nothing is pressed
int Input::GetAxisKey( Axis axis )
{
    switch ( axis )
    {
    case HORIZONTAL:
        if ( GetKeyDown( SDL_SCANCODE_D ) || GetKeyDown( SDL_SCANCODE_RIGHT ) )
        {
            m_Direction = "right";
            return 1;
        }
        if ( GetKeyDown( SDL_SCANCODE_A ) || GetKeyDown( SDL_SCANCODE_LEFT ) )
        {
            m_Direction = "left";
            return -1; 
        }
    break;

    case VERTICAL:
        if ( GetKeyDown( SDL_SCANCODE_W ) || GetKeyDown( SDL_SCANCODE_UP ) )
        {
            m_Direction = "up";
            return 1;
        }
        if ( GetKeyDown( SDL_SCANCODE_S ) || GetKeyDown( SDL_SCANCODE_DOWN ) )
        {
            m_Direction = "down";
            return -1;
        }
    break;
    
    default:
        return 0;
    break;
    }
    return 0;
}

bool Input::GetMouseButtonState( MouseButtons button )
{
    return m_MouseButtonStates[button];
}

std::string Input::GetDirection()
{
    if ( GetAxisKey( HORIZONTAL ) == BACKWARD )
        m_Direction = "left";

    if ( GetAxisKey( HORIZONTAL ) == FORWARD )
        m_Direction = "right";

    if ( GetAxisKey( VERTICAL ) == UPWARD )
        m_Direction = "down";

    if ( GetAxisKey( VERTICAL ) == DOWNWARD )
        m_Direction = "up";
    
    return m_Direction;
}

void Input::ResetDirection()
{
    m_Direction = "";
}

Input::~Input()
{
    delete m_KeyState;
}