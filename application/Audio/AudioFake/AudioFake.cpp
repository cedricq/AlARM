#include "AudioFake.h"
#include <iostream>

using namespace Audio;

static int time_low = 0;
static int time_med = 0;
static int time_high = 0; 

AudioI& AudioI::GetInstance()
{
    static AudioFake audio;
    return audio; 
}

void AudioFake::playHigh() 
{
    priotity_ = AlARM::Priority::High;
    time_med = 0;
    time_low = 0;
    if (   ( time_high >= 0  and time_high < 2 ) 
        or ( time_high >= 4  and time_high < 6 ) 
        or ( time_high >= 8  and time_high < 10 )
        or ( time_high >= 16 and time_high < 18 ) 
        or ( time_high >= 20 and time_high < 22 )
    )
    {
        std::cout<<"X";    
    }
    else 
    {
        std::cout<<".";
        if (time_high >= 30) time_high = 0;

    }
    time_high++;
}

void AudioFake::playMed() 
{
    priotity_ = AlARM::Priority::Medium;
    time_high = 0;
    time_low = 0;

    if (time_med < 5 
        or ( time_med >=10 and time_med < 15 ) 
    )
    {
        std::cout<<"X";    
    }
    else 
    {
        std::cout<<".";
        if (time_med >= 50) time_med = 0;

    }

    time_med++;
}

void AudioFake::playLow() 
{
    priotity_ = AlARM::Priority::Low;
    time_high = 0;
    time_med = 0;

    if (time_low < 10 )
    {
        std::cout<<"X";    
    }
    else 
    {
        std::cout<<".";
        if (time_low >= 100) time_low = 0;

    }

    time_low++;
}

void AudioFake::stop()
{
    priotity_ = AlARM::Priority::None;
    std::cout<<".";
}

