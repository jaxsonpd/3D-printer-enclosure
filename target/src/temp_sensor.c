/**
 * @file temp_sensor.c
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2025-01-23
 * @brief Interface to the temperature sensor
 */


#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "avr_extends/GPIO.h"
#include "avr_extends/wire.h"
#include "avr_extends/delay.h"
#include "avr_extends/UART.h"

#define TCN75A_ADDR (uint8_t)0b1001111
#define TCN75A_CONIFG_REG (uint8_t)0b00000001
#define TCN75A_AMBIENT_TEMP_REG (uint8_t)0b00000000
#define TCN75A_HYSTERESIS_REG (uint8_t)0b00000010
#define TCN75A_TEMP_LIMIT_REG (uint8_t)0b00000011


int temp_sensor_init(void) {
    wire_write_reg(TCN75A_ADDR, TCN75A_CONIFG_REG, 0b00000000);
    uint8_t config[1] = { 0 };
    wire_read_reg(TCN75A_ADDR, TCN75A_CONIFG_REG, config, 1);

    return 0;
}


int16_t temp_sensor_get_temp(void) {
    uint8_t tempRaw[2] = { 0 };
    // wire_write(TCN75A_ADDR, TCN75A_TEMP_LIMIT_REF);

    wire_read_reg(TCN75A_ADDR, TCN75A_AMBIENT_TEMP_REG, tempRaw, 2);

    int16_t temperature = 10;
    temperature = ((int16_t)tempRaw[0] << 4) | ((tempRaw[1] >> 4) & 0x0F);

    return temperature;
}

uint16_t convertFractionalTempToInt(uint8_t hexValue, uint8_t precision) {
    uint16_t result = 0;
    uint16_t factor = 5*1000;
    for (int i = 0; i < precision; i++) {
        uint8_t checkValue = (1 << (4-1-i));
        uint8_t digitSet = hexValue & checkValue;
        if (digitSet) {
            result += factor;
        }
        factor /= 2; 
    }

    return result;
}

void temp_sensor_print_temp(void) {
    int16_t temp = temp_sensor_get_temp();

    int16_t highTemp = temp >> 4 & 125;
    uint16_t lowTemp = convertFractionalTempToInt((temp & 0x0F), 1);

    printf("Temperature: %d.%d\n", highTemp, lowTemp);
}


int16_t temp_sensor_get_whole_num(int16_t temp) {
    return temp >> 4;
}

uint16_t temp_sensor_get_fractional(int16_t temp) {
    return convertFractionalTempToInt(temp & 0x0F, 4);
}