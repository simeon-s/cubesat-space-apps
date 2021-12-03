/**
 *  @author Simeon Baltadzhiev, Yordan Ganev
 *  @team Space Sense Team
 *  @comp NASA Space Apps 2021
 *  
 *  @about Ground Station nrf functions
 *  
 *  @date 03.10.2021
 */

const byte slaveAddress[5] = {'S','A','T','0','1'};
const byte thisSlaveAddress[5] = {'S','T','A','0','1'};

void nrf_init() {
    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.setRetries(3, 5); // delay, count
    radio.openWritingPipe(slaveAddress);
    radio.openReadingPipe(1, thisSlaveAddress);
}

//================ Station ================
void nrf_send( uint8_t size ) {

    bool rslt;
    rslt = radio.write(&nrf_tx_buff, size);

    Println("Data Sent");
    if (rslt) {
        Println("Acknowledge received");
    }
    else {
        Println("Tx failed");
    }
}

//================ Station ================
void nrf_getData() {
    if ( radio.available() ) {
        radio.read( &nrf_rx_buff, sizeof(nrf_rx_buff) );
        if (nrf_rx_buff[0] == 1) {
            memcpy(&sys_data, &nrf_rx_buff, sizeof(sys_data));
            nrf_status |= NRF_RCV_SYS;
        }
        if (nrf_rx_buff[0] == 2) {
            newData = true;
            memcpy(&gps_data, &nrf_rx_buff, sizeof(gps_data));
            nrf_status |= NRF_RCV_GPS;
        }
    }
}

//================ Station ================
void nrf_showData() {
      Println("Data received: ");
      
      Print("MSG_ID: "); Println(sys_data.msg_id);
      Print("Temp: "); Println(sys_data.temperature,2);
      Print("GX: "); Println(sys_data.gx);
      Print("GY: "); Println(sys_data.gy);
      Print("GZ: "); Println(sys_data.gz);
      Print("BAT V: "); Println(sys_data.battery);
      Print("SP V: "); Println(sys_data.solar_panel);
      Print("Longitude: "); Println(gps_data.longitude, 5);
      Print("Latitude: "); Println(gps_data.latitude, 5);
      Print("Altitude: "); Println(gps_data.altitude, 5);
      Print("Speed: "); Println(gps_data.speed, 2);
      Print("Angle: "); Println(gps_data.angle, 2);
      Print("Satellites: "); Println(gps_data.satellites);
      Print("Quality: "); Println(gps_data.quality);
      
      char tmp_str[65];
      sprintf(tmp_str, "%02d:%02d:%02d", sys_data.hour, sys_data.min, sys_data.sec);
      Println(tmp_str);
      
      sprintf(tmp_str, "%02d:%02d:%02d", sys_data.month, sys_data.day, sys_data.year);
      Println(tmp_str);

      Print("Checksum: "); Println(sys_data.chk_sum);
}
