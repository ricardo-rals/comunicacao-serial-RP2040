#ifndef BUTTON_CONTROL_H
#define BUTTON_CONTROL_H

#include "pico/stdlib.h"

// Definition of button pins
#define BUTTON_A 5
#define BUTTON_B 6

// Declaration of functions
void configure_buttons(void);
void handle_button_interrupt(uint gpio, uint32_t events);

#endif
