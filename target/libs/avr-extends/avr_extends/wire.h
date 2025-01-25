/** 
 * @file wire.h
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-10-20
 * @brief Declarations for the I2C 2 wire driver
 */


#ifndef WIRE_H
#define WIRE_H


#include <stdint.h>
#include <stdbool.h>

/** 
 * @brief Initialise the wire driver
 * @param scl_freq the frequency for the serial clock
 * @param enPullups enable the 5V pullups on the serial interface
 * 
 * @return 0 on success
 */
int wire_init(uint32_t scl_freq, bool enPullups);

/** 
 * @brief Send a write message with data to the slave
 * @param addr the address to write to 7-bit
 * @param data the data to send
 * 
 * @return 0 if successful, 1 if internal error, 2 if no ack
 */
int wire_write(uint8_t addr, uint8_t data);

/** 
 * @brief Read a number of words from the slave
 * @param addr the address to read (7-bit)
 * @param buf the buffer to read into 
 * @param len the number of words to read
 * 
 * @return 0 if successful
 */
int wire_read(uint8_t addr, uint8_t buf[], uint8_t len);


/** 
 * @brief Write to a register with a data value
 * @param addr the device address to write 7-bit
 * @param reg the register to write too
 * @param data the data to write
 * 
 * @return 0 if successful, 1 if internal error, 2 if no ack
 */

int wire_write_reg(uint8_t addr, uint8_t reg, uint8_t data);
// void wire_read(void);

/** 
 * @brief Read a register from the device
 * @param addr the device address (7-bit)
 * @param reg the register to read
 * @param buf the buffer to load into
 * @param len the number of bytes to read
 * 
 * @return 0 if successful, 1 if internal error, 2 if no ack
 */
int wire_read_reg(uint8_t addr, uint8_t reg, uint8_t buf[], uint8_t len);


#endif // WIRE_H