#include "TimerTrigger.h"
#include <iostream>

int main()
{
    try
    {
        TimerTrigger timerTrigger;
        timerTrigger.addTimer(0x0, []
        {
            std::cout << "Timer 0 timeout" << std::endl;
        });
        timerTrigger.startTimer(0x0, 3);

        timerTrigger.addTimer(0x1, []
        {
            std::cout << "Timer 1 timeout" << std::endl;
        });
        timerTrigger.startTimer(0x1, 3);
        timerTrigger.cancelTimer(0x1);

        timerTrigger.addTimer(0x2, []
        {
            std::cout << "Timer 2 timeout" << std::endl;
        });
        timerTrigger.deleteTimer(0x2);

        sleep(5);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}