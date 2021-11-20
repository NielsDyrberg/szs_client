//
// Created by knham on 22-10-2021.
//
#ifndef C_SOUNDZONE_CLIENT_ALSADRIVER_H
#define C_SOUNDZONE_CLIENT_ALSADRIVER_H
#include "alsa/asoundlib.h"

class alsadriver {

    public:

        /*
        * Display the hardware setup if the alsa driver
        */
        void checksetup();
        /*
        * Starts playing music
        */
        void startstreaming(unsigned sampling_rate = 2, int channels = 44100, const char* bitformat = "SND_PCM_FORMAT_S16_LE");
        /*
        * Start/stops reading from buffer
        */
        bool run_on = false;
        /*
        * Char holding the location of the file to be read
        */
        char* readbuffer; //"/home/pi/download/epic_sax_guy.raw";

    private:
        // Variables used for running the alsa driver
        snd_pcm_format_t format;
        snd_pcm_hw_params_t *params;
        snd_pcm_t *handle;
        snd_pcm_uframes_t frames;
        int rc, dir;
        unsigned int val, val2;


        /*
        * Convertes format to enum
        */
        void CharToFormat(const char* bitformat);




};



#endif //C_SOUNDZONE_CLIENT_ALSADRIVER_H
