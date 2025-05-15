#include "AudioFake.h"
#include <iostream>

using namespace Audio;

void AudioFake::playHigh() 
{
    std::cout<<"AUDIO HIGH" <<std::endl;
    priotity_ = AlARM::Priority::High;
}

void AudioFake::playMed() 
{
    std::cout<<"AUDIO MED" <<std::endl;
    priotity_ = AlARM::Priority::Medium;
}

void AudioFake::playLow() 
{
    std::cout<<"AUDIO LOW" <<std::endl;
    priotity_ = AlARM::Priority::Low;
}

void AudioFake::stop()
{
    std::cout<<"AUDIO STOP" <<std::endl;
    priotity_ = AlARM::Priority::None;
}

