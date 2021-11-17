//
// Created by ncpd on 11-11-2021.
//

#ifndef SOUNDZONE_CLIENT_SZS_CLIENT_H
#define SOUNDZONE_CLIENT_SZS_CLIENT_H

#include "szp_slave.h"
#include "alsadriver.h"
#include "sync_handler.h"

class SZS_client{
private:
    SZP_slave* szp;
    alsadriver* alsa;
    SYNC_handler* sync;

    static void szp_receive(SZP_slave* szp);
    static void run_sync_handler(SYNC_handler* sync_handler);
protected:

public:
    SZS_client();
    int run();
};

#endif //SOUNDZONE_CLIENT_SZS_CLIENT_H
