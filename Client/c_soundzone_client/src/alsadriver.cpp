//
// Created by knham on 22-10-2021.
//
// libasound2-dev

#include "asoundlib.h"
#include "alsadriver.h"
#include <iostream>
#include <thread>
#include <string.h>

using namespace std;
#define ALSA_PCM_NEW_HW_PARAMS_API

void alsadriver::CharToFormat(const char* bitformat) {

    if (strcmp (bitformat, "SND_PCM_FORMAT_S16_LE") == 0) /** Signed 16 bit Little Endian */
        format = SND_PCM_FORMAT_S16_LE;
    else if (strcmp (bitformat, "SND_PCM_FORMAT_S16_BE") == 0) /** Signed 16 bit Big Endian */
        format = SND_PCM_FORMAT_S16_BE;
    else if (strcmp (bitformat, "SND_PCM_FORMAT_U16_LE") == 0) /** Unsigned 16 bit Little Endian */
        format = SND_PCM_FORMAT_U16_LE;
    else if (strcmp (bitformat, "SND_PCM_FORMAT_U16_BE")  == 0)	/** Unsigned 16 bit Big Endian */
        format = SND_PCM_FORMAT_U16_BE;
    else
        format = SND_PCM_FORMAT_UNKNOWN;

}



int alsadriver::startstreaming(unsigned int sampling_rate, int channels, const char* bitformat) {

    bool debug = true;
    int rc, dir;
    unsigned int val;
    char *buffer = NULL;
    int buff_size;
    int readfd, readval = 0;
    const char* readbuffer = "/home/pi/download/MYFIFO"; //"/home/pi/download/epic_sax_guy.raw";
    CharToFormat(bitformat);

    /* Open PCM device for playback. */
    rc = snd_pcm_open(&handle, "default",SND_PCM_STREAM_PLAYBACK, 0);
    if (rc < 0) {
        fprintf(stderr,
                "unable to open pcm device: %s\n",
                snd_strerror(rc));
        exit(1);
    }

    /* Allocate a hardware parameters object. */
    snd_pcm_hw_params_alloca(&params);

    /* Fill it in with default values. */
    snd_pcm_hw_params_any(handle, params);

    /* Set the desired hardware parameters. */

    /* Interleaved mode */
    snd_pcm_hw_params_set_access(handle, params,SND_PCM_ACCESS_RW_INTERLEAVED);
    /* Set format  */
    snd_pcm_hw_params_set_format(handle, params, format);

    /* Set period size to 32 frames. */
    //frames = 32;
    //snd_pcm_hw_params_set_period_size_near(handle, params, &frames, &dir);



    /* Two channels (stereo) */
    snd_pcm_hw_params_set_channels(handle, params, channels);



    /* 44100 bits/second sampling rate (CD quality) */
    snd_pcm_hw_params_set_rate_near(handle, params, &sampling_rate, &dir);


    /* Write the parameters to the driver */
    rc = snd_pcm_hw_params(handle, params);
    if (rc < 0) {
        fprintf(stderr,
                "unable to set hw parameters: %s\n",
                snd_strerror(rc));
        exit(1);
    }

    /* Allocate buffer to hold single period */
    snd_pcm_hw_params_get_period_size(params, &frames, 0);
   // printf("frames: %d\n", (int)frames);

    buff_size = frames * channels * 2 /* 2 -> sample size */;
    buffer = (char *) malloc(buff_size);
    memset(buffer, 0, buff_size);


    readfd = open(readbuffer, O_RDONLY);
    if (readfd < 0) {
        printf("Error reading file");
        exit(1);
    }

    if (debug == 1) {


        printf("PCM name: '%s'\n", snd_pcm_name(handle));

        printf("PCM state: %s\n",  snd_pcm_state_name(snd_pcm_state(handle)));

        snd_pcm_hw_params_get_rate(params, &val, 0);
        printf("rate: %d bps\n", val);

        snd_pcm_hw_params_get_channels(params, &val);
        printf("channels: %i ", val);

        snd_pcm_hw_params_get_format(params, reinterpret_cast<snd_pcm_format_t *>(&val));
        printf("format = '%s' (%s)\n",
               snd_pcm_format_name((snd_pcm_format_t) val),
               snd_pcm_format_description(
                       (snd_pcm_format_t) val));

    }

    while(readval = read(readfd, buffer, buff_size) > 0) {
        if (val = snd_pcm_writei(handle, buffer, frames) == -EPIPE) {
            fprintf(stderr, "Underrun!\n");
            snd_pcm_prepare(handle);
        } else if (val < 0) {
            fprintf(stderr, "Error writing to PCM device: %s\n", snd_strerror(val));
        }
    }

    snd_pcm_drain(handle);
    snd_pcm_close(handle);
    free(buffer);

    return 1;

}

void alsadriver::dropplayer(){
    snd_pcm_drop(handle);
    snd_pcm_close(handle);

}


void alsadriver::checksetup(){
    int rc, dir;
    unsigned int val, val2;

    /* Display information about the PCM interface */

    printf("PCM handle name = '%s'\n",
           snd_pcm_name(handle));

    printf("PCM state = %s\n",
           snd_pcm_state_name(snd_pcm_state(handle)));

    snd_pcm_hw_params_get_access(params,
                                (snd_pcm_access_t *) &val);
    printf("access type = %s\n",
           snd_pcm_access_name((snd_pcm_access_t) val));

    snd_pcm_hw_params_get_format(params, reinterpret_cast<snd_pcm_format_t *>(&val));
    printf("format = '%s' (%s)\n",
           snd_pcm_format_name((snd_pcm_format_t) val),
           snd_pcm_format_description(
                   (snd_pcm_format_t) val));



    printf("subformat = '%s' (%s)\n",
           snd_pcm_subformat_name((snd_pcm_subformat_t) val),
           snd_pcm_subformat_description(
                   (snd_pcm_subformat_t) val));


    snd_pcm_hw_params_get_channels(params, &val);
    printf("channels = %d\n", val);

    snd_pcm_hw_params_get_rate(params, &val, &dir);
    printf("rate = %d bps\n", val);

    snd_pcm_hw_params_get_period_time(params,
                                      &val, &dir);
    printf("period time = %d us\n", val);

    snd_pcm_hw_params_get_period_size(params,
                                      &frames, &dir);
    printf("period size = %d frames\n", (int) frames);

    snd_pcm_hw_params_get_buffer_time(params,
                                      &val, &dir);
    printf("buffer time = %d us\n", val);

    snd_pcm_hw_params_get_buffer_size(params,
                                      (snd_pcm_uframes_t *) &val);
    printf("buffer size = %d frames\n", val);

    snd_pcm_hw_params_get_periods(params, &val, &dir);
    printf("periods per buffer = %d frames\n", val);

    snd_pcm_hw_params_get_rate_numden(params,
                                      &val, &val2);
    printf("exact rate = %d/%d bps\n", val, val2);

    val = snd_pcm_hw_params_get_sbits(params);
    printf("significant bits = %d\n", val);

    snd_pcm_hw_params_get_tick_time(params,
                                    &val, &dir);
    printf("tick time = %d us\n", val);

    val = snd_pcm_hw_params_is_batch(params);
    printf("is batch = %d\n", val);

    val = snd_pcm_hw_params_is_block_transfer(params);
    printf("is block transfer = %d\n", val);

    val = snd_pcm_hw_params_is_double(params);
    printf("is double = %d\n", val);

    val = snd_pcm_hw_params_is_half_duplex(params);
    printf("is half duplex = %d\n", val);

    val = snd_pcm_hw_params_is_joint_duplex(params);
    printf("is joint duplex = %d\n", val);

    val = snd_pcm_hw_params_can_overrange(params);
    printf("can overrange = %d\n", val);

    val = snd_pcm_hw_params_can_mmap_sample_resolution(params);
    printf("can mmap = %d\n", val);

    val = snd_pcm_hw_params_can_pause(params);
    printf("can pause = %d\n", val);

    val = snd_pcm_hw_params_can_resume(params);
    printf("can resume = %d\n", val);

    val = snd_pcm_hw_params_can_sync_start(params);
    printf("can sync start = %d\n", val);
}

int alsadriver::SetVolume(int volume)
{
    long min, max;
    snd_mixer_t *handlel;
    snd_mixer_selem_id_t *sid;
    const char *card = "hw:0";
    const char *selem_name = "default";


    snd_mixer_open(&handlel, 0);
    snd_mixer_attach(handlel, card);
    snd_mixer_selem_register(handlel, NULL, NULL);
    snd_mixer_load(handlel);

    snd_mixer_selem_id_malloc(&sid);
    snd_mixer_selem_id_set_index(sid, 0);
    snd_mixer_selem_id_set_name(sid, selem_name);
    snd_mixer_elem_t* elem = snd_mixer_find_selem(handlel, sid);

    snd_mixer_selem_get_playback_volume_range(elem, &min, &max);
    snd_mixer_selem_set_playback_volume_all(elem, volume * max / 100);

    snd_mixer_close(handlel);

    return 1;

}

void alsadriver::pauseplay(int state){
   // snd_pcm_pause(handle, state);

}