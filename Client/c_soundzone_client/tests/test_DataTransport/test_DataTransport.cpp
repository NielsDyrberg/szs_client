//
// Created by ncpd on 22-10-2021.
//
#include <iostream>
#include "dataTransport.h"

void test_send(){
    char hostname[] = "rpi4-master";
    DataTransport dt;
    // char* tmp_hostname = dt.GetHostname();
    uint8_t msgToSend[] = {255, 3, 53, 35, 42};
    dt.send(msgToSend, sizeof(msgToSend));
}

void test_recv(){
    char hostname[] = "rpi3-master";
    uint8_t* bufPTR = nullptr;
    uint16_t size = 0;
    DataTransport dt;
    dt.receive();
    bufPTR = dt.GetBuffer(bufPTR, &size);
    for(int i = 0; i < size; i++){
        std::cout << unsigned(*bufPTR) << std::endl;
        bufPTR++;
    }
    std::cout << "Hello, World!" << std::endl;
}

int main(){
    test_recv();
    return 0;
}