#include <gtest/gtest.h>

#include "AlARM.h"

#include <iostream>

using namespace AlARM;

MAKE_ALARM(alm1, "alarm_1", "Do nothing", Priority::Low, 1, INACTIVE, []()->bool_t {return true;}, []()->bool_t {return false; });
MAKE_ALARM(alm2, "alarm_2", "Call maintenance", Priority::Low, 2, INACTIVE, []()->bool_t {return true;}, []()->bool_t {return false; });
MAKE_ALARM(alm3, "alarm_3", "Run !", Priority::High, 2, INACTIVE, []()->bool_t {return true;}, []()->bool_t {return false; });
MAKE_ALARM(alm4, "alarm_4", "Walk !", Priority::Medium, 1, INACTIVE, []()->bool_t {return true;}, []()->bool_t {return false; });
MAKE_ALARM(alm5, "alarm_5", "Walk !", Priority::Medium, 0, INACTIVE, []()->bool_t {return false;}, []()->bool_t {return false; });
MAKE_ALARM(alm6, "alarm_6", "Run !", Priority::High, 1, INACTIVE, []()->bool_t {return false;}, []()->bool_t {return false; });
MAKE_ALARM(alm7, "alarm_7", "Trigger OFF", Priority::Low, 10, ACTIVE, []()->bool_t {return false;}, []()->bool_t {return true; });

MAKE_ALARM(almDefective, "alarm_defective", "Defective alarm !", Priority::None, 1, INACTIVE, nullptr, nullptr);
MAKE_ALARM(almDefective_no_act, "alarm_defective_no_act", "Defective alarm !", Priority::None, 1, INACTIVE, nullptr, []()->bool_t {return false; });
MAKE_ALARM(almDefective_no_deact, "alarm_defective_no_deact", "Defective alarm !", Priority::None, 1, ACTIVE, []()->bool_t {return false; }, nullptr);

bool_t alarm_test_on = false;
bool_t alarm_test_off = false;
MAKE_ALARM(alm_test, "alarm_test", "Just for test", Priority::High, 0, INACTIVE, []()->bool_t {return alarm_test_on;}, []()->bool_t {return alarm_test_off; });

TEST(AlARM, creation)
{
    ASSERT_STREQ("alarm_1", alm1.alarmId.name.c_str());
    ASSERT_EQ(Priority::Low, alm1.alarmId.priority);
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

    // This is just to test singleton is working fine
    AlARM_Manager& alm_mgr_bis = AlARM_Manager::GetInstance();
    const Alarm alm = alm_mgr_bis.IsTriggered();

    ASSERT_EQ(Priority::Low, alm.alarmId.priority);
    ASSERT_STREQ("alarm_1", alm.alarmId.name.c_str());
    ASSERT_STREQ("Do nothing", alm.alarmId.description.c_str());

    alm_mgr_bis.print_active_alarms();

    alm_mgr_bis.reset();
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

    ASSERT_EQ(Priority::Medium, alm.alarmId.priority);
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

    ASSERT_EQ(Priority::High, alm.alarmId.priority);
    ASSERT_STREQ("alarm_3", alm.alarmId.name.c_str());
    ASSERT_STREQ("Run !", alm.alarmId.description.c_str());

    alm_mgr.print_all_alarms();
    alm_mgr.reset();
}

TEST(AlARM, no_alarm)
{
    AlARM_Manager& alm_mgr = AlARM_Manager::GetInstance();
    const Alarm alm = alm_mgr.IsTriggered();
    const Alarm NO_ALARM = {{"None", "No alarm", Priority::None, 0}, INACTIVE, NULL, NULL };
    ASSERT_EQ(Priority::None, alm.alarmId.priority);
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
    ASSERT_EQ(Priority::High, alarm1.alarmId.priority);
    ASSERT_STREQ("alarm_3", alarm1.alarmId.name.c_str());
    ASSERT_STREQ("Run !", alarm1.alarmId.description.c_str());

    alarm_test_on = true;
    alarm_test_off = false;
    const Alarm alarm2 = alm_mgr.IsTriggered();
    ASSERT_EQ(Priority::High, alarm2.alarmId.priority);
    ASSERT_STREQ("alarm_test", alarm2.alarmId.name.c_str());
    ASSERT_STREQ("Just for test", alarm2.alarmId.description.c_str());

    alarm_test_on = true;
    alarm_test_off = true;
    const Alarm alarm3 = alm_mgr.IsTriggered();
    ASSERT_EQ(Priority::High, alarm3.alarmId.priority);
    ASSERT_STREQ("alarm_test", alarm3.alarmId.name.c_str());
    ASSERT_STREQ("Just for test", alarm3.alarmId.description.c_str());

    alarm_test_on = false;
    alarm_test_off = false;
    const Alarm alarm4 = alm_mgr.IsTriggered();
    ASSERT_EQ(Priority::High, alarm4.alarmId.priority);
    ASSERT_STREQ("alarm_test", alarm4.alarmId.name.c_str());
    ASSERT_STREQ("Just for test", alarm4.alarmId.description.c_str());

    alarm_test_on = false;
    alarm_test_off = true;
    const Alarm alarm5 = alm_mgr.IsTriggered();
    ASSERT_EQ(Priority::High, alarm5.alarmId.priority);
    ASSERT_STREQ("alarm_3", alarm5.alarmId.name.c_str());
    ASSERT_STREQ("Run !", alarm5.alarmId.description.c_str());

    alm_mgr.reset();
}

TEST(AlARM, deactivation)
{
    AlARM_Manager& alm_mgr = AlARM_Manager::GetInstance();
    alm_mgr.add(alm7);

    ASSERT_EQ(1, alm_mgr.getLengthLows());
    ASSERT_EQ(0, alm_mgr.getLengthMeds());
    ASSERT_EQ(0, alm_mgr.getLengthHighs());    

    const Alarm alarm = alm_mgr.IsTriggered();
    ASSERT_EQ(Priority::None, alarm.alarmId.priority);
    ASSERT_STREQ("None", alarm.alarmId.name.c_str());
    ASSERT_STREQ("No alarm", alarm.alarmId.description.c_str());

    alm_mgr.reset();
}

TEST(AlARM, defective_alarm)
{
    AlARM_Manager& alm_mgr = AlARM_Manager::GetInstance();
    alm_mgr.add(almDefective);

    // A wrong alarm priority is considered High
    ASSERT_EQ(0, alm_mgr.getLengthLows());
    ASSERT_EQ(0, alm_mgr.getLengthMeds());
    ASSERT_EQ(1, alm_mgr.getLengthHighs());

    alm_mgr.print_active_alarms();

    const Alarm alarm = alm_mgr.IsTriggered();
    ASSERT_EQ(Priority::None, alarm.alarmId.priority);
    ASSERT_STREQ("None", alarm.alarmId.name.c_str());
    ASSERT_STREQ("No alarm", alarm.alarmId.description.c_str());

    alm_mgr.reset();
    alm_mgr.add(almDefective_no_act);
    const Alarm alarm2 = alm_mgr.IsTriggered();
    ASSERT_EQ(Priority::None, alarm2.alarmId.priority);
    ASSERT_STREQ("None", alarm2.alarmId.name.c_str());
    ASSERT_STREQ("No alarm", alarm2.alarmId.description.c_str());

    alm_mgr.reset();
    alm_mgr.add(almDefective_no_deact);
    const Alarm alarm3 = alm_mgr.IsTriggered();
    ASSERT_EQ(Priority::None, alarm3.alarmId.priority);
    ASSERT_STREQ("None", alarm3.alarmId.name.c_str());
    ASSERT_STREQ("No alarm", alarm3.alarmId.description.c_str());

    alm_mgr.reset();
}
