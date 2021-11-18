//
// Created by ncpd on 15-11-2021.
//


#ifndef SOUNDZONE_CLIENT_SYNC_HANDLER_H
#define SOUNDZONE_CLIENT_SYNC_HANDLER_H
#include "syncSlave.h"


class SYNC_handler{
public:
    SYNC_handler();
    int run();
    int pinTest();
    int bcmSetup();

private:
    Sync_Slave slaveSync;

};

#endif //SOUNDZONE_CLIENT_SYNC_HANDLER_H

