#include "../includes/led_rgb.h"

// Red LED state variables
static bool red_led_state = false;

// Configures the RGB LED pins as output
void configure_led_rgb(void) {
    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);

    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_OUT);

    gpio_init(LED_B);
    gpio_set_dir(LED_B, GPIO_OUT);
}

// Sets the RGB LED color (without interfering with the red blinking)
void set_led_rgb(bool red, bool green, bool blue) {
    gpio_put(LED_G, green);
    gpio_put(LED_B, blue);
}

// Function that blinks **only** the red LED
bool blink_red_rgb_led(struct repeating_timer *t) {
    red_led_state = !red_led_state;
    gpio_put(LED_R, red_led_state);
    return true;
}
