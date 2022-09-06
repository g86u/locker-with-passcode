#include <Arduino.h>
#include "Adafruit_Keypad.h"
#include "Wire.h"
#include "Adafruit_LiquidCrystal.h"
#include <Servo.h>

#define LUNGIME_PAROLA 4
#define ROWS 4
#define COLS 4
#define NOTE_C5 523 // de aici incep notele necesare pentru creearea sunetelor
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

char parola_corecta[LUNGIME_PAROLA] = {'1', '2', '3', 'A'}; // aici setezi parola dorita
char parola_introdusa[LUNGIME_PAROLA] = {};                 // acesta este tabloul unidimensional unde va fi introdusa parola
// data de la tastatura si verificata

char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
const int led_red = 10, led_green = 11, buzzer = 13;

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

int pozitie = 0; // memoreazz pozitia caracterului introdus
int greseli = 0; // memoreaza parolele introduse gresit

void loop()
{
  customKeypad.tick();

  // ====== Citire caracter curent
  lcd.setCursor(pozitie, 0); // seteaza pozitia cursorului pe ecranul lcd-ului
  keypadEvent e = customKeypad.read();
  if (e.bit.KEY != 255) // testeaza daca ceva este introdus. Daca un caracter este apasat, acesta va fi convertit in ASCII
  {
    if (e.bit.EVENT == KEY_JUST_PRESSED)
    {
      lcd.print((char)e.bit.KEY);
      parola_introdusa[pozitie] = (char)e.bit.KEY;
      pozitie++;
    }
  }

  // ====== Validare parolă
  if (pozitie == LUNGIME_PAROLA) // incepe a verifica parola introdusa imediat dupa ce au fost introduse 4 caractere
  {
    int i; // acest numar ajuta la verificare greselilor din parola introdusa (daca exista)
    for (i = 0; i < LUNGIME_PAROLA; i++)
    {
      if (parola_introdusa[i] != parola_corecta[i])
      {
        greseli++; // daca e gresita parola introdusa, greselile se aduna
        break;
      }
    }
    if (greseli == 3) // verifica inainte de codul de dedesubt cate greseli sunt. Daca sunt 3 greseli "seiful" se blocheaza pentru 30 de secunde
    {
      lcd.clear();
      digitalWrite(led_red, HIGH);
      tone(13, NOTE_G2, 2000);
      tone(13, NOTE_CS3, 2000);
      tone(13, NOTE_C3, 2000);
      tone(13, NOTE_GS2, 2000);
      delay(30000);
      digitalWrite(led_red, LOW);
      greseli = 0; // greselile trebuiesc resetate imediat dupa
      return;
    }

    delay(250);

    bool parola_e_valida = i == LUNGIME_PAROLA;
    if (parola_e_valida) // daca numarul i a ajuns la 4 inseamna ca parola e valida
    {
      lcd.clear();
      digitalWrite(led_green, HIGH); // iar led-ul verde se va aprinde si servo motorul va deschide "seiful"
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
      greseli = 0; // greselile trebuiesc resetate si aici
    }
    else // daca numarul i nu a ajuns la 4, inseamna ca parola a fost introdusa gresit si va fi executat codul de mai jos
    {
      lcd.clear();
      tone(13, NOTE_AS3, 2000);
      tone(13, NOTE_FS7, 2000);
      tone(13, NOTE_G3, 2000);
      tone(13, NOTE_FS3, 2000);
      digitalWrite(led_red, HIGH);
      delay(3000);
    }

    lcd.clear(); // ecranul se "curata"
    pozitie = 0; // pozitia se reseteaza pentru a fi introdusa o noua parola
    digitalWrite(led_green, LOW);
    digitalWrite(led_red, LOW);
  }
}