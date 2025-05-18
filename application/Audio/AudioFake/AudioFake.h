#ifndef AUDIOFAKE_H_
#define AUDIOFAKE_H_

#include "AudioI.h"

namespace Audio
{

class AudioFake : public AudioI
{
public:
    AudioFake() {};
    virtual ~AudioFake() {};

    void stop() override;

private:
    void playHigh() override;
    void playMed()  override;
    void playLow()  override;
};

}

#endif