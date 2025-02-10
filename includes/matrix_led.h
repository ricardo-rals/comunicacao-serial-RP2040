#ifndef MATRIX_LED_H
#define MATRIX_LED_H

#include "pico/stdlib.h"
#include "hardware/pio.h"

// Constants
#define NUM_PIXELS 25
#define LED_PIN 7
#define FPS 10

// General functions for LEDs
uint32_t rgb_return(double b, double r, double g);

#endif
