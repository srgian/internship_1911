#include "Lights.h"
#include "Inputs.h"
#include "Outputs.h"
#include <stdio.h>
#include <inttypes.h>

#define NULL_PTR 0U

bec_t becuri[NR_BECURI];
buton_t butoane[NR_BUTOANE];

void LightsInit()
{
    bec_t *b;

    b=&becuri[0];
    b->tip = NORMAL;
    b->pin = 22;
    b->stare = OFF;
    b->timer = 0;
    b->nrButoane = 2;
    b->butoane = &(butoane[0])+0;
    b->timerX_val = 100;

    (b->butoane + 0)->pin=8;
    (b->butoane + 1)->pin=9;

    b=&becuri[1];
    b-> tip = 1;
    b-> pin = 14;
    b-> stare = 0;
    b-> timer = 0;
    b-> nrButoane = 3;
    b-> butoane = &(butoane[0])+2;
    b-> timerX_val = 100;

    (b->butoane + 0)->pin=10;
    (b->butoane + 1)->pin=11;

    for(int i=0; i<NR_BECURI; i++)
    {
        bec_t *b=&becuri[i];
        digitalPinMode(b->pin, OUTPUT);
    }
}

void LightsMainFunction()
{
    for(int i=0; i<NR_BECURI; i++)
    {
        bec_t *b=&becuri[i];
        for(int j=0; j<(b->nrButoane); j++)
        {
            buton_t *t=&(b->butoane[j]);
            b-> stare=digitalPinRead(t->pin);
        }

        digitalPinWrite(b->pin, b->stare);
    }
}


