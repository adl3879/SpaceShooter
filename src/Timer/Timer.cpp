#include "Timer.h"

Timer* Timer::s_Instance = nullptr;

void Timer::Tick()
{
    m_DeltaTime = ( SDL_GetTicks() - m_LastTime ) * ( TARGET_FPS / 1000.0f );
    if ( m_DeltaTime > TARGET_DELTA_TIME )
    {
        m_DeltaTime = TARGET_DELTA_TIME;
    }
    m_LastTime = SDL_GetTicks();
}

float Timer::GetDeltaTime() const
{
    return m_DeltaTime;
}
