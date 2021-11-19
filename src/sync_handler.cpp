//
// Created by mc on 19-11-2021.
//


#include "sync_handler.h"
#define RTT_FILTER_ON 2400 // Optimal RTT på 2400µs
#define RTT_FILTER_OFF 30000 // RTT på 30ms for bare at lukke synk igennem uden filter.


SYNC_handler::SYNC_handler()=default;

int SYNC_handler::run(){

    bool checkPrint = true;
    slaveSync.Set_RTT_Filter(RTT_FILTER_OFF);
    slaveSync.Reset_Time();
    jump :
    if (checkPrint){
        std::cout<<" \033[1;34mAwaiting synchronization request from master\033[0m\n "<<std::endl;
    }
    slaveSync.Sync_Check_And_Accept();
    slaveSync.Recive_TS23();
    if (!slaveSync.Check_Sync_OK()){
        if (checkPrint){
            std::cout<<" \033[1;34mRetransmitting due to poor round trip time.. please wait\033[0m\n "<<std::endl;
            checkPrint = false;}
        goto jump;

    }else{
        std::cout<<" \033[1;32mThe synchronization was successful\033[0m\n "<<std::endl;
       // slaveSync.print(); //--> printer TS1234 samt offset og RTT tider. Bruges til debug.
    }
    return 0;
}







