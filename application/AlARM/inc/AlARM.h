#ifndef AlARM_H_
#define AlARM_H_

#include "NameString.h"

#include <functional>
#include <memory>
#include <vector>
#include <iostream>

namespace AlARM
{

enum class Priority { None = 0, High = 1, Medium = 2, Low = 3 };
enum State { INACTIVE = 1, ACTIVE = 2 };

#define MAKE_ALARM(name, name_str, desc_str, prio, subprio, state, triggerON, triggerOFF)  Alarm name { { name_str, desc_str, prio, subprio }, state, triggerON, triggerOFF}

struct AlarmId
{
    core::NameString name;
    core::NameString description;
    Priority priority;
    int subPriority;
};

struct Alarm
{
    AlarmId const alarmId;
    State state;
    std::function<bool()> triggerON;
    std::function<bool()> triggerOFF;

    void print() const {
        char * state_str = nullptr;
        char active[] = "ACTVE";
        char inactive[] = "INACTVE";
        (state == ACTIVE) ? state_str = active : state_str = inactive; 

        char * prio_str = nullptr;
        char low[] = "LOW";
        char medium[] = "MEDIUM";
        char high[] = "HIGH";
        (alarmId.priority == Priority::Low) ? prio_str = low : (alarmId.priority == Priority::Medium) ? prio_str = medium : prio_str = high;  // GCOVR_EXCL_LINE
        std::cout<<alarmId.name.c_str() <<" - " <<alarmId.description.c_str() <<" - " <<state_str <<" - " <<prio_str <<"-" <<alarmId.subPriority <<std::endl;  // GCOVR_EXCL_LINE
    }
};

class AlARM_Manager
{
public:
    static AlARM_Manager& GetInstance();
    ~AlARM_Manager() {};

    void add(Alarm& alm);
    Alarm const& IsTriggered();

    int getLengthLows() { return lows.size(); };
    int getLengthMeds() { return meds.size(); };
    int getLengthHighs() { return highs.size(); };

    void reset();

    void print_all_alarms();
    void print_active_alarms();

private:
    AlARM_Manager() {};

    Alarm const& IsTriggered(std::vector<std::unique_ptr<Alarm>>& vec);
    void print_alarms(std::vector<std::unique_ptr<Alarm>>& vec, bool active_only);

    std::vector<std::unique_ptr<Alarm>> lows;
    std::vector<std::unique_ptr<Alarm>> meds;
    std::vector<std::unique_ptr<Alarm>> highs;
};

} // namespace

#endif
