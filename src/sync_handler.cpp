//
// Created by ncpd on 15-11-2021.
//


#include "sync_handler.h"

SYNC_handler::SYNC_handler() {

};

int SYNC_handler::run(){

    slaveSync.Reset_Time();
    jump :
    std::cout<<" :) "<<std::endl;
    slaveSync.Sync_Check_And_Accept();
    std::cout<<" :))) "<<std::endl;

    slaveSync.Recive_TS23();
    std::cout<<" ts2ts3 "<<std::endl;
    if (!slaveSync.Check_Sync_OK()){
        std::cout<<" BAD RTT "<<std::endl;
        goto jump;

    }else{
        std::cout<<" sync OK "<<std::endl;
    }

    return 0;
}
