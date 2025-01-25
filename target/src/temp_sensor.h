/** 
 * @file temp_sensor.h
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2025-01-23
 * @brief Interface to the temperature sensor
 */


#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H


#include <stdint.h>
#include <stdbool.h>

/** 
 * @brief Initialise the temperature sensor
 * 
 * @return 0 if succesful
 */
int temp_sensor_init(void);

/** 
 * @brief Get the current temperature
 * 
 * @return the temperature in celsius * 1000
 */
int16_t temp_sensor_get_temp(void);

/** 
 * @brief Get the whole number part of the temperature
 * @param temp the temperature to extract from
 * 
 * @return the whole number portion of the temperature
 */
int16_t temp_sensor_get_whole_num(int16_t temp);

/** 
 * @brief Get the fractional part of the temperature
 * @param temp the temperature to extract from
 * 
 * @return the fractional portion of the temperature
 */
uint16_t temp_sensor_get_fractional(int16_t temp);





/** 
 * @brief Print temp to stdout also gets the temperature
 * 
 */
void temp_sensor_print_temp(void);

#endif // TEMP_SENSOR_H