void title() {
  locate(7, 3);
  arduboy.print(F("Rogue"));
  if (arduboy.justPressed(A_BUTTON)) {
    gstate = 1;
  }
}

void gameover() {
  hp=hpm;
  hh=1200;
  locate(7, 3);
  arduboy.print(F("R.I.P."));
  if (arduboy.justPressed(A_BUTTON)) {
    gstate = 0;
  }
}

void winner() {
  locate(7, 0);
  arduboy.print(F("winner"));
  if (arduboy.justPressed(A_BUTTON)) {
    gstate = 0;
  }
}

void gameloop() {
  byte mm, r;

  if (arduboy.justPressed(LEFT_BUTTON)) {
    heroMove(1);
  }

  if (arduboy.justPressed(RIGHT_BUTTON)) {
    heroMove(3);
  }

  if (arduboy.justPressed(UP_BUTTON)) {
    heroMove(2);
  }

  if (arduboy.justPressed(DOWN_BUTTON)) {
    heroMove(4);
  }

  if (arduboy.justPressed(A_BUTTON)) {
    if (dungeon[hx][hy] >= 11 && dungeon[hx][hy] <= 16) {
      hmdet=0;
      hisee=0;
      if(ii[im-1]==144){
        dlv--;
        if(dlv==0){
          gstate=3;
        }
      } else {
        dlv++;
      }
      clearDungeon();
      makeDungeon4();
      placeMonst();
      placeThing();
    } else {
      ss = 1;
      clearBuf();
      search();
      wakeUp();
      tweatHero();
      moveMonst();
    }
  }

  if (arduboy.justPressed(B_BUTTON)) {
    ss = 0;
    clearBuf();
    inventry(0);
  }

  makeKnown();
  if(hblnd==0) drawMap();
  drawHero();
  if(hblnd==0) drawThing();
  if(hblnd==0) drawMonst();
  if (ss == 1) {
    showStatus();
  }
  showMsg();
}

void heroMove(byte dir) {
  if(hconf>0){
    dir=random(4)+1;
  }
  char dx = (dir - 2) * (dir % 2);
  char dy = (dir - 3) * ((dir - 1) % 2);
  byte mm, r;

  if(hslep>0){
    dx=0;
    dy=0;
  }
  ss = 0;
  if (monst[hx + dx][hy + dy] == 0) {
    if ((hy + dy) <= 7 && (hy + dy) >= 0 && (hx + dx) >= 0 && (hx + dx) <= 20
        && dungeon[hx+dx][hy+dy] >= 1 && dungeon[hx+dx][hy+dy] <= 38) {
      if(hheld==0){
        hx = hx + dx;
        hy = hy + dy;
      }
      clearBuf();
      checkThing(hx, hy);
    }
  } else {
    mm = monst[hx + dx][hy + dy];
    r = ms[mm - 1] % 32;
    clearBuf();
    hitMonst(mm, r, dx, dy);
  }
  wakeUp();
  tweatHero();
  if(hfast > 0) {
    if(ht%2==0){
      moveMonst();
    }
  } else {
    moveMonst();
  }
}

