#include "AlARM.h"

#include <iostream>
#include <chrono>
#include <string>

extern "C" void start_thread();
extern "C" void stop_thread();
extern "C" int get_counter();

using namespace AlARM;

bool_t alarm_test_high = false;
MAKE_ALARM(alm_test, "alarm_test", "Just for test", Priority::High, 0, INACTIVE, []()->bool_t {return alarm_test_high;}, []()->bool_t {return !alarm_test_high; });
bool_t alarm_test_med = false;
MAKE_ALARM(alm_test_med, "alarm_test_med", "Just for test med", Priority::Medium, 0, INACTIVE, []()->bool_t {return alarm_test_med;}, []()->bool_t {return !alarm_test_med; });
bool_t alarm_test_low = false;
MAKE_ALARM(alm_test_low, "alarm_test_low", "Just for test low", Priority::Low, 0, INACTIVE, []()->bool_t {return alarm_test_low;}, []()->bool_t {return !alarm_test_low; });

#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
    char getch() {
        struct termios oldt, newt;
        char c;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        read(STDIN_FILENO, &c, 1);
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return c;
    }
#endif

int main() 
{
    std::cout.setf(std::ios::unitbuf);
    std::cout << "Press following keys :\n";
    std::cout << "  - \'h\' for activating/deactivating high prio alarm \n";
    std::cout << "  - \'m\' for activating/deactivating medium prio alarm \n";
    std::cout << "  - \'l\' for activating/deactivating low prio alarm \n";
    std::cout << "  - \'q\' for quitting \n";
    std::cout << "Output :\n";
    std::cout << "  - \'X\' is equivalent to a 100ms beep window\n";
    std::cout << "  - \'.\' is equivalent to a 100ms no-beep window\n";


    start_thread();

    AlARM_Manager& alm_mgr = AlARM_Manager::GetInstance();
    alm_mgr.add(alm_test);
    alm_mgr.add(alm_test_low);
    alm_mgr.add(alm_test_med);


    while (true) 
    {
        char c;
        #ifdef _WIN32
            c = _getch();
        #else
            c = getch();
        #endif

        if (c == 'q') break;

        switch (c)
        {
        case 'h':
            alarm_test_high = !alarm_test_high;
            break;
        case 'm':
            alarm_test_med = !alarm_test_med;
            break;
        case 'l':
            alarm_test_low = !alarm_test_low;
            break;
        default:
            alarm_test_low = false;
            alarm_test_med = false;
            alarm_test_high = false;
            break;
        }
    }

    stop_thread();
    std::cout <<std::endl;

    alm_mgr.reset();

    return 0;
}