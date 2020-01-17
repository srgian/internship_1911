#ifndef MENU_H
#define MENU_H

typedef struct MENU MENU;

struct MENU {
  MENU *prevMenu;
  MENU *nextMenu;
  MENU *subMenu;
  MENU *parent;
  int sensorValue;
  char *title;
  char *prefix;
  char *suffix;
  bool writable;
};

  #endif
