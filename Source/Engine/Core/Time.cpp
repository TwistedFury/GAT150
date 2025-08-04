#pragma once
#include "Time.h"

namespace swaws
{
    /// <summary>
    /// Updates the time and delta time for the current frame.
    /// </summary>
    void Time::Tick()
    {
        auto now = clock::now();
        m_deltaTime = std::chrono::duration<float>(now - m_frameTime).count();
        m_time = std::chrono::duration<float>(now - m_startTime).count();
        m_frameTime = now;
    }
}
