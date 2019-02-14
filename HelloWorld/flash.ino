void flashHero(){
  if(hblnd==0) {
    drawMap();
    drawThing();
    drawMonst();
  }
  arduboy.setTextBackground(WHITE);
  arduboy.setTextColor(BLACK);
  locate(hx, hy);
  arduboy.print(F("@"));
  arduboy.display();
  delay(100);
  arduboy.setTextBackground(BLACK);
  arduboy.setTextColor(WHITE);
/*  drawMap();
  drawThing();
  drawMonst();
  locate(hx, hy);
  arduboy.print(F("@"));
  arduboy.display();
  delay(1000);
*/
}

void flashMonst(byte num){
  if(hblnd==0) {
    drawMap();
    drawThing();
    drawMonst();
  }
  arduboy.setTextBackground(WHITE);
  arduboy.setTextColor(BLACK);
  locate(mx[num], my[num]);
  arduboy.print((char)pgm_read_byte(mname+(ms[num] % 32)));
  arduboy.display();
  delay(100);
  arduboy.setTextBackground(BLACK);
  arduboy.setTextColor(WHITE);
}

