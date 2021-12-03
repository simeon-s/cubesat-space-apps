/**
 *  @author Simeon Baltadzhiev, Yordan Ganev
 *  @team Space Sense Team
 *  
 *  @about Map and upload data to database
 *  
 *  @date 03.10.2021
 */

void upload_data()
{
  HTTPClient http;    // http object of clas HTTPClient
  
  String postData = F("status=1");
  if ( nrf_status & NRF_RCV_SYS)  {
    postData += F("&sendvalX=");
    postData += String(sys_data.gx);
    postData += F("&sendvalY=");
    postData += String(sys_data.gy);
    postData += F("&sendvalZ=");
    postData += String(sys_data.gz);
    postData += F("&sendvalTemp=");
    postData += String(sys_data.temperature);
    postData += F("&sendvalBV=");
    postData += String(sys_data.battery);
    postData += F("&sendvalPV=");
    postData += String(sys_data.solar_panel);
  }

  if( nrf_status & NRF_RCV_GPS ) {
    postData += F("&quality=");
    postData += String(gps_data.quality);
    postData += F("&speed=");
    postData += String(gps_data.speed);
    postData += F("&altitude=");
    postData += String(gps_data.altitude);
    postData += F("&satellites=");
    postData += String(gps_data.satellites);
    postData += F("&longitude=");
    postData += String(gps_data.longitude, 8);
    postData += F("&latitude=");
    postData += String(gps_data.latitude, 8);
  }

  http.begin((String(HOST) + "/dbwrite.php").c_str());              // Connect to host where MySQL databse is hosted
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");            //Specify content-type header
  
  int httpCode = http.POST(postData);   // Send POST request to php file and store server response code in variable named httpCode
  
  // if connection eatablished then do this
  if (httpCode == 200) { 
    Println("Values uploaded successfully."); 
    Println(httpCode); 
    String webpage = http.getString();    // Get html webpage output and store it in a string
    Println(webpage + "\n"); 
  } else {   // if failed to connect then return and restart
    Println(httpCode); 
    Println("Failed to upload values. \n"); 
    http.end(); 
  }
}


void get_command()
{
  //TODO
}
