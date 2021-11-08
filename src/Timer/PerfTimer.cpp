#include "PerfTimer.h"

#include <SDL_timer.h>

uint64_t PerfTimer::m_Frequency = 0;

PerfTimer::PerfTimer()
{
    if ( m_Frequency == 0 )
        m_Frequency = SDL_GetPerformanceFrequency();
    
    Start();
}

void PerfTimer::Start()
{
    m_StartedAt = SDL_GetPerformanceCounter();
}

double PerfTimer::ReadMs() const
{
    return 1000.0 * ( static_cast<double>( SDL_GetPerformanceCounter() - m_StartedAt ) /  static_cast<double>( m_Frequency ) );
}

uint64_t PerfTimer::ReadTicks() const
{
    return SDL_GetPerformanceCounter() - m_StartedAt;
}
