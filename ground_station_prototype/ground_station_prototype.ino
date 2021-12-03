/**
 *  @author Simeon Baltadzhiev, Yordan Ganev
 *  @team Space Sense Team
 *  
 *  @about Ground Station Esp32 + nRF24L01
 *  
 *  @date 03.10.2021
 */

// ----- Included libraries -----
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <HTTPClient.h>

// ----- Local libraries -----
#include "data_structures.h"
#include "secrets.h"

// ----- Definitions & Macros -----
#define Println Serial.println // Comment these to turn off serial debugging
#define Print Serial.print
#define LED_BUILTIN 2

#define CE_PIN 22
#define CSN_PIN 21

#define NRF_TX_BUFF_SIZE 32
#define NRF_RX_BUFF_SIZE 96

#define NRF_RCV_SYS 0x01
#define NRF_RCV_GPS 0x02

#define HOST "cube-sat.000webhostapp.com"

// Declare global variables which will be uploaded to server

// ----- Global Variables ------
char nrf_rx_buff[NRF_RX_BUFF_SIZE];
char nrf_tx_buff[NRF_TX_BUFF_SIZE];

char dataReceived[10]; // this must match dataToSend in the TX
bool newData = false;


char dataToSend[10] = "Message 0" ;
char txNum = '0';

ST_SYS_PAYLOAD_T sys_data;
ST_GPS_PAYLOAD_T gps_data;

uint8_t nrf_status = 0;

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

WebServer server(80);

const int led = 13;

unsigned long txIntervalMillis = 2000; // send once per second

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Print('.');
    delay(1000);
  }
  Println(WiFi.localIP());
}


void setup() {

    Serial.begin(115200);
    delay(5000);
    Println("SimpleTx Starting");

    nrf_init();

    initWiFi();
    Print("RRSI: ");
    Println(WiFi.RSSI());
}

uint8_t station_state = 0;

#define ST_IDLE    0
#define ST_UPLOAD  1

//====================

void loop() {
  
    nrf_getData();
    switch (station_state) {
      case ST_IDLE:
        if (millis() >= txIntervalMillis) {
            txIntervalMillis = millis() + 20000;
            radio.stopListening();
            send();
            radio.startListening();
        }
        
        if ( newData ) {
          station_state = ST_UPLOAD;
          nrf_showData();
          newData = 0;
        }
        
        break;
        
      case ST_UPLOAD:
        Println(nrf_status);
        upload_data();
        station_state = ST_IDLE;
        nrf_status = 0;
        break;
    }
    
}

//====================

void send() {

    bool rslt;
    rslt = radio.write( &dataToSend, strlen(dataToSend) );
        // Always use sizeof() as it gives the size as the number of bytes.
        // For example if dataToSend was an int sizeof() would correctly return 2
        
    Print("Data Sent ");
    Print(dataToSend);
    if (rslt) {
        Println("  Acknowledge received");
        updateMessage();
    }
    else {
        Println("  Tx failed");
    }
    
}

//================

void updateMessage() {
        // so you can see that new data is being sent
    txNum += 1;
    if (txNum > '9') {
        txNum = '0';
    }
    dataToSend[11] = txNum;
}
