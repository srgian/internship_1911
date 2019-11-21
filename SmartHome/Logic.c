#include <inttypes.h>
#include "Inputs.h"
#include "Outputs.h"

uint8_t input=0xaa;

void MainFunction()
{
    ReadInputs(&input);
    WriteOutputs(&input);
}
