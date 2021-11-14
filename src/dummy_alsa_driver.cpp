//
// Created by ncpd on 13-11-2021.
//

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <cerrno>
#include <fcntl.h>

#include "dummy_alsa_driver.h"


#define BUFFER_SIZE 1028
uint8_t buffer[BUFFER_SIZE];

dummy_alsa_driver::dummy_alsa_driver(char* fifo_name) {
    fd = 0;
    this->fifo_name = fifo_name;
    this->p_buffer = new buffer_t(buffer, (uint16_t)BUFFER_SIZE);
}

int dummy_alsa_driver::open_fifo() {

    std::cout << "Before open, dummy" << std::endl;
    fd = open(fifo_name, O_RDONLY);

    std::cout << "After open, dummy" << std::endl;

    return 0;
}

int dummy_alsa_driver::read_buffer() const {
    int n_bytes;
    n_bytes = read(fd, buffer, BUFFER_SIZE);
    p_buffer->set_write_head(n_bytes);
    p_buffer->print_buffer();
    return 0;
}

