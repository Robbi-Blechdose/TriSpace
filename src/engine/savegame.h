#ifndef _SAVEGAME_H
#define _SAVEGAME_H

#include <stdint.h>

void openSave(char* name, uint8_t writing);
void writeElement(void* ptr, uint16_t size);
void readElement(void* ptr, uint16_t size);
void closeSave();

#endif