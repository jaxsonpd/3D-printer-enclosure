/** 
 * @file fan_speed.c
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2025-01-05
 * @brief Implementation for the fan speed module which detects the speed
 * of the enclosure fan using timer 0
 * 
 * @note uses timer 0 and must use PD4 as this is T0 and requires uptime to function
 * 
 * @todo Add circular buffer for fan speed readings
 */


#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#include "avr_extends/uptime.h"

#include "circular_buffer.h"

#include "fan_speed.h"


#define PULSES_PER_INTERUPT (20) // How many pulses to count before interrupt <255
#define PULSES_PER_REV (2)
#define RPM_CONSTANT ((PULSES_PER_INTERUPT/PULSES_PER_REV)*1000LL*60LL)

#define SPEED_BUFFER_SIZE 10

#define MIN_RPM 200 // The minimum rpm that the fan can achieve

circBuf_t fanSpeedBuffer;

ISR(TIMER0_COMPA_vect) {
    static uint64_t lastIntTime = 0;

    uint64_t currentTime = uptime_ms();
    uint64_t delta = currentTime - lastIntTime;
    lastIntTime = currentTime;

    delta = delta == 0 ? 1 : delta; 

    if (delta < RPM_CONSTANT/MIN_RPM) {
        circ_buf_write(&fanSpeedBuffer,  (int32_t)(RPM_CONSTANT/(delta)));
    } else {
        circ_buf_write(&fanSpeedBuffer,  0);
    }
}

int fan_speed_init(void) {
    uptime_init();

    circ_buf_init(&fanSpeedBuffer, SPEED_BUFFER_SIZE);

    TCCR0A |= (1 << WGM01); // Count up to OCRA

    TCCR0B |= (1 << CS02) | (1 << CS01) | (1 << CS00); // Clock on PD4 rising edge Pin 4

    OCR0A = PULSES_PER_INTERUPT;

    TIMSK0 |= (1 << OCIE0A); // Enable interrupt on OCR0A achieve

    return 0;
}

int32_t fan_speed_get(void) {
    int32_t fanSpeedReturn = 0;

    int numSamples = 0;
    for (int i = 0; i < SPEED_BUFFER_SIZE; i++) {
        int32_t value;
        ATOMIC_BLOCK(ATOMIC_FORCEON) {
            value = circ_buf_read(&fanSpeedBuffer);
        }
        if (value != BUF_EMPTY_VAL) {
            fanSpeedReturn += value;
            numSamples ++;
        }
        
    }
    if (numSamples > 0) {
        fanSpeedReturn /= numSamples;
    }

    return fanSpeedReturn;
}