#pragma once

#include <avr/pgmspace.h>

#include "strings.h"
#include "FlashStringHelper.h"

inline const char * readProgmem(const char * const * progmemPointer)
{
	return static_cast<const char *>(pgm_read_ptr(progmemPointer));
}

inline const char * getItemName(byte type, byte r, byte k)
{
	switch(type)
	{
		case 1:
			return readProgmem(&gold[r]);
		case 2:
			return readProgmem(&food[r]);
		case 3:
			return readProgmem(&weapon[r]);
		case 4:
			return readProgmem(&armour[r]);
		case 5:
			if(k == 0)
				return readProgmem(&colour[r]);
			else
				return readProgmem(&potion[ptab[r]]);
		case 6:
			if(k == 0)
				return readProgmem(&label[r]);
			else
				return readProgmem(&scroll[stab[r]]);
		case 7:
			if(k == 0)
				return readProgmem(&stone[r]);
			else
				return readProgmem(&ring[rtab[r]]);
		case 8:
			if(k == 0)
				return readProgmem(&metal[r]);
			else
				return readProgmem(&wand[wtab[r]]);
		case 9:
			return readProgmem(&amulet[r]);
		default:
			return nullptr;
	}
}

inline FlashStringHelper getPrintableItemName(byte type, byte r, byte k)
{
	return asFlashStringHelper(getItemName(type, r, k));
}