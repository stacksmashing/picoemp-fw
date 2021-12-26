#include <stdio.h>
#include <string.h>

#include "pico/stdlib.h"
#include "picoemp.h"

int main() {
    // Initialize USB-UART as STDIO
    stdio_init_all();

    picoemp_init();

    bool armed = false;
    while(1) {
        gpio_put(PIN_LED_HV, gpio_get(PIN_IN_CHARGED));

        // Pulse
        if(gpio_get(PIN_BTN_PULSE)) {
            picoemp_pulse();
        }

        if(gpio_get(PIN_BTN_ARM)) {
            if(!armed) {
                gpio_put(PIN_LED_CHARGE_ON, true);
                armed = true;
            } else {
                gpio_put(PIN_LED_CHARGE_ON, false);
                armed = false;
                picoemp_disable_pwm();
            }
            // YOLO debouncing
            while(gpio_get(PIN_BTN_ARM));
            sleep_ms(100);
        }

        if(!gpio_get(PIN_IN_CHARGED) && armed) {
            picoemp_enable_pwm();
        }
    }
    
    return 0;
}
