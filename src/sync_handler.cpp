//
// Created by ncpd on 15-11-2021.
//


#include "sync_handler.h"
#include <bcm2835.h>
#define PIN1 RPI_V2_GPIO_P1_40 // Define output pin

SYNC_handler::SYNC_handler() {

};

int SYNC_handler::run(){
    bool checkPrint = true;
    bcmSetup();
    slaveSync.Reset_Time();
    jump :
    if (checkPrint){
    std::cout<<" Ready and waiting for sync from master! "<<std::endl;}
    slaveSync.Sync_Check_And_Accept();
    slaveSync.Recive_TS23();
    if (!slaveSync.Check_Sync_OK()){
        if (checkPrint){
        std::cout<<" sync retransmit due to poor round trip time.. wait "<<std::endl;
        checkPrint = false;}
        goto jump;

    }else{
        std::cout<<" Synchronization successful "<<std::endl;
    }
    pinTest(); //Denne er for pinout test! skal slettes igen!

    return 0;
}
int SYNC_handler::bcmSetup(){
    if(!bcm2835_init())return 1;
    bcm2835_gpio_fsel(PIN1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(PIN1, LOW);}

int SYNC_handler::pinTest() {
    long long int adjtime;
    long long int delay = 5000000;
    adjtime = slaveSync.clockOffset();
    while (slaveSync.adjustClock(adjtime) < delay) {}
     bcm2835_gpio_write(PIN1, HIGH);
     delayMicroseconds(500000);
     bcm2835_gpio_write(PIN1, LOW);
}