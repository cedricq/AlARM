#include "AudioFake.h"
#include <iostream>

using namespace Audio;

void AudioFake::playHigh() 
{
    std::cout<<"AUDIO HIGH" <<std::endl;
}

void AudioFake::playMed() 
{
    std::cout<<"AUDIO MED" <<std::endl;
}

void AudioFake::playLow() 
{
    std::cout<<"AUDIO LOW" <<std::endl;
}

void AudioFake::stop()
{
    std::cout<<"AUDIO STOP" <<std::endl;
}

