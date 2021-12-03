/**
 *  @author Simeon Baltadzhiev, Yordan Ganev
 *  @team Space Sense Team
 *  @comp NASA Space Apps 2021
 *  
 *  @about CubeSat nrf functions
 *  
 *  @date 03.10.2021
 */

const byte slaveAddress[5] = {'S','T','A','0','1'} ;
const byte thisSlaveAddress[5] = {'S','A','T','0','1'};

/**
 * @brief nrf_send 
 * @param tx_buff data to be send
 * @param size size of data to be send
 * 
 * Note: Size must be between 1 - 32
 */
void nrf_init() {
    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.setRetries(5, 3); // delay, count
    radio.openWritingPipe(slaveAddress);
    radio.openReadingPipe(1, thisSlaveAddress);
}

/**
 * @brief nrf_send 
 * @param tx_buff data to be send
 * @param size size of data to be send
 * 
 * Note: Size must be between 1 - 32
 */
void nrf_send(uint8_t *tx_buff, uint8_t size ) {

    bool rslt;
    rslt = radio.write(tx_buff, size);

    Print("Data Sent: ");
    if (rslt) {
        Println("ACK received");
    }
    else {
        Println("NAC");
    }
}

/** 
 *  @brief nrf_getData Get incomming data
 *  TODO Commands packet translate
 */
void nrf_getData() {
    if ( radio.available() ) {
        radio.read( &nrf_rx_buff, sizeof(nrf_rx_buff) );
        nrf_rcv_flag = true;
    }
}
