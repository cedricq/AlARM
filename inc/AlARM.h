#ifndef AlARM_H_
#define AlARM_H_

#include <functional>
#include <memory>
#include <vector>

#include "NameString.h"
#include <iostream>

namespace AlARM
{
enum Priority { High = 1, Medium, Low, None };

#define MAKE_ALARM(name, name_str, desc_str, prio, subprio, triggerON, triggerOFF)  Alarm const name { { name_str, desc_str }, prio, subprio, triggerON, triggerOFF}

struct AlarmId
{
    core::NameString name;
    core::NameString description;

    bool operator==(AlarmId const& other) const
    {
        return (name == other.name);
    }

    bool operator!=(AlarmId const& other) const
    {
        return not (*this == other);
    }
};

struct Alarm
{
    AlarmId alarmId;
    Priority priority;
    int subPriority;
    std::function<bool()> triggerON;
    std::function<bool()> triggerOFF;

    void print() {
        std::cout<<alarmId.name.c_str() <<" - " <<alarmId.description.c_str() <<" - Prio " <<priority <<"-" <<subPriority <<std::endl;
    }
};

Alarm const NO_ALARM {{"None", "No alarm"}, None, 0, NULL, NULL };

class AlARM_Manager
{
public:
    static AlARM_Manager& GetInstance();
    virtual ~AlARM_Manager() {};

    void add(Alarm const& alm);
    Alarm const& IsTriggered();

    int getLengthLows() { return lows.size(); };
    int getLengthMeds() { return meds.size(); };
    int getLengthHighs() { return highs.size(); };

    void reset();

private:
    AlARM_Manager() {};
    Alarm const& IsTriggered(std::vector<std::unique_ptr<Alarm>>& vec);

    std::vector<std::unique_ptr<Alarm>> lows;
    std::vector<std::unique_ptr<Alarm>> meds;
    std::vector<std::unique_ptr<Alarm>> highs;
};

} // namespace

#endif
