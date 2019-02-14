void hitMonst(byte mm, byte r, char dx, char dy) { //mm=monst[x][y](1 to 16) r=kind(0 to 25
  byte rr = random(100);
  byte dmg = 0;
  byte w=equip(3,1);
  byte hdex=0, hdmg=0;
  if(w != 0){
    hdex = pgm_read_byte(wstat[ii[w-1] % 16]) + i2[w-1];
    hdmg = pgm_read_byte(wstat[ii[w-1] % 16 + 1]) + i3[w-1];
  }
  byte prob = 40 + hdex * 3 + lv * 2;
//  Serial.println(hdex);
//  Serial.println(hdmg);

  if (rr < prob) {
    // msgc="you hit.";
//    clearBuf();
//    mesToGmes(0);
//    addBuf(gmes);
//    monToGmon(r);
//    addBuf(gmon);
    flashMonst(mm-1);
    dmg = (random(hdex, hdex * hdmg) * 2 + strToDmg(st+rstr)*2 + rdex + lv + 1) / 2;
    if (mh[mm - 1] <= dmg) {
      monst[hx + dx][hy + dy] = 0;
      ms[mm - 1] = 0;
      ex = ex + pgm_read_byte(mstat[r] + 4);
      if(r==15){
        hheld=0;
      }
      if(pgm_read_byte(mstat[r] + 5) >= random(100)){
        placeThingXY(hx+dx, hy+dy);
      }
    } else {
      mh[mm - 1] = mh[mm - 1] - dmg;
      if(ms[mm-1]/32 > 1){
        ms[mm-1]=32+ms[mm-1]%32;
      }
//      if(bitRead(m1[mm-1],3)==1){
//        specialAttack(ms[mm-1]%32);
//      }
    }
  } else {
//    clearBuf();
//    mesToGmes(1);
//    addBuf(gmes);
//    monToGmon(r);
//    addBuf(gmon);
  }
}

void hitHero(byte i, byte r) { //i=kind(0 to 25 r=ID(0 to 16)
  byte prob = pgm_read_byte(mstat[i] + 3) - lv * 2 - rdex*2;
  byte rr = random(100);
  byte dmg = 0;
  byte a=equip(4,1);
  byte ac=0;
  if(a==0){
    ac=0;
  } else {
    ac=pgm_read_byte(astat + ii[a-1] % 16 ) + i2[a-1];
  }

  if (rr < prob) {
    //    msgc="mon hit.";
    dmg = (random(pgm_read_byte(mstat[i] + 1), pgm_read_byte(mstat[i] + 2)) * (100 - ac * 3)) / 100;
    if (hp <= dmg) {
      gstate = 2;
    } else {
      flashHero();
      hp = hp - dmg;
      if(bitRead(m1[r],3)==1){
        specialAttack( i );
      }
    }
  } else {
    //    msgc="mon miss.";
  }
}

void specialAttack(byte mon){   //mon=0 to 25 mon vari
  
  byte eq, ac, prob;
  switch(mon){
    case 5:     //IceMon
      if(random(5)==0){
        flashHero();
        mess(13);
        hslep=random(5)+4;
        if(random(20)==0){
          hp=0;
        }
      }
      break;
    case 6:     //R.snake    
      if(st>3 || hasRing(5)==0){
        if(random(5)==0){
          flashHero();
          mess(14);
          st--;
        }
      }
      break;
    case 9:     //Leprchaun
      if(random(10) != 0){
        flashHero();
        mess(15);
        au=au-random(50);
      }
      break;
    case 12:    //Aquator
      eq=equip(4,1);
      if( equip(4,1) != 0 && bitRead(i4[eq-1],3)==0){
        if(hasRing(9)==0) {
          flashHero();
          mess(16);
          i2[eq-1]--;
        }
      }
      break;
    case 13:    //Nymph
      if(random(2)==0){
        byte t=random(20);
        if(bitRead(i4[t],4)==0){
          flashHero();
          mess(15);
          deleteItem(t);
        }
      }
      break;
    case 15:    //Flytrap
      if(hlevi==0){
        flashHero();
        mess(17);
        hheld=1;
      }
      break;
    case 17:    //Wraith
      if(lv>5 && random(5)==0){
        flashHero();
        mess(20);
        nl=nl/2;
        ex=nl-1;
        lv--;
        hpm=hpm-3-random(7);
        if(hp>hpm) hp=hpm;
      }
      break;
    case 22:    //Vampire
      if(random(10)<4){
        flashHero();
        mess(21);
        byte r=random(3);
        if(r%2==0){
          if(hasRing(5)==0 || st>5){
            st--;
          }
        }
        if(r>0){
          if(hp>9){
            hp--;
            hpm--;
          }
        }
      }
      break;
  }
}

