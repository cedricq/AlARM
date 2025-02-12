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

Alarm alarm_on = {{"None", "No alarm", None, 0}, INACTIVE, NULL, NULL };

TEST(AlARM, overall_low)
{
    AlARM_Manager& alm_mgr = AlARM_Manager::GetInstance();
    alm_mgr.add(alm1);
    alm_mgr.add(alm2);
    ASSERT_EQ(2, alm_mgr.getLengthLows());
    ASSERT_EQ(0, alm_mgr.getLengthMeds());
    ASSERT_EQ(0, alm_mgr.getLengthHighs());

    alarm_on = alm_mgr.IsTriggered();

    ASSERT_EQ(Low, alarm_on.alarmId.priority);
    ASSERT_STREQ("alarm_1", alarm_on.alarmId.name.c_str());
    ASSERT_STREQ("Do nothing", alarm_on.alarmId.description.c_str());

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

    alarm_on = alm_mgr.IsTriggered();

    ASSERT_EQ(Medium, alarm_on.alarmId.priority);
    ASSERT_STREQ("alarm_4", alarm_on.alarmId.name.c_str());
    ASSERT_STREQ("Walk !", alarm_on.alarmId.description.c_str());
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

    alarm_on = alm_mgr.IsTriggered();

    ASSERT_EQ(High, alarm_on.alarmId.priority);
    ASSERT_STREQ("alarm_3", alarm_on.alarmId.name.c_str());
    ASSERT_STREQ("Run !", alarm_on.alarmId.description.c_str());
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

    alarm_on = alm_mgr.IsTriggered();
    alm_mgr.print_all_alarms();
    std::cout<<" Current => "; alarm_on.print();

    alarm_test_on = false;
    alarm_test_off = false;
    alarm_on = alm_mgr.IsTriggered();
    alm_mgr.print_active_alarms();
    std::cout<<" Current => "; alarm_on.print();
    ASSERT_EQ(High, alarm_on.alarmId.priority);
    ASSERT_STREQ("alarm_3", alarm_on.alarmId.name.c_str());
    ASSERT_STREQ("Run !", alarm_on.alarmId.description.c_str());

    alarm_test_on = true;
    alarm_test_off = false;
    alarm_on = alm_mgr.IsTriggered();
    alm_mgr.print_active_alarms();
    std::cout<<" Current => "; alarm_on.print();
    ASSERT_EQ(High, alarm_on.alarmId.priority);
    ASSERT_STREQ("alarm_test", alarm_on.alarmId.name.c_str());
    ASSERT_STREQ("Just for test", alarm_on.alarmId.description.c_str());

    alarm_test_on = true;
    alarm_test_off = true;
    alarm_on = alm_mgr.IsTriggered();
    alm_mgr.print_active_alarms();
    std::cout<<" Current => "; alarm_on.print();
    ASSERT_EQ(High, alarm_on.alarmId.priority);
    ASSERT_STREQ("alarm_test", alarm_on.alarmId.name.c_str());
    ASSERT_STREQ("Just for test", alarm_on.alarmId.description.c_str());

    alarm_test_on = false;
    alarm_test_off = false;
    alarm_on = alm_mgr.IsTriggered();
    alm_mgr.print_active_alarms();
    std::cout<<" Current => "; alarm_on.print();
    ASSERT_EQ(High, alarm_on.alarmId.priority);
    ASSERT_STREQ("alarm_test", alarm_on.alarmId.name.c_str());
    ASSERT_STREQ("Just for test", alarm_on.alarmId.description.c_str());

    alarm_test_on = false;
    alarm_test_off = true;
    alarm_on = alm_mgr.IsTriggered();
    alm_mgr.print_active_alarms();
    std::cout<<" Current => "; alarm_on.print();
    ASSERT_EQ(High, alarm_on.alarmId.priority);
    ASSERT_STREQ("alarm_3", alarm_on.alarmId.name.c_str());
    ASSERT_STREQ("Run !", alarm_on.alarmId.description.c_str());

    alm_mgr.reset();
}
