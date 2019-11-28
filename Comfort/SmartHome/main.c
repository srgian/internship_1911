#include <time.h>
#include "Logic.h"
#include "Lights.h"

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

int main()
{
    LightsInit();

    for(;;)
    {
        MainFunction();
        delay(1000);
    }
    return 0;
}
