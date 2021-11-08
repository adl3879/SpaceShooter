#pragma once

#include "Engine.h"

class PerfTimer
{
public:
    PerfTimer();

    void Start();
    double ReadMs() const;
    uint64_t ReadTicks() const;

private:
    uint64_t m_StartedAt;
    static uint64_t m_Frequency;
};
