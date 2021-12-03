/**
 *  @author Simeon Baltadzhiev, Yordan Ganev
 *  @team Space Sense Team
 *  @comp NASA Space Apps 2021
 *  
 *  @about CubeSat Esp32 + nRF24L01 + GPS + AccelGyro + Temp Sensor
 *  
 *  @date 03.10.2021
 */

// ----- Included libraries -----
#include <nRF24L01.h> 
#include <RF24.h>               // v1.4.1
#include <Adafruit_GPS.h>       // v1.5.4
#include <Wire.h>  
#include <MPU6050_light.h>      // 1.2.1
#include <OneWire.h>            //2.3.5
#include <DallasTemperature.h>  //3.9.1

// ----- Local libraries -----
#include "data_structures.h"
#include "pin_definitions.h"

// ----- Definitions & Macros -----
#define Println Serial.println // Comment these to turn off serial debugging
#define Print Serial.print

#define DUTY_CYCLE       30000

#define NRF_TX_BUFF_SIZE 32
#define NRF_RX_BUFF_SIZE 96

#define NRF_RCV_SYS 0x01
#define NRF_RCV_GPS 0x02

// ----- Global Variables ------
uint8_t nrf_rx_buff[NRF_RX_BUFF_SIZE];
uint8_t nrf_tx_buff[NRF_TX_BUFF_SIZE];

uint32_t duty_cycle;
bool nrf_rcv_flag = false;

unsigned long timer_mpu = 0;

ST_SYS_PAYLOAD_T sys_data;
ST_GPS_PAYLOAD_T gps_data;

// ----- Object declarations -----
Adafruit_GPS GPS(&Serial2);
RF24 radio(NRF_CE_PIN, NRF_CSN_PIN); // Create a Radio

OneWire oneWire(DS18B20_PIN);
DallasTemperature ds18b20(&oneWire);

MPU6050 mpu(Wire);


void setup()
{
  Serial.begin(115200);
  delay(500); // Give time to the hardware to bootup

  // Init NRF
  nrf_init();
  // Init GPS
  gps_init();
  // Start the DS18B20 sensor
  ds18b20.begin();
  
  // mpu.upsideDownMounting = true; // cubesat accgyro orientation
  // Init Accelerometer Gyroscope
  Wire.begin();
  
  mpu.begin();
  mpu.calcOffsets(); // gyro and accelero

  // Init Values
  sys_data.type = NRF_RCV_SYS;
  gps_data.type = NRF_RCV_GPS;
  
  duty_cycle = millis() + 1000; // 1 sec before sending first packet

}

void loop()                     // run over and over again
{
  background_tasks();
  
  if (millis() > duty_cycle)
  {
    duty_cycle = millis() + DUTY_CYCLE;
    
    packet_data();
    
    radio.stopListening();
    
    // Send data threw transmit buffer 
    memcpy(&nrf_tx_buff, &sys_data, sizeof(sys_data));
    nrf_send( (uint8_t*) &nrf_tx_buff, sizeof(sys_data));
    
    if ( GPS.fix ) {
      memcpy(&nrf_tx_buff, &gps_data, sizeof(gps_data));
      nrf_send( (uint8_t*) &nrf_tx_buff, sizeof(gps_data));
    }
    radio.startListening(); 
  }

  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {

    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return;  // we can fail to parse a sentence in which case we should just wait for another
  }
}

/**
 * @brief background_tasks Continuous measurements and reading tasks
 */
void background_tasks() {
  GPS.read();
  nrf_getData();
  mpu.update();
}
