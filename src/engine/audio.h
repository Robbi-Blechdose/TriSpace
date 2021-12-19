#ifndef _MUSIC_H
#define _MUSIC_H

#include "SDL_mixer.h"

#define NUM_MIX_CHANNELS 4

void initAudio(uint8_t volume, uint8_t nm, uint8_t ns);
void quitAudio();

//Music functions

void loadMusic(uint8_t index, char* filename);
void playMusic(uint8_t index, uint16_t fadeIn);
void stopMusic(uint16_t fadeOut);

//Sample functions

uint8_t loadSample(char* filename);
void playSample(uint8_t index);

#endif