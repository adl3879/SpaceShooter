#pragma once

#include <SDL.h>

const int TARGET_FPS = 60;
const float TARGET_DELTA_TIME = 1.5f;

class Timer
{
public:
    // Returns single Instance of "Timer"
    static Timer* Instance()
	{
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Timer();
	}

    /**
	 * Measures the time between this call and the previous call,
	 * and updates internal values accordingly.
	 **/
    void Tick();
    
    /**
	 * Gets the time between the last two frames, assuming step is called
	 * each frame.
	 **/
    float GetDeltaTime() const;

private:
    Timer() {};

    static Timer* s_Instance;
    float m_DeltaTime;
    float m_LastTime;
};
 
