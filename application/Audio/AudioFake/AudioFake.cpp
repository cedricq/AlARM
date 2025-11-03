#include "AudioFake.h"
#include <iostream>
#include <sstream>
#include <iomanip>

#ifdef _WIN32
  #include <windows.h>  // declares Beep
#endif

using namespace Audio;

static int time_low = 0;
static int time_med = 0;
static int time_high = 0; 

void beep(unsigned int time_ms) 
{
    // Frequency: 1000 Hz, Duration: time_ms
#ifdef _WIN32
    Beep(1000, time_ms);
#else
    double seconds = time_ms / 1000.0;
    std::ostringstream out;
    out << std::fixed << std::setprecision(1) << seconds;

    std::string cmd  = "play -nq -t alsa synth " + out.str() + " sine 1000 >/dev/null 2>&1";
    system(cmd.c_str());
#endif
}

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
    if (   ( time_high == 0  and time_high < 2 ) 
        or ( time_high == 4  and time_high < 6 ) 
        or ( time_high == 8  and time_high < 10 )
        or ( time_high == 16 and time_high < 18 ) 
        or ( time_high == 20 and time_high < 22 )
    )
    {
        if (time_high%2 == 0)
        {
            std::cout<<"XX";   
            beep(200); 
        }
    }
    else 
    {
        std::cout<<".";
    }
    if (time_high >= 30) time_high = 0;
    else time_high++;
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
        if (time_med == 0 or time_med == 10)
        {
            std::cout<<"XXXXX";   
            beep(500); 
        }
    }
    else 
    {
        std::cout<<".";
    }

    if (time_med >= 50) time_med = 0;
    else time_med++;
}

void AudioFake::playLow() 
{
    priotity_ = AlARM::Priority::Low;
    time_high = 0;
    time_med = 0;

    if (time_low < 10 )
    {
        if (time_low == 0)
        {
            std::cout<<"XXXXXXXXXX";   
            beep(1000); 
        }
    }
    else 
    {
        std::cout<<".";
    }

    if (time_low >= 100) time_low = 0;
    else time_low++;
}

void AudioFake::stop()
{
    priotity_ = AlARM::Priority::None;
    std::cout<<".";
}

