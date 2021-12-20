//
// Created by ncpd on 11-11-2021.
//

#include "szs_client.h"
#include "sync_handler.h"
#include <bcm2835.h>
#define PIN1  RPI_V2_GPIO_P1_40 // Define output pin

int test_recv_packet(){
    SZS_client client;




    return 0;
}


int main(){
    long long int adjtime;
    long long int savetime = 0;
    long long int delay = 1000000; // 5sec
    if(!bcm2835_init())return 1;
    bcm2835_gpio_fsel(PIN1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(PIN1, LOW);
    SYNC_handler s;
    for(int i=0; i < 10;i++){
    s.run();
        adjtime = s.slaveSync.clockOffset();
        while (s.slaveSync.adjustClock(adjtime)<delay+savetime){}
        bcm2835_gpio_write(PIN1, HIGH);
        delayMicroseconds(500);
        bcm2835_gpio_write(PIN1, LOW);
        savetime=s.slaveSync.adjustClock(adjtime);
    }
    std::cout<<" \033[1;32mThe synchronization was successful\033[0m\n "<<std::endl;
    return 0;
}