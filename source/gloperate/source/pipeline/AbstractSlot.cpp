
#include <gloperate/pipeline/AbstractSlot.h>

#include <sstream>

#include <gloperate/pipeline/Stage.h>


namespace gloperate
{


AbstractSlot::AbstractSlot(SlotType type)
: m_slotType(type)
, m_owner(nullptr)
{
}

AbstractSlot::~AbstractSlot()
{
}

SlotType AbstractSlot::slotType() const
{
    return m_slotType;
}

Stage * AbstractSlot::owner() const
{
    return m_owner;
}

std::string AbstractSlot::qualifiedName() const
{
    std::stringstream ss;

    if (m_owner)
    {
        ss << m_owner->name() << ".";
    }

    ss << name();

    return ss.str();
}


} // namespace gloperate