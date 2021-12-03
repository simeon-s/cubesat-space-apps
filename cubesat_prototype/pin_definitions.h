/**
 *  @author Simeon Baltadzhiev, Yordan Ganev
 *  @team Space Sense Team
 *  @comp NASA Space Apps 2021
 *  
 *  @about CubeSat GPS Esp32 + nRF24L01 + GPS + AccelGyro + Temp Sensor Pins
 *  
 *  @date 03.10.2021
 */

#ifndef __PIN_DEFINITIONS_H__
#define __PIN_DEFINITIONS_H__

#define DS18B20_PIN 15

#define NRF_CE_PIN 14
#define NRF_CSN_PIN 4

#define BATTERY_ADC_PIN 32
#define SOLAR_PANEL_ADC_PIN 35

#define GPS_TX_PIN 16
#define GPS_RX_PIN 17

#define MPU6050_SDA_PIN 22 // Check ESP pinout
#define MPU6050_SCL_PIN 21

#endif /* __PIN_DEFINITIONS_H__ */
