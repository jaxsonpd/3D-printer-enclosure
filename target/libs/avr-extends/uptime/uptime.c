/** 
 * @file uptime.c
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2025-01-05
 * @brief Implementation for the uptime module to store the time since initialisation
 * 
 * @cite https://github.com/monoclecat/avr-millis-function/
 */


#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#include "avr_extends/GPIO.h"

volatile uint64_t timerCount = 0; // The uptime count

// ISR(TIMER1_COMPA_vect) {
//     timerCount++;
// }

// void uptime_init(void) {
//     uint16_t msCount = ((F_CPU / 1000) / 8); // When count is this 1ms passed

//     TCCR1B |= (1 << WGM12) | (1 << CS11); // Count Up, clk/8 prescaler 

//     OCR1A = msCount;
    
//     TIMSK1 |= (1 << OCIE1A);
// }

ISR(TIMER2_COMPA_vect) {
    timerCount++;
}

void uptime_init(void) {
    uint8_t msCount = ((F_CPU / 1000) / 64); // When count is this 1ms passed

    TCCR2A |= (1 << WGM21);
    TCCR2B |= (1 << CS22); // Count Up, clk/8 prescaler 

    OCR2A = msCount;
    
    TIMSK2 |= (1 << OCIE2A);
}

 uint64_t uptime_ms(void) {
    uint64_t timerCountReturn = 0;

    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        timerCountReturn = timerCount;
    }

    return timerCountReturn;
 }