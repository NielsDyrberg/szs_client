#include <iostream>
#include "test_src.h"
#include "bcm2835.h"
#include <alsadriver.h>
//#include "alsadriver.h"
//#include "asoundlib.h"



alsadriver dacdriver;

int main() {
    dacdriver.displayformat();
    //displayformat();
    //std::cout << "Hello, World!" << std::endl;
    //std::cout << test_projectLink() << std::endl;
    //testSrcHello();

    return 0;
}
