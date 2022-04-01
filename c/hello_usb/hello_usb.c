#include <stdio.h>
#include "pico/stdlib.h"

// reference: https://github.com/raspberrypi/pico-sdk (how to build and make pico project)
// reference: https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf (3.2.2 indicating how to run code via ssh)
int main() {
    setup_default_uart();
    printf("Hellp, world!");
    return 0;
}