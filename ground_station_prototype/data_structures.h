/**
 *  @author Simeon Baltadzhiev, Yordan Ganev
 *  @team Space Sense Team
 *  
 *  @about CubeSat Data structure types (32 byte compatible)
 *  
 *  @date 03.10.2021
 */

#ifndef __DATA_STRUCTURES_H__
#define __DATA_STRUCTURES_H__

//#include "stdint.h"

typedef struct  __attribute__((packed)) {
//  uint16_t Status; // TODO
  uint8_t type;      // 1 
  uint8_t msg_id;    // 2
  
  float temperature; // 6
  
  int16_t gx;        // 8
  int16_t gy;        // 10
  int16_t gz;        // 12
  
  float battery;      // 16
  float solar_panel; // 20
  
  uint8_t hour;      // 21
  uint8_t min;       // 22
  uint8_t sec;       // 23
  
  uint8_t year;      // 24
  uint8_t month;     // 25
  uint8_t day;       // 26

  uint8_t chk_sum;   // 27 bytes
} ST_SYS_PAYLOAD_T;

typedef struct  __attribute__((packed)) {
  
  uint8_t type;      // 1 
  uint8_t msg_id;    // 2
  
  float longitude;   // 6
  float latitude;    // 10
  
  float altitude;    // 14
  float speed;       // 18
  float angle;       // 22
  
  uint8_t satellites;// 23
  uint8_t quality;   // 24
  
  uint8_t chk_sum;   // 25 bytes
} ST_GPS_PAYLOAD_T;

#endif /*__DATA_STRUCTURES_H__*/
