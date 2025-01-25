/**
 * @file main.c
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-03-30
 * @brief The main file for the enclosure monitor project
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <avr/interrupt.h>
#include <avr/io.h>

#include "avr_extends/GPIO.h"
#include "avr_extends/UART.h"
#include "avr_extends/delay.h"
#include "avr_extends/uptime.h"

#include "custom_can_protocol/packet.h"
#include "custom_can_protocol/packet_handler.h"
#include "custom_can_protocol/packet_processing.h"

#include "custom_packet.h"
#include "fan_speed.h"
#include "temp_sensor.h"

#define BAUD_RATE 115200

pin_t ledPin;

int setup(void) {
    UART_init_stdio(BAUD_RATE);

    uptime_init();
    fan_speed_init();

    delay_ms(1000);

    temp_sensor_init();

    ledPin = PIN(PORTD, 2); // Pin 2
    GPIO_set_output(ledPin, true);
    GPIO_pin_init(ledPin, OUTPUT);

    sei();

    return 0;
}

int main(void) {
    setup();
    uint64_t last_send = uptime_ms();
    uint64_t last_toggle = uptime_ms();


    while (true) {
        if ((uptime_ms() - last_send) > 1000) {
            int32_t fanSpeed = fan_speed_get();
            printf("Fan Speed = 0x%lx\n", fanSpeed);
            uint8_t fanSpeedData[4] = {fanSpeed>>24 & 0xFF, fanSpeed>>16 & 0xFF, fanSpeed>>8 & 0xFF, fanSpeed & 0xFF};
            packet_send(putchar, fanSpeedData, 4, GET_FAN_SPEED_IDENT);
            last_send = uptime_ms();
        }

        if (uptime_ms() - last_toggle > 1000) {
            // GPIO_toggle_output(ledPin);
            temp_sensor_print_temp();
            int16_t temp = temp_sensor_get_temp();
            uint8_t tempData[4] = {(temp_sensor_get_whole_num(temp)>>8)&0xFF, 
                                    temp_sensor_get_whole_num(temp)&0xFF,
                                    (temp_sensor_get_fractional(temp)>>8)&0xFF,
                                    temp_sensor_get_fractional(temp)&0xFF};
            packet_send(putchar, tempData, 4, GET_TEMP_IDENT);
            last_toggle = uptime_ms();
        }
    }


    return 0;
}
