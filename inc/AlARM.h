#ifndef AlARM_H_
#define AlARM_H_

#include <functional>

#include "NameString.h"

namespace AlARM
{
#define MAKE_ALARM(name, name_str, prio, subprio, triggerON, triggerOFF)  Alarm const name { { name_str }, prio, subprio, triggerON, triggerOFF}

enum Priority { High = 1, Medium, Low };

struct AlarmId
{
    core::NameString name;

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
};

class AlARM_Manager
{
public:
	static AlARM_Manager& GetInstance();
    virtual ~AlARM_Manager() {};

private:
    AlARM_Manager() {};
};




} // namespace

#endif
