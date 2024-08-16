#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DS3231.h>

const int BUTTONENTER = 6;
const int BUTTONLEFT = 5;
const int BUTTONCANCEL = 7;
const int BUTTONRIGHT = 8;

const int box1address = 100;
const int box2address = 200;
const int box3address = 300;
const int box4address = 400;
const int box5address = 500;
const int box6address = 600;
const int box7address = 700;
const int box8address = 800;

DS3231 jam;
RTCDateTime dt; //ini adalah objek dengan tipe data RTCDataTime. Objek ini terdapat di dalamnya variabel2 public berupa
LiquidCrystal_I2C lcd(0x27,16,2);

class OBAT{
  public:
    int jamjam[6];
    int box;
    OBAT();
    OBAT(int boxholder){
      jamjam[0] = 25;
      jamjam[1] = 25;
      jamjam[2] = 25;
      jamjam[3] = 25;
      jamjam[4] = 25;
      jamjam[5] = 25;
      box = boxholder;
  }
  }; //INI OBJEK OBAT.


int menuval = 1;
int boxval = 1;
bool menuenter = false;

OBAT box1();
OBAT box2();
OBAT box3();
OBAT box4();
OBAT box5();
OBAT box6();
OBAT box7();
OBAT box8();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //
  jam.begin(); //inisialisasi jam. p.s. ini tuh dokumentasinya buruk sekali tapi paling mudah dipakai
  jam.setDateTime(__DATE__, __TIME__);
  //jam.setDateTime(); masukkan unix timespan ditambah 7 jam karena Bandung GMT+7. Cukup dilakukan sekali. DS3231 akan terus 
  /*akan terus menghitung waktu sampai baterainya habis*/
  lcd.begin();
  lcd.backlight();
  pinMode(BUTTONENTER, INPUT_PULLUP);
  pinMode(BUTTONCANCEL, INPUT_PULLUP);
  pinMode(BUTTONRIGHT, INPUT_PULLUP);
  pinMode(BUTTONLEFT, INPUT_PULLUP);
  
}

void loop() {
  // put your main code here, to run repeatedly:


  dt = jam.getDateTime();

  if(menuenter == true){
    switch(menuval){
      case 1:
        String hour = String(dt.hour);
        String min = String(dt.minute);
        String sec = String(dt.second);
        lcd.setCursor(0,0);
        lcd.print("Jam");
        lcd.setCursor(0,1);
        lcd.print(hour);
        lcd.print(":");
        lcd.print(min);
        lcd.print(":");
        lcd.print(sec);
      case 2:
        tambahobat();
      case 3:
        hapusobat();   
    }
  }
  else{  
    if (digitalRead(BUTTONRIGHT) == LOW) {
      menuval = menuval + 1;
      menu();
    }
    if(digitalRead(BUTTONLEFT) == LOW){
      menuval = menuval - 1;
      menu();
    }
    if(digitalRead(BUTTONENTER) == LOW){
      menuenter = true;
    }
    if (digitalRead(BUTTONCANCEL) == LOW){
      menuenter = false;
      menu();
    }
  }
}


void menu(){
  switch(menuval){
    case 0:
      menuval = 1;
      break;
    case 1:
      lcd.clear();
      lcd.print(">Jam");
      lcd.setCursor(0,1);
      lcd.print("Tambah Obat");
      break;
    case 2:
      lcd.clear();
      lcd.print("Jam");
      lcd.setCursor(0,1);
      lcd.print(">Tambah Obat");
      break;
    case 3:
      lcd.clear();
      lcd.print("Tambah Obat");
      lcd.setCursor(0,1);
      lcd.print(">Hapus Obat");
      break;
    case 4:
      menuval = 4;
      break;
  }
}

void tambahobat(){
  int dailyval = 1; //menyimpan jumlah obat per hari.
  lcd.clear();
  lcd.print("BOX:");
  lcd.setCursor(5,0);
  boxval = valuechange(1, 8);
  lcd.setCursor(0,1);
  lcd.print("kali:");
  dailyval = valuechange(1, 6);
  int boxrealaddress;
  float valEmpty;
  switch(boxval){
    case 1:
      boxrealaddress = box1address;
    case 2:
      boxrealaddress = box1address;
    case 3:
      boxrealaddress = box3address;
    case 4:
      boxrealaddress = box4address;
    case 5:
      boxrealaddress = box5address;
    case 6:
      boxrealaddress = box1address;
    case 7:
      boxrealaddress = box7address;
    case 8:
      boxrealaddress = box8address;
  }
  if (EEPROM.get(boxrealaddress, valEmpty) != 0XFF){
      lcd.clear();
      lcd.print("HAPUS DULU");
      lcd.setCursor(0,1);
      lcd.print("PRESS CNCL");        
      if(digitalRead(BUTTONCANCEL) == LOW){
        menuenter = false;       
        menuval = 1;
      }
    }
  else{

  }

}

void hapusobat(){
  for(int i; EEPROM.length();i++){
    EEPROM.write(i, 0XFF);
  }
}

int valuechange(int minval, int maxval){
  int x;
  while(true){
    if ((x > maxval) or (x < minval)){
        x = 1;
      }
    lcd.print(String(x));
    if (digitalRead(BUTTONRIGHT) == LOW){
      x = x + 1;
    }
    if (digitalRead(BUTTONLEFT) == LOW){
      x = x - 1;
    }
    if (digitalRead(BUTTONENTER) == LOW){
      break;
    }  
  return x;
}
}