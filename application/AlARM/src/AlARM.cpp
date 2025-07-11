#include "AlARM.h"

namespace AlARM
{

AlARM_Manager& AlARM_Manager::GetInstance()
{
    static AlARM_Manager alm_mgr;  // GCOVR_EXCL_LINE
    return alm_mgr;
}

void AlARM_Manager::add(Alarm& alm)
{
    switch (alm.alarmId.priority)
    {
    case Priority::Low:
        lows.push_back(std::make_unique<Alarm>(alm)); // GCOVR_EXCL_LINE
        break;
    case Priority::Medium:
        meds.push_back(std::make_unique<Alarm>(alm)); // GCOVR_EXCL_LINE
        break;
    case Priority::High:
    default:
        highs.push_back(std::make_unique<Alarm>(alm)); // GCOVR_EXCL_LINE
        break;
    }
}


Alarm const& AlARM_Manager::IsTriggered(std::vector<std::unique_ptr<Alarm>>& vec)
{
    Alarm* alarm_on = nullptr;
    int subprio = INT16_MAX;

    for (auto& alm : vec)
    {
        if (alm->triggerON != nullptr && alm->triggerOFF != nullptr)
        {
            if ( alm->triggerON() ) // GCOVR_EXCL_LINE
            {
                alm->state = ACTIVE;
            }
            else if ( alm->triggerOFF() ) // GCOVR_EXCL_LINE
            {
                alm->state = INACTIVE;            
            }
        }
        else
        {
            std::cout<<"No trigger function for alarm " <<alm->alarmId.name.c_str() <<std::endl; // GCOVR_EXCL_LINE
        }

        if ( alm->state == ACTIVE && alm->alarmId.subPriority < subprio )
        {
            subprio = alm->alarmId.subPriority;
            alarm_on = alm.get();
        }
    }

    if (alarm_on) return *alarm_on;

    static Alarm NO_ALARM = {{"None", "No alarm", Priority::None, 0}, INACTIVE, nullptr, nullptr }; // GCOVR_EXCL_LINE
    return NO_ALARM;
}


Alarm const& AlARM_Manager::IsTriggered()
{
    Alarm const& alarm_on_high = IsTriggered(highs);
    if (alarm_on_high.alarmId.priority != Priority::None) 
    {
        return alarm_on_high ;
    }

    Alarm const& alarm_on_med  = IsTriggered(meds);
    if (alarm_on_med.alarmId.priority != Priority::None) 
    {
        return alarm_on_med ;
    }
    
    return IsTriggered(lows);
}


void AlARM_Manager::reset()
{
    lows.clear();
    meds.clear();
    highs.clear();
}


void AlARM_Manager::print_alarms(std::vector<std::unique_ptr<Alarm>>& vec, bool active_only)
{
    for (auto& alm : vec)
    {
        if (!active_only || alm->state == ACTIVE)
        {
            alm->print(); // GCOVR_EXCL_LINE
        }
    }
}

void AlARM_Manager::print_all_alarms()
{
    std::cout << "*** ALL alarms : " << std::endl;
    print_alarms(lows, false);
    print_alarms(meds, false);
    print_alarms(highs, false);
}

void AlARM_Manager::print_active_alarms()
{
    std::cout << "*** ACTIVE alarms : " << std::endl;
    print_alarms(lows, true);
    print_alarms(meds, true);
    print_alarms(highs, true);
}

}

