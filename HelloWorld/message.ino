void addBuf(char aray[]){
  byte ex=0, i=0, i1=0;
  do{
    if(gbuf[i]=='\0'){
      ex=1;
    } else {
      i++;
    }
  }while(ex==0);
  ex=0;
  i1=i;
  do{
    if(aray[i-i1]=='\0' || i >= 22){
      gbuf[21]='\0';
      ex=1;
    } else {
      gbuf[i]=aray[i-i1];
      i++;
    }
  }while(ex==0);
}

void mesToGmes(byte id){
  for(int i=0; i<15; i++){
//    gmes[i]=pgm_read_byte(mes[id]+i);
    gbuf[i]=pgm_read_byte(mes[id]+i);
  }
}

void itmToGitm(byte type, byte r, byte k){
  switch(type){
    case 1:
      for(int i=0; i<8; i++){
        gitm[i]=pgm_read_byte(gold[r]+i);
      }
      break;
    case 2:
      for(int i=0; i<8; i++){
        gitm[i]=pgm_read_byte(food[r]+i);
      }
      break;
    case 3:
      for(int i=0; i<8; i++){
        gitm[i]=pgm_read_byte(weapon[r]+i);
      }
      break;
    case 4:
      for(int i=0; i<8; i++){
        gitm[i]=pgm_read_byte(armor[r]+i);
      }
      break;
    case 5:
      if(k==0){
        for(int i=0; i<8; i++){
          gitm[i]=pgm_read_byte(color[r]+i);
        }
      } else {
        for(int i=0; i<8; i++){
          gitm[i]=pgm_read_byte(potion[ptab[r]]+i);
        }
      }
      break;
    case 6:
      if(k==0){
        for(int i=0; i<8; i++){
          gitm[i]=pgm_read_byte(label[r]+i);
        }
      } else {
        for(int i=0; i<8; i++){
          gitm[i]=pgm_read_byte(scroll[stab[r]]+i);
        }
      }
      break;
    case 7:
      if(k==0){
        for(int i=0; i<8; i++){
          gitm[i]=pgm_read_byte(stone[r]+i);
        }
      } else {
        for(int i=0; i<8; i++){
          gitm[i]=pgm_read_byte(ring[rtab[r]]+i);
        }
      }
      break;
    case 8:
      if(k==0){
        for(int i=0; i<8; i++){
          gitm[i]=pgm_read_byte(metal[r]+i);
        }
      } else {
        for(int i=0; i<8; i++){
          gitm[i]=pgm_read_byte(wand[wtab[r]]+i);
        }
      }
      break;
    case 9:
      for(int i=0; i<8; i++){
        gitm[i]=pgm_read_byte(amulet[r]+i);
      }
      break;
  }
}

void clearBuf(){
  for(int i=0; i<22; i++){
    gbuf[i]=0;
  }
}

void mess(byte i){
  clearBuf();
  mesToGmes(i);
//  addBuf(gmes);
}

