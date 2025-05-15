#include <gtest/gtest.h>

#include "AudioFake.h"

#include <iostream>

using namespace Audio;

TEST(AUDIO, test_prios)
{
    AudioI* audio = new AudioFake();

    audio->play(AlARM::Priority::High);
    ASSERT_EQ(AlARM::Priority::High, audio->getPrio());

    audio->play(AlARM::Priority::Medium);
    ASSERT_EQ(AlARM::Priority::Medium, audio->getPrio());

    audio->play(AlARM::Priority::None);
    ASSERT_EQ(AlARM::Priority::None, audio->getPrio());

    audio->play(AlARM::Priority::Low);
    ASSERT_EQ(AlARM::Priority::Low, audio->getPrio());

    audio->stop();
    ASSERT_EQ(AlARM::Priority::None, audio->getPrio());

    delete audio;
    //ASSERT_EQ(nullptr, audio);
}