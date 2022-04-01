#include "pico/stdlib.h"

int main() {
    
#ifndef PICO_DEFAULT_LED_PIN
#warning blink example requires a board with a regular LED
#else

    const uint led_pin = PICO_DEFAULT_LED_PIN;
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);
    while(true) {
        gpio_put(led_pin, 1);
        sleep_ms(250);
        gpio_put(led_pin, 0);
        sleep_ms(250);
    }
#endif

}