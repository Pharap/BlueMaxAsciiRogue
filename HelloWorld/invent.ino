byte inputWait() {
  byte result = 0;
  do {
    arduboy.pollButtons();
    if (arduboy.justPressed(LEFT_BUTTON)) result = 1;
    if (arduboy.justPressed(UP_BUTTON)) result = 2;
    if (arduboy.justPressed(RIGHT_BUTTON)) result = 3;
    if (arduboy.justPressed(DOWN_BUTTON)) result = 4;
    if (arduboy.justPressed(A_BUTTON)) result = 5;
    if (arduboy.justPressed(B_BUTTON)) result = 6;
  } while (result == 0);
  return result;
}

void drawInventry(byte st, byte mode) {
  byte ed;
  arduboy.clear();
  locate(0, 0);
  if(mode==0){
    arduboy.setTextBackground(WHITE);
    arduboy.setTextColor(BLACK);
    arduboy.print(F(" Inventory     "));
    arduboy.print( hh );
    arduboy.print(F("  "));
  } else {
    arduboy.print(F(" which?"));
  }
  locate(0, 1);
  arduboy.setTextBackground(BLACK);
  arduboy.setTextColor(WHITE);
  arduboy.print(F(">"));

  if (st + 7 > im) {
    ed = im;
  } else {
    ed = st + 7;
  }
  for (int i = st; i < ed; i++) {
    locate(1, i - st + 1);
    char buff;
    if(bitRead(i4[i],3)==1){
      buff='{';
    } else {
      buff = pgm_read_byte(tsym + ii[i] / 16 - 1);
    }
    arduboy.print(buff);
    arduboy.print(F(" "));
    byte kind = ii[i] % 16;
    switch (ii[i] / 16) {
      case 2:
        arduboy.print(i1[i]);
        arduboy.print(F(" "));
        itmToGitm(ii[i]/16,kind,0);
        arduboy.print(gitm);
        break;
      case 3:
        if(kind>=4){
          arduboy.print(i1[i]);
          arduboy.print(F(" "));
        }
        itmToGitm(ii[i]/16,kind,0);
        arduboy.print(gitm);
        if(bitRead(i4[i],5)==1){
          arduboy.print(F("["));
          arduboy.print((int)i2[i]);
          arduboy.print(F(","));
          arduboy.print((int)i3[i]);
          arduboy.print(F("]"));
        }
        if(bitRead(i4[i],6)==1){
          arduboy.print(F(" C"));
        }
        if(bitRead(i4[i],4)==1){
          arduboy.print(F(" E"));
        }
        break;
      case 4:
        itmToGitm(ii[i]/16,kind,0);
        arduboy.print(gitm);
        if(bitRead(i4[i],5)==1){
          arduboy.print(F("["));
          arduboy.print((int)i2[i]);
          arduboy.print(F("]"));
        }
        if(bitRead(i4[i],6)==1){
          arduboy.print(F(" C"));
        }
        if(bitRead(i4[i],4)==1){
          arduboy.print(F(" E"));
        }
        break;
      case 5:
        arduboy.print(i1[i]);
        arduboy.print(F(" "));
        if(bitRead(pknow,kind)==0){
          itmToGitm(ii[i]/16,kind,0);
        } else {
          itmToGitm(ii[i]/16,kind,1);
        }
        arduboy.print(gitm);
        break;
      case 6:
        arduboy.print(i1[i]);
        arduboy.print(F(" "));
        if(bitRead(sknow,kind)==0){
          itmToGitm(ii[i]/16,kind,0);
        } else {
          itmToGitm(ii[i]/16,kind,1);
        }
        arduboy.print(gitm);
        break;
      case 7:
        if(bitRead(rknow,kind)==0){
          itmToGitm(ii[i]/16,kind,0);
        } else {
          itmToGitm(ii[i]/16,kind,1);
        }
        arduboy.print(gitm);
        if(bitRead(i4[i],5)==1){
          if(i2[i] != 0){
            arduboy.print(F("["));
            arduboy.print((int)i2[i]);
            arduboy.print(F("]"));
          }
        }
        if(bitRead(i4[i],6)==1){
          arduboy.print(F(" C"));
        }
        if(bitRead(i4[i],4)==1){
          arduboy.print(F(" E"));
        }
        break;
      case 8:
        if(bitRead(wknow,kind)==0){
          itmToGitm(ii[i]/16,kind,0);
        } else {
          itmToGitm(ii[i]/16,kind,1);
        }
        arduboy.print(gitm);
        if(bitRead(i4[i],5)==1){
          arduboy.print(F("["));
          arduboy.print((int)i2[i]);
          arduboy.print(F("]"));
        }
        break;
      case 9:
        itmToGitm(ii[i]/16,kind,1);
        arduboy.print(gitm);
        break;
    }
  }
  arduboy.display();
}

byte inventry(byte mode) {
  byte st = 0;
  byte ex = 0;
/*
  for(int i=0; i<im; i++){
    Serial.print(ii[i]/16);
    Serial.print("\t");
    Serial.print(rtab[ii[i]%16]);
    Serial.print("\t");
    Serial.print(i1[i]);
    Serial.print("\t");
    Serial.print((int)i2[i]);
    Serial.print("\t");
    Serial.print((int)i3[i]);
    Serial.print("\t");
    Serial.print(i4[i],BIN);
    Serial.println("");
  }
  Serial.println(F("------"));
*/
  do {
    drawInventry(st, mode);
    byte a = inputWait();
    if (a == 2) {
      if (st > 0) st--;
    }
    if (a == 4) {
      if (st < im - 1) st++;
    }
    if (a == 5) {
      if(mode==0){
        ex = action(st);
      } else {
        ex=1;
      }
    }
    if (a == 6) {
      ex = 1;
    }
  } while (ex == 0);
  return st;
}

byte action(byte st) {
  byte curs = 0;
  arduboy.setTextBackground(WHITE);
  arduboy.setTextColor(BLACK);
  locate(1, 1);
  arduboy.print(F(" Action           "));
  arduboy.setTextBackground(BLACK);
  arduboy.setTextColor(WHITE);
  locate(1, 2);
  arduboy.print(F("  use          "));
  locate(1, 3);
  arduboy.print(F("  throw        "));
  locate(1, 4);
  arduboy.print(F("  drop         "));
  locate(1, 5);
  arduboy.print(F("               "));
//  arduboy.print(F("  save and quit"));
//  locate(1, 6);
//  arduboy.print(ii[st] / 16);
//  arduboy.print(F(" "));
//  arduboy.print(ii[st] % 16);
//  arduboy.print(F("   "));
  locate(1, curs + 2);
  arduboy.print(F("> "));

  arduboy.display();
  byte ex = 0;
  do {
    byte a = inputWait();
    switch (a) {
      case 2:
        if (curs > 0) {
          locate(1, curs + 2);
          arduboy.print(F("  "));
          curs--;
          locate(1, curs + 2);
          arduboy.print(F("> "));
          arduboy.display();
        }
        break;
      case 4:
        if (curs < 2) {
          locate(1, curs + 2);
          arduboy.print(F("  "));
          curs++;
          locate(1, curs + 2);
          arduboy.print(F("> "));
          arduboy.display();
        }
        break;
      case 5:
        if(curs==0){
          useItem(st);
          sortItem();
          ex=1;
        } else if(curs==1){
          throwItem(st);
          sortItem();
          ex=1;
        } else if(curs==2){
          dropItem(hx, hy, st);
          sortItem();
          ex=1;
        } else if(curs==3){
          saveStatus();
          gstate=2;
          ex=1;
        }
        break;
      case 6:
        ex = 1;
        break;
    }
  } while (ex == 0);
  return 1;
}

void showStatus() {
  byte h = 0;
  if (hx < 10) {
    h = 11;
  }
  if(hblnd==0) drawMap();
  drawHero();
  if(hblnd==0) drawThing();
  if(hblnd==0) drawMonst();

  arduboy.setTextBackground(WHITE);
  arduboy.setTextColor(BLACK);
  locate(h, 0);
  arduboy.print(F(" Status   "));
  arduboy.setTextBackground(BLACK);
  arduboy.setTextColor(WHITE);
  for (int i = 1; i < 8; i++) {
    locate(h, i);
    arduboy.print(F("          "));
  }
  locate(h, 1);
  arduboy.print(F("Lv:"));
  arduboy.print(dlv);
  locate(h, 2);
  arduboy.print(F("Au:"));
  arduboy.print(au);
  locate(h, 3);
  arduboy.print(F("Hp:"));
  arduboy.print(hp);
  arduboy.print(F("/"));
  arduboy.print(hpm);
  locate(h, 4);
  arduboy.print(F("St:"));
  arduboy.print(st);
  arduboy.print(F("/"));
  arduboy.print(stm);
  locate(h, 5);
  arduboy.print(F("AC:"));
  byte a=equip(4,1);
  byte ac=0;
  if(a==0){
    ac=0;
  } else {
    ac=pgm_read_byte(astat + ii[a-1] % 16 ) + i2[a-1];
  }
  arduboy.print(ac);
  locate(h, 6);
  arduboy.print(F("Ex:"));
  arduboy.print(lv);
  arduboy.print(F("/"));
  locate(h + 3, 7);
  arduboy.print(ex);
}

void search() {
  for (int i = hx - 1; i <= hx + 1; i++) {
    for (int j = hy - 1; j <= hy + 1; j++) {
      if (dungeon[i][j] >= 61 && dungeon[i][j] <= 66) {
        dungeon[i][j] = dungeon[i][j] - 40;
      } else if (dungeon[i][j] == 68) {
        dungeon[i][j] = dungeon[i][j] - 60;
      } else if (dungeon[i][j] >= 71 && dungeon[i][j] <= 76) {
        dungeon[i][j] = dungeon[i][j] - 50;
      }
    }
  }
}

