#ifndef AUDIOI_H_
#define AUDIOI_H_

#include "AlARMlib.h"

namespace Audio
{

class AudioI
{
public:
    AudioI() {};
    virtual ~AudioI() {};

    void play ( AlARM::Priority priority ) 
    {
        switch (priority)
        {
        case AlARM::Priority::None:
            stop();
            break;
        case AlARM::Priority::Low:
            playLow();
            break;
        case AlARM::Priority::Medium:
            playMed();
            break;
        case AlARM::Priority::High:
        default:
            playHigh();
            break;
        }
    }

    virtual void stop () = 0 ;

    AlARM::Priority getPrio() { return priotity_; };

protected:
    virtual void playHigh() = 0;
    virtual void playMed()  = 0;
    virtual void playLow()  = 0;

    AlARM::Priority priotity_ { AlARM::Priority::None } ;

};

}

#endif