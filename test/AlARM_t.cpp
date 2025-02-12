#include <gtest/gtest.h>

#include "AlARM.h"

#include <iostream>

using namespace AlARM;


void tick()
{

}

MAKE_ALARM(alm1, "alarm_1", Low, 1, []()->bool_t {std::cout <<"ON" <<std::endl; return true;}, []()->bool_t {std::cout <<"OFF" <<std::endl; return false; });

TEST(AlARM, creation)
{
	ASSERT_EQ("alarm_1", alm1.alarmId.name.c_str());
	ASSERT_EQ(Low, alm1.priority);
	ASSERT_EQ(1, alm1.subPriority);
	ASSERT_TRUE(alm1.triggerON());
	ASSERT_FALSE(alm1.triggerOFF());
}


TEST(AlARM, overall)
{
	tick();
}
