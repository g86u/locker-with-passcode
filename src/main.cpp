#include <Arduino.h>
#include "Adafruit_Keypad.h"
#include "Wire.h"
#include "Adafruit_LiquidCrystal.h"
#include <Servo.h>

#define LUNGIME_PAROLA 4 // this is the lenght of teh password
#define ROWS 4
#define COLS 4
#define NOTE_C5 523 // here it starts the notes for teh sounds
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

char parola_corecta[LUNGIME_PAROLA] = {'1', '2', '3', 'A'}; // here you set up your password
char parola_introdusa[LUNGIME_PAROLA] = {};                 // here is the array which will contain the password you will introduce from the keypad

char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
byte rowPins[ROWS] = {9, 8, 7, 6};                   // the pins for the ROWS
byte colPins[COLS] = {5, 4, 3, 2};                   // the pins for the COLOUMNS
const int led_red = 10, led_green = 11, buzzer = 13; // the pins for the green led, red led and the buzzer

Adafruit_LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
Adafruit_Keypad customKeypad = Adafruit_Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
Servo myservo; // the object myservo

void setup()
{
  lcd.begin(16, 2);
  customKeypad.begin();
  myservo.attach(12);

  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

int pozitie = 0; // this keeps track of every character introduced from teh keyboard
int greseli = 0; // this keeps track of the mistakes made

void loop()
{
  customKeypad.tick();

  // ====== Reading the current character
  lcd.setCursor(pozitie, 0); // set up the coursor position on the LCD display
  keypadEvent e = customKeypad.read();
  if (e.bit.KEY != 255) // it tests if there is aomething introduced from the keypad
  {
    if (e.bit.EVENT == KEY_JUST_PRESSED)
    {
      lcd.print((char)e.bit.KEY);
      parola_introdusa[pozitie] = (char)e.bit.KEY;
      pozitie++;
    }
  }

  // ====== Password validation
  if (pozitie == LUNGIME_PAROLA) // it starts immediately verifying after 4 characters if the password introduced is correct
  {
    int i; // this number keeps track of the differences between the correct password and the introduced one (if it exist)
    for (i = 0; i < LUNGIME_PAROLA; i++)
    {
      if (parola_introdusa[i] != parola_corecta[i])
      {
        greseli++; // if the password introduced is incorrect this  will add up
        break;
      }
    }
    if (greseli == 3) // put this before the code below so it can verify if there were made 3 mistakes
    {
      lcd.clear();
      digitalWrite(led_red, HIGH);
      tone(13, NOTE_G2, 2000);
      tone(13, NOTE_CS3, 2000);
      tone(13, NOTE_C3, 2000);
      tone(13, NOTE_GS2, 2000);
      delay(30000);
      digitalWrite(led_red, LOW);
      greseli = 0; // you have to reset the mistakes here
      return;
    }

    delay(250);

    bool parola_e_valida = i == LUNGIME_PAROLA;
    if (parola_e_valida) // if the number i reached to 4 it means that the password introduced is correct
    {
      lcd.clear();
      digitalWrite(led_green, HIGH); // the green eld will ligh up, the buzzer will make a sound and the "locker" will stay open for 10 seconds
      myservo.write(180);
      tone(13, NOTE_C5, 2000);
      tone(13, NOTE_D5, 2000);
      tone(13, NOTE_E5, 2000);
      tone(13, NOTE_F5, 2000);
      tone(13, NOTE_G5, 2000);
      tone(13, NOTE_A5, 2000);
      tone(13, NOTE_B5, 2000);
      tone(13, NOTE_C6, 2000);

      delay(10000);
      myservo.write(-180);
      greseli = 0; // also, you have to reset the mistakes again
    }
    else //  if teh number "i" haven't reached 4 then it means that the password is incorrect
    {
      lcd.clear();
      tone(13, NOTE_AS3, 2000);
      tone(13, NOTE_FS7, 2000);
      tone(13, NOTE_G3, 2000);
      tone(13, NOTE_FS3, 2000);
      digitalWrite(led_red, HIGH);
      delay(3000);
    }

    lcd.clear(); // you have to clean the lcd dispaly
    pozitie = 0; // you have to reset the position in order to introduce another password form the keyboard
    digitalWrite(led_green, LOW);
    digitalWrite(led_red, LOW);
  }
}