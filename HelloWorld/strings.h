#pragma once

#include <avr/pgmspace.h>

const char gold0[] PROGMEM = "gold";

const char * const gold[] PROGMEM =
{
	gold0
};

const char food0[] PROGMEM = "food";
const char food1[] PROGMEM = "mold";

const char * const food[] PROGMEM =
{
	food0,
	food1,
};

const char weapon0[] PROGMEM = "mace";
const char weapon1[] PROGMEM = "axe";
const char weapon2[] PROGMEM = "sword";
const char weapon3[] PROGMEM = "bow";
const char weapon4[] PROGMEM = "dart";
const char weapon5[] PROGMEM = "arrow";
const char weapon6[] PROGMEM = "shuriken";
const char weapon7[] PROGMEM = "dagger";

const char * const weapon[WEMAX] PROGMEM =
{
	weapon0,
	weapon1,
	weapon2,
	weapon3,
	weapon4,
	weapon5,
	weapon6,
	weapon7,
};

const char armour0[] PROGMEM = "leather";
const char armour1[] PROGMEM = "ring";
const char armour2[] PROGMEM = "scale";
const char armour3[] PROGMEM = "chain";
const char armour4[] PROGMEM = "splint";
const char armour5[] PROGMEM = "banded";
const char armour6[] PROGMEM = "plate";

const char * const armour[ARMAX] PROGMEM =
{
	armour0,
	armour1,
	armour2,
	armour3,
	armour4,
	armour5,
	armour6,
};

const char colour0[] PROGMEM = "amber";
const char colour1[] PROGMEM = "black";
const char colour2[] PROGMEM = "blue";
const char colour3[] PROGMEM = "brown";
const char colour4[] PROGMEM = "clear";
const char colour5[] PROGMEM = "cyan";
const char colour6[] PROGMEM = "gold";
const char colour7[] PROGMEM = "green";
const char colour8[] PROGMEM = "grey";
const char colour9[] PROGMEM = "pink";
const char colour10[] PROGMEM = "red";
const char colour11[] PROGMEM = "violet";
const char colour12[] PROGMEM = "white";
const char colour13[] PROGMEM = "yellow";

const char * const colour[POMAX] PROGMEM =
{
	colour0,
	colour1,
	colour2,
	colour3,
	colour4,
	colour5,
	colour6,
	colour7,
	colour8,
	colour9,
	colour10,
	colour11,
	colour12,
	colour13,
};

const char label0[] PROGMEM = "ZELGO";
const char label1[] PROGMEM = "JUYED";
const char label2[] PROGMEM = "NR 9";
const char label3[] PROGMEM = "XIXAXA";
const char label4[] PROGMEM = "DAIYEN";
const char label5[] PROGMEM = "ELBIB";
const char label6[] PROGMEM = "THARR";
const char label7[] PROGMEM = "YUM YUM";
const char label8[] PROGMEM = "ANDOVA";
const char label9[] PROGMEM = "FOOBIE";
const char label10[] PROGMEM = "TEMOV";
const char label11[] PROGMEM = "READ ME";

const char * const label[SCMAX] PROGMEM =
{
	label0,
	label1,
	label2,
	label3,
	label4,
	label5,
	label6,
	label7,
	label8,
	label9,
	label10,
	label11,
};

const char stone0[] PROGMEM = "agate";
const char stone1[] PROGMEM = "amethyst";
const char stone2[] PROGMEM = "diamond";
const char stone3[] PROGMEM = "emerald";
const char stone4[] PROGMEM = "garnet";
const char stone5[] PROGMEM = "onyx";
const char stone6[] PROGMEM = "opal";
const char stone7[] PROGMEM = "pearl";
const char stone8[] PROGMEM = "sapphire";
const char stone9[] PROGMEM = "topaz";

const char * const stone[RGMAX] PROGMEM =
{
	stone0,
	stone1,
	stone2,
	stone3,
	stone4,
	stone5,
	stone6,
	stone7,
	stone8,
	stone9,
};

const char metal0[] PROGMEM = "brass";
const char metal1[] PROGMEM = "bronze";
const char metal2[] PROGMEM = "copper";
const char metal3[] PROGMEM = "iron";
const char metal4[] PROGMEM = "lead";
const char metal5[] PROGMEM = "nickel";
const char metal6[] PROGMEM = "steel";
const char metal7[] PROGMEM = "silver";
const char metal8[] PROGMEM = "tin";
const char metal9[] PROGMEM = "zinc";

const char * const metal[WDMAX] PROGMEM =
{
	metal0,
	metal1,
	metal2,
	metal3,
	metal4,
	metal5,
	metal6,
	metal7,
	metal8,
	metal9,
};

const char potion0[] PROGMEM = "power";
const char potion1[] PROGMEM = "restore";
const char potion2[] PROGMEM = "heal";
const char potion3[] PROGMEM = "e.heal";
const char potion4[] PROGMEM = "poison";
const char potion5[] PROGMEM = "level";
const char potion6[] PROGMEM = "blind";
const char potion7[] PROGMEM = "hallu";
const char potion8[] PROGMEM = "m.detect";
const char potion9[] PROGMEM = "i.detect";
const char potion10[] PROGMEM = "confuse";
const char potion11[] PROGMEM = "levitate";
const char potion12[] PROGMEM = "speed";
const char potion13[] PROGMEM = "look";

const char * const potion[POMAX] PROGMEM =
{
	potion0,
	potion1,
	potion2,
	potion3,
	potion4,
	potion5,
	potion6,
	potion7,
	potion8,
	potion9,
	potion10,
	potion11,
	potion12,
	potion13,
};

const char scroll0[] PROGMEM = "protect";
const char scroll1[] PROGMEM = "hold";
const char scroll2[] PROGMEM = "weapon";
const char scroll3[] PROGMEM = "armour";
const char scroll4[] PROGMEM = "identify";
const char scroll5[] PROGMEM = "telport";
const char scroll6[] PROGMEM = "sleep";
const char scroll7[] PROGMEM = "scare";
const char scroll8[] PROGMEM = "bless";
const char scroll9[] PROGMEM = "create";
const char scroll10[] PROGMEM = "anger";
const char scroll11[] PROGMEM = "map";

const char * const scroll[SCMAX] PROGMEM =
{
	scroll0,
	scroll1,
	scroll2,
	scroll3,
	scroll4,
	scroll5,
	scroll6,
	scroll7,
	scroll8,
	scroll9,
	scroll10,
	scroll11,
};

const char ring0[] PROGMEM = "stealth";
const char ring1[] PROGMEM = "teleport";
const char ring2[] PROGMEM = "life";
const char ring3[] PROGMEM = "food";
const char ring4[] PROGMEM = "damage";
const char ring5[] PROGMEM = "strong";
const char ring6[] PROGMEM = "gold";
const char ring7[] PROGMEM = "dex";
const char ring8[] PROGMEM = "adorn";
const char ring9[] PROGMEM = "see";
const char ring10[] PROGMEM = "armour";
const char ring11[] PROGMEM = "search";

const char * const ring[RGMAX] PROGMEM =
{
	ring0,
	ring1,
	ring2,
	ring3,
	ring4,
	ring5,
	ring6,
	ring7,
	ring8,
	ring9,
	ring10,
	ring11,
};

const char wand0[] PROGMEM = "teleport";
const char wand1[] PROGMEM = "slow";
const char wand2[] PROGMEM = "confuse";
const char wand3[] PROGMEM = "clear";
const char wand4[] PROGMEM = "change";
const char wand5[] PROGMEM = "fast";
const char wand6[] PROGMEM = "sleep";
const char wand7[] PROGMEM = "missile";
const char wand8[] PROGMEM = "cancel";
const char wand9[] PROGMEM = "nothing";

const char * const wand[WDMAX] PROGMEM =
{
	wand0,
	wand1,
	wand2,
	wand3,
	wand4,
	wand5,
	wand6,
	wand7,
	wand8,
	wand9,
};

const char amulet0[] PROGMEM = "Yendor";

const char * const amulet[1] PROGMEM =
{
	amulet0,
};

const char message0[] PROGMEM = "you hit ";
const char message1[] PROGMEM = "you miss ";
const char message2[] PROGMEM = "no space";
const char message3[] PROGMEM = "something here";
const char message4[] PROGMEM = "no slot";
const char message5[] PROGMEM = "dir?";
const char message6[] PROGMEM = "level up";
const char message7[] PROGMEM = "Oops...";
const char message8[] PROGMEM = "Yummy";
const char message9[] PROGMEM = "it cursed";
const char message10[] PROGMEM = "removed";
const char message11[] PROGMEM = "ready go";
const char message12[] PROGMEM = "alread wield";
const char message13[] PROGMEM = "frozen";
const char message14[] PROGMEM = "poisoned";
const char message15[] PROGMEM = "stolen";
const char message16[] PROGMEM = "water";
const char message17[] PROGMEM = "held";
const char message18[] PROGMEM = "graced";
const char message19[] PROGMEM = "burned";
const char message20[] PROGMEM = "level down";
const char message21[] PROGMEM = "drained";

const char * const messages[22] PROGMEM =
{
	message0,
	message1,
	message2,
	message3,
	message4,
	message5,
	message6,
	message7,
	message8,
	message9,
	message10,
	message11,
	message12,
	message13,
	message14,
	message15,
	message16,
	message17,
	message18,
	message19,
	message20,
	message21,
};

const char selectorString[] PROGMEM = "> ";
const char blankString[] PROGMEM = "  ";
