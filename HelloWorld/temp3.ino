void box(byte x1, byte y1, byte x2, byte y2, byte kind){
  for(int x=x1; x<x2+1; x++){
    for(int y=y1; y<y2+1; y++){
      dungeon[x][y]=kind;
    }
  }
}

void makeRoom(byte i){
  for(int x=roomSX[i]-1; x<=roomEX[i]+1; x++){
    if(dungeon[x][roomSY[i]-1]==8){
      dungeon[x][roomSY[i]-1]=21+i+random(2)*40;   //'+'
    } else {
      dungeon[x][roomSY[i]-1]=41+i;   //'-'
    }
    if(dungeon[x][roomEY[i]+1]==8){
      dungeon[x][roomEY[i]+1]=21+i+random(2)*40;   //'+'
    } else {
      dungeon[x][roomEY[i]+1]=41+i;   //'-'
    }
  }
  for(int y=roomSY[i]; y<=roomEY[i]; y++){
    if(dungeon[roomSX[i]-1][y]==8){
      dungeon[roomSX[i]-1][y]=21+i+random(2)*50;
    } else {
      dungeon[roomSX[i]-1][y]=51+i;
    }
    if(dungeon[roomEX[i]+1][y]==8){
      dungeon[roomEX[i]+1][y]=21+i+random(2)*50;
    } else {
      dungeon[roomEX[i]+1][y]=51+i;
    }
  }
  box(roomSX[i],roomSY[i],roomEX[i],roomEY[i],i+1);
}


void makeDungeon4() {
  char areaSX[4] = {}, areaSY[4] = {}, areaEX[4] = {}, areaEY[4] = {};
  char root = 0;
  int pass[4] = {1, 1, 1, 1};
  int passstat = 0;

  for(int i=0; i<4; i++){
    hasRoom[i]=0;
  }
//縦に３分割する  
  int r=7+random(7);
//横に２分割する
  int r3 = random(2) + 3;
  areaSX[0] = 0; areaSY[0] = 0; areaEX[0] = r - 1; areaEY[0] = r3; if (r3 >= 3) hasRoom[0] = 1;
  areaSX[1] = 0; areaSY[1] = r3 + 1; areaEX[1] = r - 1; areaEY[1] = 7; if ((7 - r3) >= 4) hasRoom[1] = 1;
  if (r3 == 3) { pass[0] = 0; passstat=passstat + 1; }
  root = r;
  int r5 = random(2) + 3;
  areaSX[2] = r + 1; areaSY[2] = 0; areaEX[2] = 20; areaEY[2] = r5; if (r5 >= 3) hasRoom[2] = 1;
  areaSX[3] = r + 1; areaSY[3] = r5 + 1; areaEX[3] = 20; areaEY[3] = 7; if ((7 - r5) >= 4) hasRoom[3] = 1;
  if (r5 == 3) { pass[3] = 0; passstat=passstat+2; }
//部屋の大きさを決める
  for (int i = 0; i <= 3; i++) {
    if (hasRoom[i] == 1) {
//      int roomX = random(areaEX[i] - areaSX[i] - 2) + 2; // 2<= roomX <= areaEX-areaSX+1-2
//      int roomY = random(areaEY[i] - areaSY[i] - 2) + 2;
      roomSX[i] = areaSX[i]  + 1+random(3);
      roomSY[i] = areaSY[i]  + 1;
      roomEX[i] = areaEX[i]  - 1-random(3);
      roomEY[i] = areaEY[i]  - 1;
    }
  }
  if(passstat==0 && random(2)==0){
    pass[random(4)]=0;
  }
//回廊  
  box(r/2  ,1,r+1+(20-r)/2  ,6,8);
//  box(r/2+1,2,r+1+(20-r)/2-1,5,0);

  
  if(pass[0]==0) box(r/2,2,r+(20-r)/2,5,0);
  if(pass[1]==0) box(r/2+1,1,r+(20-r)/2,5,0);
  if(pass[2]==0) box(r/2,2,r+(20-r)/2-1,6,0);
  if(pass[3]==0) box(r/2+1,2,r+1+(20-r)/2,5,0);
  box(r/2+1,2,r+1+(20-r)/2-1,5,0);

  for(int i=0; i<=3; i++){
    if (hasRoom[i] == 1) {
      makeRoom(i);
    }
  }

//４部屋の場合，縦につなぐ
  if(passstat==3) box(r,1,r,6,8);
//隠された通路
  for(int i=0; i<21; i++){
    for(int j=0; j<8; j++){
      if(dungeon[i][j]==8 && random(5)==0){
        dungeon[i][j]=68;
      }
    }
  }
  
//階段をつくる
  int s=random(RMAX)*2;
  if(hasRoom[s]==0) s++;
  dungeon[roomSX[s]+random(roomEX[s]-roomSX[s]+1)][roomSY[s]+random(roomEY[s]-roomSY[s]+1)] =11+s;
//暗い部屋をつくる
  for(int i=0; i<4; i++){
    if(random(5)==0){
      isDark[i]=1;
    } else {
      isDark[i]=0;
    }
  }

  clearKnown();
//ヒーローを置く
  teleportHero();
//  allKnown();
/*
  int h=random(3)*2;
  if(hasRoom[h]==0) h++;
  hx=roomSX[h]+random(roomEX[h]-roomSX[h]+1);
  hy=roomSY[h]+random(roomEY[h]-roomSY[h]+1);
*/
}
/*
void teleportHero(){
  int h=random(3)*2;
  if(hasRoom[h]==0) h++;
  hx=roomSX[h]+random(roomEX[h]-roomSX[h]+1);
  hy=roomSY[h]+random(roomEY[h]-roomSY[h]+1);
}
*/
