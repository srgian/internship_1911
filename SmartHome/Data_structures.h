typedef struct bec
{
    uint8_t tip;
    uint8_t pin;
    uint8_t stare;
    uint8_t timer;
    uint8_t timerX_val;
    uint8_t nrButoane;
    buton_t *butoane;

} bec_t;

typedef struct buton
{
    uint8_t pin;
    uint8_t stare;
    uint8_t pvs_stare;
} buton_t;

