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

/**
 * @brief Hangs until current time i larger than #time_to_play
 * @param time_to_return The time when the function should return.
 */
void SYNC_handler::return_when(long long time_to_return) {
    std::cout << "Current time: " << slaveSync.adjustClock(slaveSync.clockOffset())<< std::endl;
    while (slaveSync.adjustClock(slaveSync.clockOffset()) < time_to_return);

}
