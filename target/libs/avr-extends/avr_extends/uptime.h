/** 
 * @file uptime.h
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2025-01-05
 * @brief Allows checking of the up time of the processor
 * 
 * @note uses TIMER2
 */


#ifndef UPTIME_H
#define UPTIME_H


#include <stdint.h>
#include <stdbool.h>

ISR(TIMER1_COMPA_vect);

/** 
 * @brief Initialise the uptime module setting up the required timer 2
 * 
 */
void uptime_init(void);

/** 
 * @brief Get the current elapsed time since start
 * 
 * @return the elapsed time in ms
 */
uint64_t uptime_ms(void);


#endif // UPTIME_H