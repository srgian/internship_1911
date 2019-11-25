#ifndef LIGHTS_H
#define LIGHTS_H

#include <inttypes.h>
#define NR_BECURI 1U
#define NR_BUTOANE 15U
#define TIMER_BECURI 100

#define NORMAL 1U
#define TEMP 2U
#define INTENSITATE 3U
#define OFF 0U
#define ON 255U


void LightsInit();
void LightsMainFunction();

typedef struct st_buton    /// Definire structura buton
{
    uint8_t pin;    /// Nr pin buton
    uint8_t stare;  /// Stare Buton
    uint8_t pvs_stare;  /// Stare precedenta buton

} buton_t; /// Numele structurii buton

typedef struct st_bec{     /// Definire structura bec
    uint8_t tip;    /// Tip normal/timer/50% intensitate
    uint8_t pin; /// Nr pin bec
    uint8_t stare;  /// 0-255; 0=off; 255=full
    uint8_t timer; /// 0-100 secunde
    uint8_t nrButoane; ///
    buton_t *butoane;   /// Pointer catre buton
    uint8_t timerX_val;     /// Valoare timer.
} bec_t;



extern bec_t becuri[NR_BECURI];


#endif // LIGHTS_H
