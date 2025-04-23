#include <gtest/gtest.h>

#include "AlARM.h"

#include <iostream>

using namespace AlARM;

MAKE_ALARM(alm1, "alarm_1", "Do nothing", Low, 1, INACTIVE, []()->bool_t {return true;}, []()->bool_t {return false; });
MAKE_ALARM(alm2, "alarm_2", "Call maintenance", Low, 2, INACTIVE, []()->bool_t {return true;}, []()->bool_t {return false; });
MAKE_ALARM(alm3, "alarm_3", "Run !", High, 2, INACTIVE, []()->bool_t {return true;}, []()->bool_t {return false; });
MAKE_ALARM(alm4, "alarm_4", "Walk !", Medium, 1, INACTIVE, []()->bool_t {return true;}, []()->bool_t {return false; });
MAKE_ALARM(alm5, "alarm_5", "Walk !", Medium, 0, INACTIVE, []()->bool_t {return false;}, []()->bool_t {return false; });
MAKE_ALARM(alm6, "alarm_6", "Run !", High, 1, INACTIVE, []()->bool_t {return false;}, []()->bool_t {return false; });

bool_t alarm_test_on = false;
bool_t alarm_test_off = false;
MAKE_ALARM(alm_test, "alarm_test", "Just for test", High, 0, INACTIVE, []()->bool_t {return alarm_test_on;}, []()->bool_t {return alarm_test_off; });

TEST(AlARM, creation)
{
    ASSERT_STREQ("alarm_1", alm1.alarmId.name.c_str());
    ASSERT_EQ(Low, alm1.alarmId.priority);
    ASSERT_EQ(1, alm1.alarmId.subPriority);
    ASSERT_TRUE(alm1.triggerON());
    ASSERT_FALSE(alm1.triggerOFF());
}

TEST(AlARM, overall_low)
{
    AlARM_Manager& alm_mgr = AlARM_Manager::GetInstance();
    alm_mgr.add(alm1);
    alm_mgr.add(alm2);
    ASSERT_EQ(2, alm_mgr.getLengthLows());
    ASSERT_EQ(0, alm_mgr.getLengthMeds());
    ASSERT_EQ(0, alm_mgr.getLengthHighs());

    const Alarm alm = alm_mgr.IsTriggered();

    ASSERT_EQ(Low, alm.alarmId.priority);
    ASSERT_STREQ("alarm_1", alm.alarmId.name.c_str());
    ASSERT_STREQ("Do nothing", alm.alarmId.description.c_str());

    alm_mgr.reset();
}

TEST(AlARM, overall_med)
{
    AlARM_Manager& alm_mgr = AlARM_Manager::GetInstance();
    alm_mgr.add(alm1);
    alm_mgr.add(alm2);
    alm_mgr.add(alm4);
    alm_mgr.add(alm5);
    alm_mgr.add(alm6);
    ASSERT_EQ(2, alm_mgr.getLengthLows());
    ASSERT_EQ(2, alm_mgr.getLengthMeds());
    ASSERT_EQ(1, alm_mgr.getLengthHighs());

    const Alarm alm = alm_mgr.IsTriggered();

    ASSERT_EQ(Medium, alm.alarmId.priority);
    ASSERT_STREQ("alarm_4", alm.alarmId.name.c_str());
    ASSERT_STREQ("Walk !", alm.alarmId.description.c_str());
    alm_mgr.reset();
}

TEST(AlARM, overall_high)
{
    AlARM_Manager& alm_mgr = AlARM_Manager::GetInstance();
    alm_mgr.add(alm1);
    alm_mgr.add(alm2);
    alm_mgr.add(alm3);
    alm_mgr.add(alm4);
    alm_mgr.add(alm5);
    alm_mgr.add(alm6);
    ASSERT_EQ(2, alm_mgr.getLengthLows());
    ASSERT_EQ(2, alm_mgr.getLengthMeds());
    ASSERT_EQ(2, alm_mgr.getLengthHighs());

    const Alarm alm = alm_mgr.IsTriggered();

    ASSERT_EQ(High, alm.alarmId.priority);
    ASSERT_STREQ("alarm_3", alm.alarmId.name.c_str());
    ASSERT_STREQ("Run !", alm.alarmId.description.c_str());

    alm_mgr.print_all_alarms();
    alm_mgr.reset();
}

TEST(AlARM, no_alarm)
{
    AlARM_Manager& alm_mgr = AlARM_Manager::GetInstance();
    const Alarm alm = alm_mgr.IsTriggered();
    const Alarm NO_ALARM = {{"None", "No alarm", None, 0}, INACTIVE, NULL, NULL };
    ASSERT_EQ(None, alm.alarmId.priority);
    ASSERT_STREQ("None", alm.alarmId.name.c_str());
    ASSERT_STREQ("No alarm", alm.alarmId.description.c_str());
    alm_mgr.reset();
}

TEST(AlARM, activation)
{
    AlARM_Manager& alm_mgr = AlARM_Manager::GetInstance();
    alm_mgr.add(alm1);
    alm_mgr.add(alm2);
    alm_mgr.add(alm3);
    alm_mgr.add(alm4);
    alm_mgr.add(alm5);
    alm_mgr.add(alm6);
    alm_mgr.add(alm_test);
    ASSERT_EQ(2, alm_mgr.getLengthLows());
    ASSERT_EQ(2, alm_mgr.getLengthMeds());
    ASSERT_EQ(3, alm_mgr.getLengthHighs());

    const Alarm alm = alm_mgr.IsTriggered();
    alm_mgr.print_all_alarms();
    std::cout<<"Current => "; alm.print();

    alarm_test_on = false;
    alarm_test_off = false;
    const Alarm alarm1 = alm_mgr.IsTriggered();
    ASSERT_EQ(High, alarm1.alarmId.priority);
    ASSERT_STREQ("alarm_3", alarm1.alarmId.name.c_str());
    ASSERT_STREQ("Run !", alarm1.alarmId.description.c_str());

    alarm_test_on = true;
    alarm_test_off = false;
    const Alarm alarm2 = alm_mgr.IsTriggered();
    ASSERT_EQ(High, alarm2.alarmId.priority);
    ASSERT_STREQ("alarm_test", alarm2.alarmId.name.c_str());
    ASSERT_STREQ("Just for test", alarm2.alarmId.description.c_str());

    alarm_test_on = true;
    alarm_test_off = true;
    const Alarm alarm3 = alm_mgr.IsTriggered();
    ASSERT_EQ(High, alarm3.alarmId.priority);
    ASSERT_STREQ("alarm_test", alarm3.alarmId.name.c_str());
    ASSERT_STREQ("Just for test", alarm3.alarmId.description.c_str());

    alarm_test_on = false;
    alarm_test_off = false;
    const Alarm alarm4 = alm_mgr.IsTriggered();
    ASSERT_EQ(High, alarm4.alarmId.priority);
    ASSERT_STREQ("alarm_test", alarm4.alarmId.name.c_str());
    ASSERT_STREQ("Just for test", alarm4.alarmId.description.c_str());

    alarm_test_on = false;
    alarm_test_off = true;
    const Alarm alarm5 = alm_mgr.IsTriggered();
    ASSERT_EQ(High, alarm5.alarmId.priority);
    ASSERT_STREQ("alarm_3", alarm5.alarmId.name.c_str());
    ASSERT_STREQ("Run !", alarm5.alarmId.description.c_str());

    alm_mgr.reset();
}
