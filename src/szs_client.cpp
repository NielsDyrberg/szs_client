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
#include "alsadriver.h"

using namespace std;

/**********************************************************************************************************************
 * Public methods
 **********************************************************************************************************************/

SZS_client::SZS_client(){
    char *fifo_file = "/tmp/rcv_file.wav";

//    if(mkfifo(fifo_file, 0777) < 0){
//        if(errno != EEXIST){
//            cout << "Could not create fifo file" << std::endl;
//        }else{
//            cout << "Fifo is made" << std::endl;
//        }
//    }

    sync = new SYNC_handler();
    szp = new SZP_slave(fifo_file);
    alsa = new alsadriver();

    thread t_szp(&SZP_slave::open_fifo, szp);
    alsa->readbuffer = fifo_file;

    t_szp.join();

};

int SZS_client::run() {
    thread t_sync(run_sync_handler, this->sync);
    thread t_szp(szp_receive, this->szp);
    thread t_alsa(&alsadriver::startstreaming, alsa, 44100, 2, "SND_PCM_FORMAT_S16_LE");
    thread t_tied_up(&SZS_client::play_music_when_ready, this->sync, this->alsa, this->szp);


    if(t_sync.joinable()){
        t_sync.join();
    }
    if (t_szp.joinable()){
        t_szp.join();
    }
    if(t_alsa.joinable()){
        t_alsa.join();
    }
    if(t_tied_up.joinable()){
        t_tied_up.join();
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

void SZS_client::run_sync_handler(SYNC_handler* sync_handler){
    sync_handler->run();
}

void SZS_client::play_music_when_ready(SYNC_handler* sync_handler, alsadriver* alsa_obj, SZP_slave* szp){
    long long int play_time = TIME_NOT_SET;
    int err = 0;

    std::cout << "play tume: " << play_time << std::endl;

    while (true){
        err = szp->get_time(&play_time);
        if(err == 0){
            break;
        }
    }
    std::cout << "play Updated: " << play_time << std::endl;

    sync_handler->return_when(play_time);

    alsa_obj->run_on = true;
}