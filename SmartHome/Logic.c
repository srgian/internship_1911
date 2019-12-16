#include "WifiConn.h"
#include "Logic.h"
#include "Lights.h"
#include "Comfort.h"
#include  "Security.h"
#include "Doorlock.h"

void MainFunction()
{
    //LightsMainFunction();
<<<<<<< HEAD
    //ComfortMainFunction();
    connToWifi();
=======
   // ComfortMainFunction();
>>>>>>> ce269943966fffe52251b89da76bbbfca6a5a46e
    SecurityMainFunction();
    DoorlockMainFunction();
}
