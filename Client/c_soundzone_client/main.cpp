#include <iostream>
#include "bcm2835.h"
#include "alsadriver.h"
//#include "alsadriver.h"
//#include "asoundlib.h"



alsadriver dacdriver;

int main() {
   // dacdriver.startstreaming(44100, 2, "SND_PCM_FORMAT_S16_LE");
    dacdriver.playmusic();
    dacdriver.checksetup();
    return 0;
}
