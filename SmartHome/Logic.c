#include "Logic.h"
#include "Lights.h"
#include "Comfort.h"
#include  "Security.h"
#include "DoorLock.h"

void MainFunction()
{
    DoorLockMainFunction();
    LightsMainFunction();
    ComfortMainFunction();
    SecurityMainFunction();
}
