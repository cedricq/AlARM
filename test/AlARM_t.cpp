#include <gtest/gtest.h>

#include "AlARM.h"

#include <iostream>

using namespace AlARM;

MAKE_ALARM(alm1, "alarm_1", "Do nothing", Low, 1, []()->bool_t {return true;}, []()->bool_t {return false; });
MAKE_ALARM(alm2, "alarm_2", "Call maintenance", Low, 2, []()->bool_t {return true;}, []()->bool_t {return false; });
MAKE_ALARM(alm3, "alarm_3", "Run !", High, 1, []()->bool_t {return true;}, []()->bool_t {return false; });
MAKE_ALARM(alm4, "alarm_4", "Walk !", Medium, 1, []()->bool_t {return true;}, []()->bool_t {return false; });
MAKE_ALARM(alm5, "alarm_5", "Walk !", Medium, 0, []()->bool_t {return false;}, []()->bool_t {return false; });
MAKE_ALARM(alm6, "alarm_6", "Run !", High, 0, []()->bool_t {return false;}, []()->bool_t {return false; });

TEST(AlARM, creation)
{
    ASSERT_STREQ("alarm_1", alm1.alarmId.name.c_str());
    ASSERT_EQ(Low, alm1.priority);
    ASSERT_EQ(1, alm1.subPriority);
    ASSERT_TRUE(alm1.triggerON());
    ASSERT_FALSE(alm1.triggerOFF());
}

Alarm alarm_on = NO_ALARM;

TEST(AlARM, overall_low)
{
    AlARM_Manager& alm_mgr = AlARM_Manager::GetInstance();
    alm_mgr.add(alm1);
    alm_mgr.add(alm2);
    ASSERT_EQ(2, alm_mgr.getLengthLows());
    ASSERT_EQ(0, alm_mgr.getLengthMeds());
    ASSERT_EQ(0, alm_mgr.getLengthHighs());

    alarm_on = alm_mgr.IsTriggered();

    ASSERT_EQ(Low, alarm_on.priority);
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

    ASSERT_EQ(Medium, alarm_on.priority);
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

    ASSERT_EQ(High, alarm_on.priority);
    ASSERT_STREQ("alarm_3", alarm_on.alarmId.name.c_str());
    ASSERT_STREQ("Run !", alarm_on.alarmId.description.c_str());
    alm_mgr.reset();
}
