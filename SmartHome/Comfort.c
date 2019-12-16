#include "Outputs.h"
#include "Inputs.h"

void ComfortInit()
{
    Print("DHT11 Humidity & temperature sensor:\n\n");
}

void ComfortMainFunction()
{
    double temp;
    double humid;
    ReadDHT(&temp, &humid);

    Print("***Current data***");
    Print("Humidity: ");
    DPrint(humid);
    Print("%  \n");
    Print("Temperature: ");
    DPrint(temp);
    Print("C  \n");

    delay(3000);//Wait 3 seconds before accessing sensor again

}
