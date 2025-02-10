#include "../includes/animations.h"
#include "../includes/matrix_led.h"

// Definition of numbers in the 5x5 matrix
const int MATRIX_NUMBERS[10][25] = {
    {1, 1, 1, 1, 1,
     1, 0, 0, 0, 1,
     1, 0, 0, 0, 1,
     1, 0, 0, 0, 1,
     1, 1, 1, 1, 1},  // Number 0

    {0, 0, 1, 0, 0,
     0, 1, 1, 0, 0,
     0, 0, 1, 0, 0,
     0, 0, 1, 0, 0,
     1, 1, 1, 1, 1},  // Number 1

    {1, 1, 1, 1, 1,
     0, 0, 0, 0, 1,
     1, 1, 1, 1, 1,
     1, 0, 0, 0, 0,
     1, 1, 1, 1, 1},  // Number 2

    {1, 1, 1, 1, 1,
     0, 0, 0, 0, 1,
     1, 1, 1, 1, 1,
     0, 0, 0, 0, 1,
     1, 1, 1, 1, 1},  // Number 3

    {1, 0, 0, 0, 1,
     1, 0, 0, 0, 1,
     1, 1, 1, 1, 1,
     0, 0, 0, 0, 1,
     1, 0, 0, 0, 0},  // Number 4

    {1, 1, 1, 1, 1,
     1, 0, 0, 0, 0,
     1, 1, 1, 1, 1,
     0, 0, 0, 0, 1,
     1, 1, 1, 1, 1},  // Number 5

    {1, 1, 1, 1, 1,
     1, 0, 0, 0, 0,
     1, 1, 1, 1, 1,
     1, 0, 0, 0, 1,
     1, 1, 1, 1, 1},  // Number 6

    {1, 1, 1, 1, 1,
     0, 0, 0, 0, 1,
     0, 1, 0, 0, 0,
     0, 0, 1, 0, 0,
     0, 0, 0, 1, 0},  // Number 7

    {1, 1, 1, 1, 1,
     1, 0, 0, 0, 1,
     1, 1, 1, 1, 1,
     1, 0, 0, 0, 1,
     1, 1, 1, 1, 1},  // Number 8

    {1, 1, 1, 1, 1,
     1, 0, 0, 0, 1,
     1, 1, 1, 1, 1,
     0, 0, 0, 0, 1,
     1, 1, 1, 1, 1}   // Number 9
};



// Generic function to display a number on the LED matrix
void display_number_on_matrix(PIO pio, uint sm, int number) {
    if (number < 0 || number > 9) return;  // Ensures that the number is between 0 and 9

    uint32_t buffer[NUM_PIXELS];

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int index = (4 - i) * 5 + j;  // Maintains row inversion for correct alignment
            buffer[i * 5 + j] = MATRIX_NUMBERS[number][index]
                ? rgb_return(0.0, 0.2, 0.0)  // Green LED 20%
                : rgb_return(0.0, 0.0, 0.0); // LED off
        }
    }

    // Sends the frame to the LEDs
    for (int i = 0; i < NUM_PIXELS; i++) {
        pio_sm_put_blocking(pio, sm, buffer[i]);
    }
}


// Animation functions for each number, calling the generic function
void animation_number_zero(PIO pio, uint sm) { display_number_on_matrix(pio, sm, 0); }
void animation_number_one(PIO pio, uint sm) { display_number_on_matrix(pio, sm, 1); }
void animation_number_two(PIO pio, uint sm) { display_number_on_matrix(pio, sm, 2); }
void animation_number_three(PIO pio, uint sm) { display_number_on_matrix(pio, sm, 3); }
void animation_number_four(PIO pio, uint sm) { display_number_on_matrix(pio, sm, 4); }
void animation_number_five(PIO pio, uint sm) { display_number_on_matrix(pio, sm, 5); }
void animation_number_six(PIO pio, uint sm) { display_number_on_matrix(pio, sm, 6); }
void animation_number_seven(PIO pio, uint sm) { display_number_on_matrix(pio, sm, 7); }
void animation_number_eight(PIO pio, uint sm) { display_number_on_matrix(pio, sm, 8); }
void animation_number_nine(PIO pio, uint sm) { display_number_on_matrix(pio, sm, 9); }
