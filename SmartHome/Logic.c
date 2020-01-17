#include "Logic.h"
#include "Lights.h"
#include "Comfort.h"
#include  "Security.h"
#include "Doorlock.h"
#include "WifiConn.h"

void MainFunction()
{

    // LightsMainFunction();


    DoorlockMainFunction();
    SecurityMainFunction();
      ComfortMainFunction();

}
