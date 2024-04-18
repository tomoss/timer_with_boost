#include "TimerTrigger.h"
#include <iostream>

int main()
{
    try
    {
        TimerTrigger timerTrigger;

        timerTrigger.addTimer(0, []
        {
            std::cout << "Timer 0 timeout" << std::endl;
        });
        timerTrigger.startTimer(0, 3);

        timerTrigger.addTimer(1, []
        {
            std::cout << "Timer 1 timeout" << std::endl;
        });
        timerTrigger.startTimer(1,3);
        timerTrigger.cancelTimer(1);

        timerTrigger.addTimer(2, []
        {
            std::cout << "Timer 2 timeout" << std::endl;
        });
        timerTrigger.deleteTimer(2);

        sleep(5); 
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}