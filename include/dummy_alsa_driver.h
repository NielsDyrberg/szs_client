//
// Created by ncpd on 13-11-2021.
//

#ifndef SOUNDZONE_CLIENT_DUMMY_ALSA_DRIVER_H
#define SOUNDZONE_CLIENT_DUMMY_ALSA_DRIVER_H

#include "szp_custom_types.h"

class dummy_alsa_driver{
public:
    explicit dummy_alsa_driver(char* fifo_name);
    ~dummy_alsa_driver();
    int open_fifo();
    int read_buffer() const;

private:
    buffer_t* p_buffer;
    char* fifo_name;
    int fd;
};

#endif //SOUNDZONE_CLIENT_DUMMY_ALSA_DRIVER_H
