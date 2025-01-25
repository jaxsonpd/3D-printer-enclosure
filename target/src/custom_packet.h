/** 
 * @file custom_packet.h
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2025-01-25
 * @brief Custom parts to supplement the custom can protocol
 */


#ifndef CUSTOM_PACKET_H
#define CUSTOM_PACKET_H


#include <stdint.h>
#include <stdbool.h>

#define GET_FAN_SPEED_IDENT 0x00
#define SET_FAN_SPEED_IDENT 0x01
#define GET_TEMP_IDENT 0x02


#endif // CUSTOM_PACKET_H