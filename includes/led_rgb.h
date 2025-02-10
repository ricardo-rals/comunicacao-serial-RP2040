#ifndef LED_RGB_H
#define LED_RGB_H

#include "pico/stdlib.h"

// Definition of RGB LED pins
#define LED_G 11  // Green
#define LED_B 12  // Blue
#define LED_R 13  // Red

// Declaration of functions
void configure_led_rgb(void);
void set_led_rgb(bool red, bool green, bool blue);
bool blink_red_rgb_led(struct repeating_timer *t);

#endif // LED_RGB_H
