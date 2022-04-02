#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

#define N_SAMPLES 1000
uint16_t sample_buf[N_SAMPLES];

void printhelp() {
    puts("\nCommands:");
    puts("c0, ...\t: Select ADC channel n");
    puts("s\t: Sample once");
    puts("S\t: Sample many");
    puts("w\t: Wiggle pins");
}

void __not_in_flash_func(adc_capture)(uint16_t *buf, size_t count) {
    adc_fifo_setup(true, false, 0, false, false);
    adc_run(true);
    for (int i = 0; i < count; i = i + 1)
        buf[i] = adc_fifo_get_blocking();
    adc_run(false);
    adc_fifo_drain();
}

int main() {

    // reference: https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__gpio.html#ga2af81373f9f5764ac1a5bd6097477530
    // Initialization
    stdio_init_all();
    adc_init();
    adc_set_temp_sensor_enabled(true);

    // Set all pins to input (as far as SIO is concerned)
    gpio_set_dir_all_bits(0); // Set direction of all pins simultaneously, which set input value for each gpio, where for GPIO N, N is 1 for out while 0 for in;
    for (int i = 2; i < 30; i++) {
        gpio_set_function(i, GPIO_FUNC_SIO); // Select GPIO function
        /*  General Purpose Input/Output (GPIO) API.
            RP2040 has 36 multi-functional General Purpose Input / Output (GPIO) pins, divided into two banks. 
            In a typical use case, the pins in the QSPI bank (QSPI_SS, QSPI_SCLK and QSPI_SD0 to QSPI_SD3) are used to execute code from an external flash device, leaving the User bank (GPIO0 to GPIO29) for the programmer to use. 
            All GPIOs support digital input and output, but GPIO26 to GPIO29 can also be used as inputs to the chip’s Analogue to Digital Converter (ADC). 
            Each GPIO can be controlled directly by software running on the processors, or by a number of other functional blocks.
            The function allocated to each GPIO is selected by calling the gpio_set_function function.
        */
       if (i == PICO_DEFAULT_LED_PIN) { // 25
            gpio_init(PICO_DEFAULT_LED_PIN);
            gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
       }
        if (i >= 26) {
            gpio_disable_pulls(i);
            gpio_set_input_enabled(i, false);
        }
    }

    printf("\n===========================\n");
    printf("RP2040 ADC and Test Console\n");
    printf("===========================\n");
    printhelp();

    while(true) {

        // blink
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        sleep_ms(250);
        gpio_put(PICO_DEFAULT_LED_PIN, 0);

        // get input
        char c = getchar();
        printf("%c", c);
        switch(c) {
            case 'c':
                c = getchar();
                printf("%c\n", c);
                if (c < '0' || c > '7') {
                    printf("Unknown input channel\n");
                    printhelp();
                } else {
                    adc_select_input(c - '0');
                    printf("Switched to channel %c\n", c);
                }
                break;
            case 'b':;
                uint32_t result = adc_read();
                const float conversion_factor = 3.3f / (1 << 12);
                printf("\n0x%03x -> %f V\n", result, result * conversion_factor);
                break;
            case 'S':
                printf("\nStarting capture\n");
                adc_capture(sample_buf, N_SAMPLES);
                printf("Done\n");
                for (int i = 0; i < N_SAMPLES; i = i + 1)
                    printf("%03x\n", sample_buf[i]);
                break;
            case 'w':
                printf("\nPress any key to stop wiggling\n");
                int i = 1;
                gpio_set_dir_all_bits(-1);
                while (getchar_timeout_us(0) == PICO_ERROR_TIMEOUT) {
                    // Pattern: Flash all pins for a cycle,
                    // Then scan along pins for one cycle each
                    i = i ? i << 1 : 1;
                    gpio_put_all(i ? i : ~0);
                }
                gpio_set_dir_all_bits(0);
                printf("Wiggling halted.\n");
                break;
            case '\n':
            case '\r':
                break;
            case 'h':
                printhelp();
                break;
            default:
                printf("\nUnrecognised command: %c\n", c);
                printhelp();
                break;
        }
    }
}