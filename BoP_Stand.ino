#include "jesseoled.h"
#include "bop_logo.h"


#define DNBUTTON 1
#define SETBUTTON 3
#define UPBUTTON  4
int toggle = 1;
int ALT = 0;
int TAS = 0;
int menu = 0;
int KEAS = 0;
float Mach = 0;
char buffA[3];
char buffT[4];
char buffM[4];
char buffK[4];


//Math Stuff

const float pArray[24] = {1, 0.9854, 0.971, 0.9566, 0.9424, 0.9283, 0.9143, 0.9004, 0.8866, 0.8729, 0.8593, 0.7932, 0.7299, 0.6694, 0.6117, 0.5567, 0.5450, 0.4962, 0.4400, 0.3902, 0.3460, 0.3068, 0.2721, 0.2413};

void getKEAS()
{
  int a = (ALT - 2) / 5; // Round down to nearest thousand feet
  float p = pArray[a]; // Get multiplier for KEAS
  float e = (TAS * p); // Get float KEAS
  KEAS = ((e + 2) / 5) * 5; // Round to nearest 5 Knots
}

void getMACH()
{
  if (ALT >= 180)
  {
    Mach = (TAS / 573.88);
  }
  else
  { float m = (661 - (ALT * 0.4857));
    Mach = (TAS / m);
  }
}

// Menu function 1 is ALT, 2 is SPD, 0 is Menu Off
void menuUp()
{ if (digitalRead(SETBUTTON) == LOW) { // SET button pressed
    menu++;
    toggle = 1;
    if (menu > 2) menu = 0;
  }
  else if (digitalRead(UPBUTTON) == LOW) { // UP button pressed
    if (menu == 1) {
      ALT++; // increase ALT
      toggle = 1;
    }
    if (menu == 2) {
      TAS = (TAS + 5); // add 5 kts
      toggle = 1;
    }
  }
  else if (digitalRead(DNBUTTON) == LOW) { // DN button pressed
    if (menu == 1) {
      ALT--; // decrease ALT
      toggle = 1;
    }
    if (menu == 2) {
      TAS = (TAS - 5); // subtract 5 kts
      toggle = 1;
    }
  }
  else {
    toggle = 0;
  }
}

//Display stuff

void dispALT() {
  dtostrf(ALT, 3, 0, buffA);
  oled.drawImage(18, 0, 66, 3, alt_img);
  oled.printStringL(68, 0, buffA);
  if (menu == 1)
  {
    oled.printCharL(0, 0, "/");
  }
  else {
    oled.printCharL(0, 0, ".");
  }
}

void dispTAS() {
  dtostrf(TAS, 4, 0, buffT);
  oled.drawImage(18, 3, 66, 6, spd_img);
  oled.printStringL(68, 3, buffT);
  if (menu == 2)
  {
    oled.printCharL(0, 3, "/");
  }
  else {
    oled.printCharL(0, 3, ".");
  }
}

void dispKEAS() {
  getKEAS();
  dtostrf(KEAS, 4, 0, buffK);
  oled.printStringS(0, 6, "!/#$%&'");
  oled.printStringS(44, 6, buffK);
}

void dispMACH() {
  getMACH();
  dtostrf(Mach, 4, 2, buffM);
  oled.printStringS(0, 7, ":;<=>?@");
  oled.printStringS(44, 7, buffM);
  if (Mach <= 0.8) {
    oled.printStringS(72, 7, "ABCD");
  }
  if (0.8 <= Mach < 1) {
    oled.printStringS(72, 7, "+,-");
  }
  if (1 <= Mach < 1.2) {
    oled.printStringS(72, 7, "()*");
  }
  if (Mach >= 1.2) {
    oled.printStringS(72, 7, "    ");
  }
}

void displayUp() {
  dispALT();
  dispTAS();
  dispKEAS();
  dispMACH();
}


///////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  pinMode(DNBUTTON, INPUT_PULLUP);
  pinMode(SETBUTTON, INPUT_PULLUP);
  pinMode(UPBUTTON, INPUT_PULLUP);
  oled.init(0x3c);
  oled.clear(); // clear screen
  oled.drawImage(0, 0, 128, 8, BoP_Logo);
  delay(4000);
  displayUp();

}


void loop() {
  menuUp();
  if (toggle == 1) {
    displayUp();
  }
}



/*
  UI related
*/



