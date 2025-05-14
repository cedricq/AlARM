#ifndef AUDIOTEST_H_
#define AUDIOTEST_H_

#include "AudioI.h"

namespace Audio
{

class AudioTest : public AudioI
{
public:
    AudioTest() {};
    virtual ~AudioTest() {};

    void stop() override;

private:
    void playHigh() override;
    void playMed()  override;
    void playLow()  override;
};

}

#endif