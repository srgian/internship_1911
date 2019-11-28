#include "Security.h"
#include "Inputs.h"
#include "Outputs.h"
#include "Keypad.h"

#define ROWS 4
#define COLS 4
char keypressed[4];
char password[4] = {'1', '2', '3', '4'};
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
//Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);



void SecurityInit()
{ //citestefisierparole();// de facut cu cipri

//pwd=malloc(sizeof(char)*pwd_count*4);
}

void SecurityMainFunction()
{

}
