#include <gtest/gtest.h>

#include "AlARM.h"

#include <iostream>
#include <chrono>
#include <thread>

inline void portable_sleep(unsigned int seconds) 
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

extern "C" void start_thread();
extern "C" void stop_thread();
extern "C" int get_counter();

using namespace AlARM;

bool_t alarm_test_high = false;
MAKE_ALARM(alm_test, "alarm_test", "Just for test", Priority::High, 0, INACTIVE, []()->bool_t {return alarm_test_high;}, []()->bool_t {return !alarm_test_high; });
bool_t alarm_test_med = false;
MAKE_ALARM(alm_test_med, "alarm_test_med", "Just for test med", Priority::Medium, 0, INACTIVE, []()->bool_t {return alarm_test_med;}, []()->bool_t {return !alarm_test_med; });
bool_t alarm_test_low = false;
MAKE_ALARM(alm_test_low, "alarm_test_low", "Just for test low", Priority::Low, 0, INACTIVE, []()->bool_t {return alarm_test_low;}, []()->bool_t {return !alarm_test_low; });

TEST(AlARM, overall_low)
{
    const int TEST_TIME = 4; // duration per alarm priority
    start_thread();

    AlARM_Manager& alm_mgr = AlARM_Manager::GetInstance();
    alm_mgr.add(alm_test);
    alm_mgr.add(alm_test_low);
    alm_mgr.add(alm_test_med);
    ASSERT_EQ(1, alm_mgr.getLengthLows());
    ASSERT_EQ(1, alm_mgr.getLengthMeds());
    ASSERT_EQ(1, alm_mgr.getLengthHighs());

    {
        const Alarm alm = alm_mgr.IsTriggered();
        ASSERT_EQ(Priority::None, alm.alarmId.priority);
    }

    {
        std::cout << "\nLOW : " <<std::endl;
        alarm_test_low = true;
        int cnt = get_counter();
        portable_sleep(TEST_TIME);
        const Alarm alm = alm_mgr.IsTriggered();
        ASSERT_EQ(Priority::Low, alm.alarmId.priority);
    }

    {
        std::cout << "\nMED : " <<std::endl;
        alarm_test_med = true;
        int cnt = get_counter();
        portable_sleep(TEST_TIME);
        const Alarm alm = alm_mgr.IsTriggered();
        ASSERT_EQ(Priority::Medium, alm.alarmId.priority);
    }

    {
        std::cout << "\nHIGH : " <<std::endl; 
        alarm_test_high = true;
        int cnt = get_counter();
        portable_sleep(TEST_TIME);
        const Alarm alm = alm_mgr.IsTriggered();
        ASSERT_EQ(Priority::High, alm.alarmId.priority);
    }

    {
        std::cout << "\nNONE : " <<std::endl;
        alarm_test_low = false;
        alarm_test_med = false;
        alarm_test_high = false;
        int cnt = get_counter();
        portable_sleep(TEST_TIME);
        const Alarm alm = alm_mgr.IsTriggered();
        ASSERT_EQ(Priority::None, alm.alarmId.priority);
    }

    stop_thread();
    std::cout <<std::endl;

    alm_mgr.reset();
}

