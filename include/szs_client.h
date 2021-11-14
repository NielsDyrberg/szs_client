//
// Created by ncpd on 11-11-2021.
//

#ifndef SOUNDZONE_CLIENT_SZS_CLIENT_H
#define SOUNDZONE_CLIENT_SZS_CLIENT_H

#include "szp_slave.h"
#include "dummy_alsa_driver.h"

#define BUFFER_SIZE 1028;

class SZS_client{
private:
    static const uint16_t buffer_size = BUFFER_SIZE;
    uint8_t* comm_buffer;
    SZP_slave* szp;
    dummy_alsa_driver* alsa;

    static void szp_receive(SZP_slave* szp);
    static void alsa_play(dummy_alsa_driver* alsa);
protected:

public:
    SZS_client();
    int run();
};

#endif //SOUNDZONE_CLIENT_SZS_CLIENT_H
