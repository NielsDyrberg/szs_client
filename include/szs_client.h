//
// Created by ncpd on 11-11-2021.
//

#ifndef SOUNDZONE_CLIENT_SZS_CLIENT_H
#define SOUNDZONE_CLIENT_SZS_CLIENT_H

#include "szp_slave.h"
#include "dummy_alsa_driver.h"
#include "sync_handler.h"

class SZS_client{
private:
    SZP_slave* szp;
    dummy_alsa_driver* alsa;
    SYNC_handler* sync;

    static void szp_receive(SZP_slave* szp);
    static void alsa_play(dummy_alsa_driver* alsa);
    static void run_sync_handler(SYNC_handler* sync_handler);
protected:

public:
    SZS_client();
    int run();
};

#endif //SOUNDZONE_CLIENT_SZS_CLIENT_H
