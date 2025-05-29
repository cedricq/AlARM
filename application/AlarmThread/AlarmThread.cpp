
#include "AlARM.h"
#include "AudioI.h"

#include <iostream>
#include <pthread.h>
#include <atomic>
#include <chrono>
#include <thread>

static std::atomic<int> counter(0);
static pthread_t thread_id;
static std::atomic<bool> in_progress(false);

static const int PERIOD_MS = 100;

void* boucle_thread(void*) {
    static AlARM::AlARM_Manager& alm_mgr = AlARM::AlARM_Manager::GetInstance(); // GCOVR_EXCL_LINE
    while (in_progress.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(PERIOD_MS));      // GCOVR_EXCL_LINE
        counter++;
        
        const AlARM::Alarm alm = alm_mgr.IsTriggered();                         // GCOVR_EXCL_LINE
        Audio::AudioI& audio = Audio::AudioI::GetInstance();                    // GCOVR_EXCL_LINE

        if(alm.alarmId.priority == AlARM::Priority::None)
        {
            audio.stop();                                                       // GCOVR_EXCL_LINE
        }
        else
        {
            audio.play(alm.alarmId.priority);                                   // GCOVR_EXCL_LINE     
        }
    }
    return nullptr;
}

extern "C" void start_thread() {
    if (!in_progress.load())    // GCOVR_EXCL_LINE
    {
        in_progress = true;
        pthread_create(&thread_id, nullptr, boucle_thread, nullptr);
    }
}

extern "C" void stop_thread() { // GCOVR_EXCL_LINE
    if (in_progress.load())     // GCOVR_EXCL_LINE
    {
        in_progress = false;
        pthread_join(thread_id, nullptr);
    }
}

extern "C" int get_counter() {
    return counter.load();
}