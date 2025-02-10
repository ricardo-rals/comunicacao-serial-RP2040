#include <stdio.h>
#include <math.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "../includes/ssd1306.h"
#include "../includes/font.h"
#include "../includes/matrix_led.h"
#include "../includes/animations.h"
#include "../includes/led_rgb.h"
#include "../includes/button_control.h"
#include "pio_matrix.pio.h"

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define OLED_ADDRESS 0x3C
#define BUFFER_SIZE 20  // Maximum sentence length for the display

// Define the display as global to be accessed by buttons
ssd1306_t ssd;

int main() {
    stdio_init_all();

    // Initialize I2C
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Initialize the SSD1306 display
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, OLED_ADDRESS, I2C_PORT);
    ssd1306_config(&ssd);
    ssd1306_fill(&ssd, false);
    ssd1306_rect(&ssd, 3, 3, 122, 58, true, false);
    ssd1306_send_data(&ssd);

    // Initialize the WS2812 LED Matrix
    PIO pio = pio0;
    set_sys_clock_khz(128000, false);
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, LED_PIN);
    sleep_ms(100);

    // Configure buttons and LEDs
    configure_buttons();
    configure_led_rgb();

    // Animation function array
    void (*animation[]) (PIO, uint) = {
        animation_number_zero,
        animation_number_one,
        animation_number_two,
        animation_number_three,
        animation_number_four,
        animation_number_five,
        animation_number_six,
        animation_number_seven,
        animation_number_eight,
        animation_number_nine
    };

    printf("System ready. Type characters in the Serial Monitor.\n");

    char sentence[BUFFER_SIZE + 1] = "";
    int position = 0;

    while (true) {
        int c = getchar_timeout_us(100000);
        if (c == PICO_ERROR_TIMEOUT) continue; 

        if (c >= '0' && c <= '9') {  
            int num = c - '0';
            printf("Displaying number %d on the LED Matrix\n", num);

            ssd1306_fill(&ssd, false);
            ssd1306_rect(&ssd, 3, 3, 122, 58, true, false);
            ssd1306_draw_string(&ssd, "Number ", 10, 10);
            char num_str[2] = {c, '\0'};
            ssd1306_draw_string(&ssd, num_str, 60, 10);
            ssd1306_send_data(&ssd);

            animation[num](pio, sm);
            position = 0;
            sentence[0] = '\0';
        } else if (c == '\b' || c == 127) {  
            if (position > 0) {
                position--;
                sentence[position] = '\0';
                printf("\rCurrent sentence: %s   ", sentence); // Update the sentence in the Serial Monitor
                fflush(stdout); // Force update in terminal

                ssd1306_fill(&ssd, false);
                ssd1306_rect(&ssd, 3, 3, 122, 58, true, false);
                ssd1306_draw_string(&ssd, sentence, 8, 10);
                ssd1306_send_data(&ssd);
            }
        } else if (c >= 32 && c <= 126 && position < BUFFER_SIZE) {
            sentence[position++] = c;
            sentence[position] = '\0';
            
            // Display the typed sentence in the Serial Monitor
            printf("\rCurrent sentence: %s ", sentence);
            fflush(stdout); // Force terminal update

            // Update the OLED display
            ssd1306_fill(&ssd, false);
            ssd1306_rect(&ssd, 3, 3, 122, 58, true, false);
            ssd1306_draw_string(&ssd, sentence, 8, 10);
            ssd1306_send_data(&ssd);
        }
    }
}
