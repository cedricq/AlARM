#include "AlARM.h"

namespace AlARM
{

static AlARM_Manager& AlARM_Manager::GetInstance()
{
    static AlARM_Manager alm_mgr;
    return alm_mgr;
}

void AlARM_Manager::add(Alarm& alm)
{
    switch (alm.alarmId.priority)
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


Alarm& AlARM_Manager::IsTriggered(std::vector<std::unique_ptr<Alarm>>& vec)
{
    Alarm* alarm_on = nullptr;
    int subprio = INT16_MAX;

    for (auto& alm : vec)
    {
        if ( alm->triggerON() ) alm->state = ACTIVE;
        else if ( alm->triggerOFF() ) alm->state = INACTIVE;

        if ( alm->state == ACTIVE && alm->alarmId.subPriority < subprio )
        {
            subprio = alm->alarmId.subPriority;
            alarm_on = alm.get();
        }
    }

    if (alarm_on) return *alarm_on;

    static Alarm NO_ALARM = {{"None", "No alarm", None, 0}, INACTIVE, NULL, NULL };
    return NO_ALARM;
}


Alarm& AlARM_Manager::IsTriggered()
{
    Alarm& alarm_on_high = IsTriggered(highs);
    if (alarm_on_high.alarmId.priority != None) return alarm_on_high ;

    Alarm& alarm_on_med  = IsTriggered(meds);
    if (alarm_on_med.alarmId.priority != None) return alarm_on_med ;

    return IsTriggered(lows);
}


void AlARM_Manager::reset()
{
    lows.clear();
    meds.clear();
    highs.clear();
}

}

