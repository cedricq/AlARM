#include "AlARM.h"

namespace AlARM
{

static AlARM_Manager& AlARM_Manager::GetInstance()
{
    static AlARM_Manager alm_mgr;
    return alm_mgr;
}

void AlARM_Manager::add(Alarm const& alm)
{
    switch (alm.priority)
    {
    case Low:
        lows.push_back(std::make_unique<Alarm>(alm));
        break;
    case Medium:
        meds.push_back(std::make_unique<Alarm>(alm));
        break;
    case High:
    default:
        highs.push_back(std::make_unique<Alarm>(alm));
        break;
    }
}


Alarm const& AlARM_Manager::IsTriggered(std::vector<std::unique_ptr<Alarm>>& vec)
{
    Alarm* alarm_on = nullptr;
    int subprio = INT16_MAX;

    for (auto& alm : vec)
    {
        if (alm->triggerON() && alm->subPriority < subprio)
        {
            subprio = alm->subPriority;
            alarm_on = alm.get();
        }
    }

    if (alarm_on) return *alarm_on;
    return NO_ALARM;
}


Alarm const& AlARM_Manager::IsTriggered()
{
    Alarm const& alarm_on_high = IsTriggered(highs);
    if (alarm_on_high.priority != None) return alarm_on_high ;

    Alarm const& alarm_on_med  = IsTriggered(meds);
    if (alarm_on_med.priority != None) return alarm_on_med ;

    Alarm const& alarm_on_low  = IsTriggered(lows);
    if (alarm_on_low.priority != None) return alarm_on_low ;

    return NO_ALARM;
}

void AlARM_Manager::reset()
{
    lows.clear();
    meds.clear();
    highs.clear();
}

}

