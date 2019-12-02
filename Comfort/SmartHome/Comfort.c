#include "Outputs.h"
#include "Inputs.h"

void ComfortInit()
{
    Print("DHT11 Humidity & temperature sensor:\n\n");
}

void ComfortMainFunction()
{
    Print("***loading***");
    //MQ4, MQ135
    uint8_t valueMQ135;
    uint8_t valueMQ4;
    ReadMQ4(&valueMQ4);
    ReadMQ135(&valueMQ135);

    //detect alcohol - MQ135
    Print("Alcohol level: ");
    DPrint(valueMQ135);
    Print("%  \n");
    if(valueMQ135 > 200){
        Print(" - Alert!\n");
    } else {
        Print(" - Normal\n");
    }

    //detect CO2 - MQ135
    Print("CO2: ");
    DPrint(valueMQ135);
    Print("ppm <parts-per-million>\n");

    //detect gas metane - MQ4
    Print("Gas methane: ");
    DPrint(valueMQ4);
    Print("ppm <parts-per-million>\n");



    //humidity & temperature
    double temp;
    double humid;
    ReadDHT(&temp, &humid);

    Print("Humidity: ");
    DPrint(humid);
    Print("%  \n");
    Print("Temperature: ");
    DPrint(temp);
    Print("C  \n");

    delay(3000);//Wait 3 seconds before accessing sensor again

}
