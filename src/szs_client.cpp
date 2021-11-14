//
// Created by ncpd on 11-11-2021.
//

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <cerrno>
#include <fcntl.h>
#include <thread>

#include "szs_client.h"

/**********************************************************************************************************************
 * Public methods
 **********************************************************************************************************************/

SZS_client::SZS_client(){
    comm_buffer = new uint8_t[buffer_size];
    char fifo_file[] = "/tmp/music_fifo";

    if(mkfifo(fifo_file, 0777) < 0){
        if(errno != EEXIST){
            std::cout << "Could not create fifo file" << std::endl;
        }else{
            std::cout << "Fifo is made" << std::endl;
        }
    }

    szp = new SZP_slave(comm_buffer, buffer_size, fifo_file);
    alsa = new dummy_alsa_driver(fifo_file);

    std::thread t_szp(&SZP_slave::open_fifo, szp);
    std::thread t_alsa(&dummy_alsa_driver::open_fifo, alsa);

    t_szp.join();
    t_alsa.join();
};

int SZS_client::run() {

    std::thread t_szp(szp_receive, this->szp);
    std::thread t_alsa(alsa_play, this->alsa);

    if (t_szp.joinable()){
        t_szp.join();
    }
    if(t_alsa.joinable()){
        t_alsa.join();
    }
    return 0;
}

/**********************************************************************************************************************
 * Private methods
 **********************************************************************************************************************/

void SZS_client::szp_receive(SZP_slave* szp) {
    int err;
    while (true){
        err = szp->recieve();

        if(err < 0){
            return;
        }
    }
}

void SZS_client::alsa_play(dummy_alsa_driver *alsa) {
    int err;
    while (true){
        err = alsa->read_buffer();

        if(err < 0){
            return;
        }
    }
}