#include <iostream>
#include "test_src.h"
#include "bcm2835.h"
#include <alsadriver.h>
//#include "alsadriver.h"
//#include "asoundlib.h"



alsadriver dacdriver;

int main() {
    dacdriver.startstreaming(8000, 1, "SND_PCM_FORMAT_S16_BE");
    dacdriver.checksetup();
    return 0;
}
