#pragma once

#include <SDL.h>
#include "Engine.h"
#include "Vector2D.h"
#include "RigidBody.h"

#include <string>

enum Axis { HORIZONTAL, VERTICAL };

enum MouseButtons { LEFT, MIDDLE, RIGHT };

class Input
{
public:
    Input();
    virtual ~Input();

    /**
     * While loop that listens to the input events ( SDL_PollEvent )
     * Determines the type of event and act accordinly
    */
    void Listen();

    // Checks if a key is pressed down
    static bool GetKeyDown( SDL_Scancode key );

    // Returns event for directional keys
	static int GetAxisKey( Axis axis );

    // Returns mouse button state
    static bool GetMouseButtonState( MouseButtons button );
    static int GetMouseX() { return m_MouseX; }
    static int GetMouseY() { return m_MouseY; }

    static std::string GetDirection();
    static void ResetDirection();

private:
    static const Uint8* m_KeyState;

    void KeyUp();
    void KeyDown();

    // Mouse
    static bool m_MouseButtonStates[3];
    static std::string m_Direction;
    static int m_MouseX, m_MouseY;
};
