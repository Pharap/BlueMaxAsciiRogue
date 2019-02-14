#define WEMAX   8     //9
#define ARMAX   7     //8
#define POMAX   14    //14
#define SCMAX   12    //14
#define RGMAX   12    //14
#define WDMAX   10    //14
#define RMAX    2
#define IMAX    26
#define TMAX    40
#define MMAX    16

#include <Arduboy2.h>
Arduboy2 arduboy;

const char tsym[9] PROGMEM = {'*', ':', ')', '[', '!', '?', '=', '/', ','};
const char tprob[9] PROGMEM = {0, 10, 15, 24, 33, 63, 93, 96, 100};
const char pprob[POMAX+1] PROGMEM = {0, 5, 10, 20, 25, 35, 40, 50, 60, 65, 75, 85, 90, 95, 100};
const char sprob[SCMAX+1] PROGMEM = {0, 5, 10, 15, 20, 35, 45, 55, 65, 75, 85, 90, 100};
//const char v[9] PROGMEM = {1, 2, 9, 8, 14, 14, 14, 14, 1};
//const char tprob[8] PROGMEM = {10,5,9,9,30,30,3,4};
//const char pprob[14] PROGMEM = {7,8,8,13,3,13,6,6,2,5,5,13,5,6};
//const char sprob[14] PROGMEM = {7,4,2,3,7,43,3,2,5,8,4,7,3,2};

const char mname[26] PROGMEM = {
  'K', 'E', 'B', 'S', 'H', 'I', 'R', 'O',
  'Z', 'L', 'C', 'Q', 'A', 'N', 'Y', 'F',
  'T', 'W', 'P', 'X', 'U', 'M', 'V', 'G',
  'J', 'D'
};

const char mstat[26][7] PROGMEM = { 
//  hp,  r+XdY, dex, exp,item, state
  { 10,  1,  4,  60,   2,   0, 0b10000011},  // 0 K  76543210
  { 11,  1,  3,  65,   2,   0, 0b00000010},  // 1 E         wake
  { 10,  1,  3,  60,   2,   0, 0b00100101},  // 2 B        sleep (mimic is sleep and deep sleep)
  {  8,  1,  3,  50,   2,   0, 0b00000011},  // 3 S       deep sleep
  { 15,  2,  5,  67,   3,   0, 0b00000011},  // 4 H      NC
  { 15,  0,  0,  68,   5,   0, 0b00000100},  // 5 I     special attack(for medusa's grace)
  { 19,  2, 10,  70,  10,   0, 0b00000011},  // 6 R    wanderer
  { 25,  1,  5,  70,   5,  10, 0b00000011},  // 7 O   transparent
  { 21,  1,  7,  69,   8,   0, 0b00000011},  // 8 Z  fast
  { 25,  0,  0,  75,  21, 100, 0b00000100},  // 9 L
  { 32,  5, 19,  85,  15,  10, 0b00000101},  //10 C
  { 30,  3, 15,  78,  20,  20, 0b00000011},  //11 Q
  { 25,  0,  0, 100,  20,   0, 0b00000011},  //12 A
  { 25,  0,  0,  75,  39, 100, 0b00000100},  //13 N
  { 35,  3, 18,  80,  50,  20, 0b00000101},  //14 Y
  { 73,  0,  0,  80,  91,   0, 0b00000001},  //15 F
  { 75,  5, 28,  75, 125,  33, 0b00000011},  //16 T
  { 45,  2, 16,  75,  55,   0, 0b00000101},  //17 W
  { 76,  5, 20,  80, 120,  50, 0b01100101},  //18 P
  { 42,  4, 24,  75, 110,   0, 0b00000110},  //19 X
  { 90,  4, 40,  85, 200,  33, 0b00000011},  //20 U
  { 97,  7, 37,  85, 250,  25, 0b00000011},  //21 M
  { 55,  2, 18,  85, 255,  18, 0b00000011},  //22 V
  {115, 10, 50,  85, 255,  10, 0b10000011},  //23 G
  {132,  7, 50, 100, 255,   0, 0b00000101},  //24 J
  {145,  8, 60, 100, 255,  90, 0b00000010}   //25 D
};
const char wstat[WEMAX][2] PROGMEM = {
  { 2, 3}, { 3, 4}, { 4, 5}, { 1, 1}, { 1, 1}, { 1, 2}, { 1, 3}, { 1, 4}
};
const char astat[ARMAX] PROGMEM = {
  2, 3, 4, 5, 6, 6, 7
};

byte dungeon[21][8];
byte known[3][8];
byte monst[21][8];
byte thing[21][8];

byte hx = 0, hy = 0, im = 5, dlv = 1, st = 16, stm = 16, lv = 1;
byte ss = 0;      //show status flag
byte hconf = 0, hblnd=0, hhall=0, hfast=0, hslep=0;
byte hmdet=0,hisee=0,hlevi=0, hheld=0;
char rdex=0, rstr=0;
long int au = 0, hp = 16, hpm = 16, ex = 0, ht = 0, hh = 1200, nl = 10;
//byte he = 0b11000000; , hw=2, ha=5, hr=0, hl=0;
//byte hdmg = 4, hdex = 3, ac = 4;

char roomSX[RMAX*2] = {}, roomSY[RMAX*2] = {}, roomEX[RMAX*2] = {}, roomEY[RMAX*2] = {};
byte hasRoom[RMAX*2] = {};
byte isDark[RMAX*2] = {};
byte mx[MMAX] = {}, my[MMAX] = {}, ms[MMAX] = {}, mh[MMAX] = {}, m1[MMAX] = {}, m2[MMAX] = {};
byte id[TMAX] = {}, t1[TMAX] = {}, t4[TMAX] = {};
byte ii[IMAX] = {}, i1[IMAX] = {}, i4[IMAX] = {};
byte fi = 0, f1 =0, f4=0;
char t2[TMAX] = {}, t3[TMAX] = {};
byte i2[IMAX] = {}, i3[IMAX] = {};
char f2 = 0, f3 =0;
byte ptab[POMAX] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
byte stab[SCMAX] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
byte rtab[RGMAX] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
byte wtab[WDMAX] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
unsigned int pknow = 0, sknow = 0, rknow = 0, wknow = 0;
//char buf[21];

#include "FlashStringHelper.h"

FlashStringHelper activeMessage = nullptr;
//char gbuf[22];
char gmon[10];
//char gitm[8];
char gmes[15];

byte gstate = 0;

void setup() {
  byte r;
//  byte eep=EEPROM.read(10);
//  arduboy.begin();
  arduboy.boot();
  arduboy.setFrameRate(15);

  arduboy.initRandomSeed();

  Serial.begin(9600);

  for (int i = 0; i < 50; i++) {
    byte r1 = random(POMAX);
    byte r2 = random(POMAX);
    byte tmp = ptab[r1];
    ptab[r1] = ptab[r2];
    ptab[r2] = tmp;
  }
  for (int i = 0; i < 50; i++) {
    byte r1 = random(SCMAX);
    byte r2 = random(SCMAX);
    byte tmp = stab[r1];
    stab[r1] = stab[r2];
    stab[r2] = tmp;
  }
  for (int i = 0; i < 50; i++) {
    byte r1 = random(RGMAX);
    byte r2 = random(RGMAX);
    byte tmp = rtab[r1];
    rtab[r1] = rtab[r2];
    rtab[r2] = tmp;
  }
  for (int i = 0; i < 50; i++) {
    byte r1 = random(WDMAX);
    byte r2 = random(WDMAX);
    byte tmp = wtab[r1];
    wtab[r1] = wtab[r2];
    wtab[r2] = tmp;
  }
  clearKnown();

  clearDungeon();
  makeDungeon4();
  placeMonst();
  placeThing();

/*
  for (int i = 0; i < 16; i++) {
    mh[i] = random(14);
    m1[i] = random(14);
    m2[i] = random(14);
  }
*/
  byte w=8;
  ii[0] = 2 * 16 + 0; i1[0] = 1; i2[0] = 0; i3[0] = 0; i4[0] = 0b10000000;
  ii[1] = 3 * 16 + 0; i1[1] = 1; i2[1] = 1; i3[1] = 1; i4[1] = 0b00110000;
  ii[2] = 3 * 16 + 3; i1[2] = 1; i2[2] = 1; i3[2] = 0; i4[2] = 0b00100000;
  ii[3] = 3 * 16 + 5; i1[3] = 30; i2[3] = 0; i3[3] = 0; i4[3] = 0b10100000;
  ii[4] = 4 * 16 + 1; i1[4] = 1; i2[4] = 1; i3[4] = 0; i4[4] = 0b00110000;
/*
  ii[5] = 6 * 16 + findScroll(7); i1[5] = 5; i2[5] = 0; i3[5] = 0; i4[5] = 0b10000000;
  ii[6] = 6 * 16 + findScroll(9); i1[6] = 20; i2[6] = 0; i3[6] = 0; i4[6] = 0b10000000;
  
  ii[7] = w * 16 + 2; i1[7] = 1; i2[7] = 5; i3[7] = 0; i4[7] = 0b10000000;
  ii[8] = w * 16 + 3; i1[8] = 1; i2[8] = 5; i3[8] = 0; i4[8] = 0b10000000;
  ii[9] = w * 16 + 4; i1[9] = 1; i2[9] = 5; i3[9] = 0; i4[9] = 0b10000000;
  ii[10] = w * 16 + 5; i1[10] = 1; i2[10] = 5; i3[10] = 0; i4[10] = 0b10000000;
  ii[11] = w * 16 + 6; i1[11] = 1; i2[11] = 5; i3[11] = 0; i4[11] = 0b10000000;
  ii[12] = w * 16 + 7; i1[12] = 1; i2[12] = 5; i3[12] = 0; i4[12] = 0b10000000;
  ii[13] = w * 16 + 8; i1[13] = 1; i2[13] = 5; i3[13] = 0; i4[13] = 0b10000000;
  ii[14] = w * 16 + 9; i1[14] = 1; i2[14] = 5; i3[14] = 0; i4[14] = 0b10000000;
  ii[15] = w * 16 + 10; i1[15] = 1; i2[15] = 5; i3[15] = 0; i4[15] = 0b10000000;
  ii[16] = w * 16 + 11; i1[16] = 1; i2[16] = 5; i3[16] = 0; i4[16] = 0b10000000;
  ii[17] = w * 16 + 12; i1[17] = 1; i2[17] = 5; i3[17] = 0; i4[17] = 0b10000000;
  ii[18] = w * 16 + 13; i1[18] = 1; i2[18] = 5; i3[18] = 0; i4[18] = 0b10000000;
*/
  sortItem();
//  if (!(arduboy.nextFrame())) return;
//  arduboy.clear();
}

void loop() {
  byte tmp;
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  arduboy.clear();
  switch (gstate) {
    case 0:
      title();
      break;
    case 1:
      gameloop();
      break;
    case 2:
      gameover();
      break;
    case 3:
      winner();
      break;
  }
  arduboy.display();
}

