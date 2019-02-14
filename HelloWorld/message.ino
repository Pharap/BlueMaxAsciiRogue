#include <avr/pgmspace.h>

#include "strings.h"
#include "messaging.h"

void clearBuf()
{
	activeMessage = nullptr;
}

void setActiveMessage(byte id)
{
	activeMessage = asFlashStringHelper(pgm_read_ptr(&messages[id]));
}

/*void addBuf(char array[])
{
}*/


void itmToGitm(byte type, byte r, byte k)
{
	activeMessage = asFlashStringHelper(getItemName(type, r, k));
}

