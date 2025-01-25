/** 
 * @file fan_speed.h
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2025-01-05
 * @brief Module to monitor the speed of the enclosure fan
 */


#ifndef FAN_SPEED_H
#define FAN_SPEED_H


#include <stdint.h>
#include <stdbool.h>

/** 
 * @brief Initialise the fan speed module
 * 
 * @return 0 if successful
 */
int fan_speed_init(void);

/** 
 * @brief Get the current fan speed
 * 
 * @return the fan speed in rpm
 */
int32_t fan_speed_get(void);


#endif // FAN_SPEED_H