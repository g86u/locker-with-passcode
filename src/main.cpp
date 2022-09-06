#include <Arduino.h>
#include "Adafruit_Keypad.h"
#include "Wire.h"
#include "Adafruit_LiquidCrystal.h"
#include <Servo.h> //all the libraries that you need in order for the program to work

#define LUNGIME_PAROLA 4
#define ROWS 4
#define COLS 4
#define NOTE_C5 523
#define NOTE_D5 587
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_G5 784
#define NOTE_A5 880
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_E7 2637
#define NOTE_A6 1760
#define NOTE_AS3 233
#define NOTE_FS7 2960
#define NOTE_G3 196
#define NOTE_FS3 185
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_C3 131
#define NOTE_CS3 139

char parola_corecta[LUNGIME_PAROLA] = {'1', '2', '3', 'A'}; // here you set the password you want for the locker
char parola_introdusa[LUNGIME_PAROLA] = {};                 // this is the array for the password that will be introduced (either wrong or right)

char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
byte rowPins[ROWS] = {9, 8, 7, 6};                   // ROWS with orange wire cables
byte colPins[COLS] = {5, 4, 3, 2};                   // COLS with green wire cables
const int led_red = 10, led_green = 11, buzzer = 13; // white wire cables for those

Adafruit_LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
Adafruit_Keypad customKeypad = Adafruit_Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
Servo myservo;

void setup()
{
  lcd.begin(16, 2);
  customKeypad.begin();
  myservo.attach(12);

  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

int pozitie = 0; // this keeps the track of the position on the display
int greseli = 0; // these keeps track of the mistakes, if there will be 3 mistakes then teh locker will be blocked for 30 seconds

void loop()
{
  customKeypad.tick();

  // ====== Citire caracter curent
  lcd.setCursor(pozitie, 0); // set the cursor on the display
  keypadEvent e = customKeypad.read();
  if (e.bit.KEY != 255) // test if something is introduced. If you pressed on teh keypad then it will convert the symbols in ascii
  {
    if (e.bit.EVENT == KEY_JUST_PRESSED)
    {
      lcd.print((char)e.bit.KEY);
      parola_introdusa[pozitie] = (char)e.bit.KEY;
      pozitie++;
    }
  }

  // ====== Validare parolă
  if (pozitie == LUNGIME_PAROLA) // it starts veryfing if the password introduce is right or wrong only when the position is equal to four
  {
    int i;
    for (i = 0; i < LUNGIME_PAROLA; i++)
    {
      if (parola_introdusa[i] != parola_corecta[i])
      {
        greseli++;
        break;
      }
    }
    if (greseli == 3) // verify  before the code below how many mistakes were made
    {
      lcd.clear();
      digitalWrite(led_red, HIGH);
      tone(13, NOTE_G2, 2000);
      tone(13, NOTE_CS3, 2000);
      tone(13, NOTE_C3, 2000);
      tone(13, NOTE_GS2, 2000);
      delay(30000);
      digitalWrite(led_red, LOW);
      greseli = 0; // don't forget to reset the mistakes  made
      return;
    }

    delay(250);

    bool parola_e_valida = i == LUNGIME_PAROLA;
    if (parola_e_valida) // if there were introduced four numbers/letters/symbols then  it means that the password introduced was right
    {
      lcd.clear();
      digitalWrite(led_green, HIGH); // and the green led will light up and the locker will unlock
      myservo.write(180);
      tone(13, NOTE_C5, 2000); // plus the tone heard will be higher
      tone(13, NOTE_D5, 2000);
      tone(13, NOTE_E5, 2000);
      tone(13, NOTE_F5, 2000);
      tone(13, NOTE_G5, 2000);
      tone(13, NOTE_A5, 2000);
      tone(13, NOTE_B5, 2000);
      tone(13, NOTE_C6, 2000);

      delay(10000);
      myservo.write(-180);
      greseli = 0;
    }
    else // otherwise the red led will light up and the tone will sound deeper
    {
      lcd.clear();
      tone(13, NOTE_AS3, 2000);
      tone(13, NOTE_FS7, 2000);
      tone(13, NOTE_G3, 2000);
      tone(13, NOTE_FS3, 2000);
      digitalWrite(led_red, HIGH);
      delay(3000);
    }

    lcd.clear();
    pozitie = 0;
    digitalWrite(led_green, LOW);
    digitalWrite(led_red, LOW);
  }
}