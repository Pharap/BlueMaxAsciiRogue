byte randThing() {
  byte done = 0;
  byte count = 0;
  byte r = random(100);
  while (done == 0) {
    if (r >= pgm_read_byte(tprob + count) && r <= pgm_read_byte(tprob + count + 1) - 1) {
      done = 1;
    } else {
      count++;
    }
  }
  return count + 1;
}

byte randPotion() {
  byte done = 0;
  byte count = 0;
  byte r = random(100);
  while (done == 0) {
    if (r >= pgm_read_byte(pprob + ptab[count]) && r <= pgm_read_byte(pprob + ptab[count] + 1) - 1) {
      done = 1;
    } else {
      count++;
    }
  }
  return count;
}

byte randScroll() {
  byte done = 0;
  byte count = 0;
  byte r = random(100);
  while (done == 0) {
    if (r >= pgm_read_byte(sprob + stab[count]) && r <= pgm_read_byte(sprob + stab[count] + 1) - 1) {
      done = 1;
    } else {
      count++;
    }
  }
  return count;
}

byte freeSlot() {
  byte done = 0;
  byte count = 0;
  while (done == 0) {
    if ( id[count] == 0 ) {
      done = 1;
    } else {
      count++;
      if (count == TMAX) {
        done = 1;
      }
    }
  }
  return count;
}

byte sortItem() {
  byte count = 0;
  for (int i = 0; i < IMAX; i++) {
    if (ii[i] == 0) {
      ii[i] = 255;
      count++;
    }
  }
  for (int i = 0; i < IMAX; ++i) {
    for (int j = i + 1; j < IMAX; ++j) {
      if (ii[i] > ii[j]) {
        byte tmp1 =  ii[i];
        byte tmp2 =  i1[i];
        byte tmp3 =  i2[i];
        byte tmp4 =  i3[i];
        byte tmp5 =  i4[i];
        ii[i] = ii[j];
        i1[i] = i1[j];
        i2[i] = i2[j];
        i3[i] = i3[j];
        i4[i] = i4[j];
        ii[j] = tmp1;
        i1[j] = tmp2;
        i2[j] = tmp3;
        i3[j] = tmp4;
        i4[j] = tmp5;
      }
    }
  }
  for (int i = 0; i < IMAX; i++) {
    if (ii[i] == 255) {
      ii[i] = 0;
    }
  }
  return 20 - count;
}

byte findScroll(byte t) {
  for (byte i = 0; i < SCMAX; i++) {
    if (stab[i] == t) return i;
  }
}

void dropItem(byte x, byte y, byte st) {
  if (bitRead(i4[st], 4) == 0) {
    if (ii[st] == 16 * 6 + findScroll(7) ) { //&& bitRead(sknow,7)==1){
      i1[st]--;
      if (i1[st] == 0) deleteItem(st);
      dungeon[x][y] = dungeon[x][y] % 10 + 30;
      /*
        } else if(ii[st]==16*6+stab[7] && bitRead(sknow,7)==0){
          bitWrite(sknow,stab[7],1);
          deleteItem(st);
          dungeon[x][y]=dungeon[x][y]%10+30;
      */
    } else if (thing[x][y] != 0) {
      //    msgc = "something here";
      mess(3);
    } else {
      byte t = freeSlot();
      if (t == TMAX) {
        //      msgc = "no slot";
        mess(4);
      } else {
        thing[x][y] = t + 1;
        id[t] = ii[st];
        t1[t] = i1[st];
        t2[t] = i2[st];
        t3[t] = i3[st];
        t4[t] = i4[st];
        deleteItem(st);
      }
    }
  } else {
    mess(12);
  }
}

void useItem(byte st) {
  byte kind = ii[st] / 16;
  byte vari = ii[st] % 16;
  if (kind == 2) {            //food
    i1[st]--;
    if (i1[st] == 0) {
      deleteItem(st);
    }
    eat(vari);
  } else if (kind == 3) {     //weapon
    wield(st);
  } else if (kind == 4) {     //armor
    wield(st);
  } else if (kind == 5) {     //potion
    bitWrite(pknow, vari, 1);
    i1[st]--;
    if (i1[st] == 0) {
      deleteItem(st);
    }
    drink(vari);
    itmToGitm(5, vari, 1);
    addBuf(gitm);
  } else if (kind == 6) {     //scroll
    bitWrite(sknow, vari, 1);
    i1[st]--;
    if (i1[st] == 0) {
      deleteItem(st);
    }
    readScroll(vari);
    if (stab[vari] != 4) {
      itmToGitm(6, vari, 1);
      addBuf(gitm);
    }
  } else if (kind == 7) {     //ring
    bitWrite(rknow, vari, 1);
    wield(st);
  } else if (kind == 8) {     //wand
    bitWrite(wknow, vari, 1);
    if (i2[st] > 0) {
      i2[st]--;
    } else {
      vari = 9;
    }
    zap(vari);
  }
}

byte randMonst(byte d) {
  char fm = d - 6;
  char to = d + 3;
  if (fm < 0) {
    fm = 0;
  } else if (fm > 21) {
    fm = 21;
  }
  if (to > 26) {
    to = 25;
  }
  return random(fm, to);
}

void wakeUp() {
  for (int i = 0; i < 16; i++) {
    if (ms[i] / 32 == 2) {
      if ((abs(mx[i] - hx) + abs(my[i] - hy)) <= 2) {
        if (random(10) < 4 / (hasRing(0) + 1)) {
          ms[i] = 32 + ms[i] % 32;
        }
      }
    }
  }
}

byte strToDmg(byte str) {
  byte result;
  if (str >= 1 && str <= 5) {
    result = str - 5;
  } else if (str >= 6 && str <= 14) {
    result = 1;
  } else if (str >= 15 && str <= 17) {
    result = 3;
  } else if (str == 18) {
    result = 4;
  } else if (str >= 19 && str <= 20) {
    result = 5;
  } else if (str == 21) {
    result = 6;
  } else if (str >= 22 && str <= 30) {
    result = 7;
  } else if (str >= 31) {
    result = 8;
  }
  return result;
}

void deleteItem(byte i) {
  ii[i] = 0;
  i1[i] = 0;
  i2[i] = 0;
  i3[i] = 0;
  i4[i] = 0;
  im--;
  sortItem();
}

void throwItem(byte i) {    //i=pack num 0 to 19
  char hdex = 0, hdmg = 0, dmg = 0;
  if (bitRead(i4[i], 4) == 0 || (ii[i] / 16 == 3 && ii[i] % 16 >= 4)) {
    if (bitRead(i4[i], 4) == 0 && bitRead(i4[i], 6) == 0) {
      byte dir = askDir();
      int dest = checkHit(dir, 20);
      //  Serial.println(hx);
      //  Serial.println(hy);
      //  Serial.println(dest / 256);       //mon id (0=wall)
      //  Serial.println((dest % 256) % 21); //x
      //  Serial.println((dest % 256) / 21); //y
      //  Serial.println(F("-------"));
      fi = ii[i];
      f1 = 1;
      f2 = i2[i];
      f3 = i3[i];
      f4 = i4[i];
      i1[i]--;
      if (i1[i] == 0) {
        deleteItem(i);
        //    im--;
        //    sortItem();
      }

      byte mon = dest / 256;
      char destx = (dest % 256) % 21;
      char desty = (dest % 256) / 21;

      if (mon == 0) {
        dropThrown(destx, desty, fi, f1, f2, f3, f4);
      } else {  // check hit
        if (fi == 3 * 16 + 5 && equip(3, 1) != 0 && ii[equip(3, 1) - 1] % 16 == 3) {
          hdex = ( 1 + i2[i]) * 4 / 3;
        } else if (fi >= 3 * 16 + 4 && bitRead(i4[i], 4) == 1) {
          hdex = ( 1 + i2[i]) * 4 / 3;
        } else {
          hdex = 1;
        }
        byte rr = random(100);
        byte prob = 40 + hdex * 3 + lv * 2;
        //    Serial.println(prob);
        if (rr < prob) {        //hit
          //      Serial.println(F("hit"));
          flashMonst(mon - 1);
          if (fi == 3 * 16 + 5 && equip(3, 1) != 0 && ii[equip(3, 1) - 1] % 16 == 3) {
            hdmg = ( 1 + i3[i]) * 4 / 3;
          } else if (fi >= 3 * 16 + 4 && bitRead(i4[i], 4) == 1) {
            hdmg = ( 1 + i3[i]) * 4 / 3;
          } else {
            hdmg = -1;
          }
          //      Serial.println((int)dmg);

          if (fi / 16 == 5) {
            hitPotion(fi % 16, mon);
          } else if (fi / 16 == 8 && random(4) != 0 ) {
            hitWand(fi % 16, mon);
          } else {
            dmg = (random(hdex, hdex * hdmg) * 2 + lv + 1) / 2;
            if (mh[mon - 1] <= dmg) {
              monst[destx][desty] = 0;
              ms[mon - 1] = 0;
              ex = ex + pgm_read_byte(mstat[mon - 1] + 4);
              if (pgm_read_byte(mstat[mon - 1] + 5) >= random(100)) {
                placeThingXY(destx, desty);
              }
            } else {
              mh[mon - 1] = mh[mon - 1] - dmg;
              if (ms[mon - 1] / 32 > 1) {
                ms[mon - 1] = 32 + ms[mon - 1] % 32;
              }
            }
          }
        } else {                //miss
          //      Serial.println(F("miss"));
          dropThrown(destx, desty, fi, f1, f2, f3, f4);
        }
      }
    } else {
      mess(9);
    }
  } else {
    mess(12);
  }
}


void dropThrown(byte x, byte y, byte fi, byte f1, char f2, char f3, byte f4) {
  char destd = findPlace(x, y);    //findPlace(thing)
  if (destd == 0) {
    //item disapear
  } else {    //drop Item
    byte t = freeSlot();
    thing[x + (destd - 1) % 3 - 1][y + (destd - 1) / 3 - 1] = t + 1;
    id[t] = fi;
    t1[t] = 1;
    t2[t] = f2;
    t3[t] = f3;
    t4[t] = f4;
  }
}

void hitPotion(byte vari, byte mon) { //mon=1 to 26 ID
  flashMonst(mon - 1);
  switch (ptab[vari]) {
    case 0:
    case 2:
    case 3:
    case 5:
      mh[mon - 1] = mh[mon - 1] + 10;
      break;
    case 4:
      mh[mon - 1] = mh[mon - 1] / 2;
      break;
    case 6:
      ms[mon - 1] = 2 * 32 + ms[mon - 1] % 32;
      break;
    case 10:
      bitWrite(m1[mon - 1], 5, 1);
      break;
    case 12:
      bitWrite(m1[mon - 1], 7, 1);
      break;
  }
}

void hitWand(byte vari, byte mon) {
  flashMonst(mon - 1);
  switch (wtab[vari]) {
    case 0:
      ms[mon-1]=0;
      monst[mx[mon-1]][my[mon-1]]=0;
      break;
    case 1:
      bitWrite(m1[mon - 1], 7, 0);
      break;
    case 2:
      bitWrite(m1[mon - 1], 5, 1);
      break;
    case 3:
      bitWrite(m1[mon - 1], 6, 1);
      break;
    case 4:
      ms[mon - 1] = ms[mon - 1] / 32 + random(26);
      break;
    case 5:
      bitWrite(m1[mon - 1], 7, 1);
      break;
    case 6:
      ms[mon - 1] = 32 * 4 + ms[mon - 1] % 32;
      break;
    case 7:
      mh[mon - 1] = mh[mon - 1] / 2;
      break;
    case 8:
      bitWrite(m1[mon - 1], 3, 0);
      break;
    case 9:
      break;
  }
}

byte askDir() {
  drawMap();
  drawHero();
  drawThing();
  drawMonst();
  //  msgc="dir?";
  mess(5);
  showMsg();
  arduboy.display();

  return inputWait();
}

