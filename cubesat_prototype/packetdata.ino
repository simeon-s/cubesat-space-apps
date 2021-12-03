/**
 *  @author Simeon Baltadzhiev, Yordan Ganev
 *  @team Space Sense Team
 *  @comp NASA Space Apps 2021
 *  
 *  @about CubeSat Data packets and measure
 *  
 *  @date 03.10.2021
 */

#define ADC_MAX_VOLTAGE   3.9 // 3.3 
#define ADC_MAX_VALUE     0x0fff

/**
 * @brief packet_data Measure data and prepare it for sending
 */
void packet_data()
{
  sys_data.msg_id++;
  gps_data.msg_id = sys_data.msg_id;

  ds18b20.requestTemperatures(); 
  
  if ( ds18b20.getTempCByIndex(0) != DEVICE_DISCONNECTED_C )
  {
    sys_data.temperature = ds18b20.getTempCByIndex(0);
  }
  
  sys_data.gx = mpu.getAngleX();
  sys_data.gy = mpu.getAngleY();
  sys_data.gz = mpu.getAngleZ();

  float adc_measure = analogRead(BATTERY_ADC_PIN);
  sys_data.battery = (ADC_MAX_VOLTAGE * adc_measure) / ADC_MAX_VALUE;
  sys_data.battery *= 5;
  
  Print( "BAT ADC: ");
  Print(adc_measure);
  Print( " : ");
  Println(sys_data.battery);
  
  adc_measure = analogRead(SOLAR_PANEL_ADC_PIN);
  sys_data.solar_panel = (ADC_MAX_VOLTAGE * adc_measure) / ADC_MAX_VALUE;
  sys_data.solar_panel *= 5;
  
  Print("SP ADC: ");
  Print(adc_measure);
  Print(" : ");
  Println(sys_data.solar_panel);
  
  sys_data.hour = GPS.hour;
  sys_data.min = GPS.minute;
  sys_data.sec = GPS.seconds;
  
  sys_data.year =  GPS.year;
  sys_data.month =  GPS.month;
  sys_data.day = GPS.day;
  
  if ( GPS.fix ) {
    gps_data.quality = GPS.fixquality;

    //N and E are positive, S and W are negative.
    gps_data.latitude = GPS.latitude;
    if ( GPS.lat == 'S' ) 
    {
      gps_data.latitude *= -1; 
    }
    
    gps_data.longitude = GPS.longitude;
    if ( GPS.lon == 'W' ) 
    {
      gps_data.longitude *= -1; 
    }
  
    gps_data.altitude = GPS.altitude;
    gps_data.speed = GPS.speed;
    gps_data.angle = GPS.angle;

    gps_data.satellites = GPS.satellites;
  }

  sys_data.chk_sum = getCheckSum( (uint8_t*)&sys_data, sizeof(sys_data) - 1);
  gps_data.chk_sum = getCheckSum( (uint8_t*)&gps_data, sizeof(gps_data) - 1);
}

/**
 * @brief getCheckSum Calc checksum of packet
 * @param tmp_pckt packet
 * @param size packet length
 * @return check sum
 */
uint8_t getCheckSum(uint8_t* tmp_pckt, uint8_t size) {
  
  uint8_t tmp_sum = 0;
  while (size--) {
    tmp_sum += *tmp_pckt;
    tmp_pckt++;
  }
  return tmp_sum;
}
