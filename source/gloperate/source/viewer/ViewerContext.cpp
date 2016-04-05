
#include <gloperate/viewer/ViewerContext.h>

#include <algorithm>

#include <gloperate/viewer/Surface.h>
#include <gloperate/scripting/ScriptEnvironment.h>


namespace gloperate
{


ViewerContext::ViewerContext()
: m_timeManager(this)
, m_inputManager()
, m_scriptEnvironment(this)
{
}

ViewerContext::~ViewerContext()
{
}

const TimeManager * ViewerContext::timeManager() const
{
    return &m_timeManager;
}

TimeManager * ViewerContext::timeManager()
{
    return &m_timeManager;
}

const InputManager * ViewerContext::inputManager() const
{
    return &m_inputManager;
}

InputManager * ViewerContext::inputManager()
{
    return &m_inputManager;
}

const ScriptEnvironment * ViewerContext::scriptEnvironment() const
{
    return &m_scriptEnvironment;
}

ScriptEnvironment * ViewerContext::scriptEnvironment()
{
    return &m_scriptEnvironment;
}

void ViewerContext::registerSurface(Surface * surface)
{
    m_surfaces.push_back(surface);
}

void ViewerContext::unregisterSurface(Surface * surface)
{
    m_surfaces.erase(std::find(m_surfaces.begin(), m_surfaces.end(), surface));
}

bool ViewerContext::update()
{
    // Update timing and timers
    bool activeTimers = m_timeManager.update();

    // Update surface
    for (Surface * surface : m_surfaces)
    {
        surface->onUpdate();
    }

    // Return indicator if any more timers are running
    return activeTimers;
}

bool ViewerContext::update(float delta)
{
    // Update timing and timers
    bool activeTimers = m_timeManager.update(delta);

    // Update surface
    for (Surface * surface : m_surfaces)
    {
        surface->onUpdate();
    }

    // Return indicator if any more timers are running
    return activeTimers;
}

void ViewerContext::exit(int exitCode)
{
    // Emit signal
    this->exitApplication(exitCode);
}


} // namespace gloperate
