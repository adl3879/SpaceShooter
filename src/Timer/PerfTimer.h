#pragma once

#include "Engine.h"

class PerfTimer
{
public:
    PerfTimer();

    void Start();
    double ReadMs() const;
    unsigned int ReadTicks() const;

private:
    unsigned int m_StartedAt;
    static unsigned int m_Frequency;
};
