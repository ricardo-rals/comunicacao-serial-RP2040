#include "../includes/button_control.h"
#include "../includes/led_rgb.h"
#include "../includes/ssd1306.h"
#include <stdio.h>

// States of the LEDs
static bool green_led_state = false;
static bool blue_led_state = false;
static volatile uint32_t last_press_time = 0; // For debounce

// Configures the buttons and enables interrupt
void configure_buttons(void) {
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &handle_button_interrupt);

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &handle_button_interrupt);
}

// Button interrupt handler
void handle_button_interrupt(uint gpio, uint32_t events) {
    extern ssd1306_t ssd; // Allows access to the global display

    uint32_t now = time_us_32();
    if (now - last_press_time < 200000) return; // Debounce (200ms)
    last_press_time = now;

    if (gpio == BUTTON_A) { // If button A was pressed
        if (green_led_state) { 
            green_led_state = false; // Turn off Green
        } else { 
            green_led_state = true;  // Turn on Green
            blue_led_state = false;  // Turn off Blue
        }
    } 
    else if (gpio == BUTTON_B) { // If button B was pressed
        if (blue_led_state) {
            blue_led_state = false; // Turn off Blue
        } else {
            blue_led_state = true;  // Turn on Blue
            green_led_state = false; // Turn off Green
        }
    }

    // Updates the RGB LED with the new states
    set_led_rgb(false, green_led_state, blue_led_state);

    // Displays a message in the Serial Monitor
    printf("Button %c pressed -> Green LED: %s | Blue LED: %s\n",
        (gpio == BUTTON_A) ? 'A' : 'B',
        green_led_state ? "ON" : "OFF",
        blue_led_state ? "ON" : "OFF"
    );

    // Updates the OLED display
    ssd1306_fill(&ssd, false);
    ssd1306_rect(&ssd, 3, 3, 122, 58, true, false);
    if (green_led_state) {
        ssd1306_draw_string(&ssd, "Green LED", 15, 10);
        ssd1306_draw_string(&ssd, "ON", 30, 30);
    } else if (blue_led_state) {
        ssd1306_draw_string(&ssd, "Blue LED", 15, 10);
        ssd1306_draw_string(&ssd, "ON", 30, 30);
    } else {
        ssd1306_draw_string(&ssd, "All LEDs", 15, 10);
        ssd1306_draw_string(&ssd, "OFF", 30, 30);
    }
    ssd1306_send_data(&ssd);
} 
