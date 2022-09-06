# Locker with passcode
## Introducere
Ideea proiectului este luată dintr-un [curs despre Arduino aflat pe platforma Skillshare](https://skl.sh/3BiAi2E), acesta fiind motivul pentru care am păstrat numele în limba engleză.

## Componente necesare
- Arduino Uno
- Breadboard (opțional)
- Keypad
- Ecran LCD
- Servo motor
- Buzzer pasiv
- 2x LED-uri
- Mai multe fire male-to-male sau female-to-male (în funcție de preferința pentru breadboard)
- 2x Rezistori de 220 ohmi
- Rezistor cu rezistență variabilă

## Editor
Inițial am folosit Arduino IDE, iar mai apoi m-am mutat pe Visual Studio Code folosind extensia [PlatformIO](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide).

## Descriere
Prin intermediul tastaturii se va introduce o parolă de 4 caractere ce vor fi afișate pe ecranul LCD. Dacă parola introdusă este corectă, motorul servo se va roti, LED-ul verde se va aprinde și buzzer-ul va scoate un anumit sunet, iar "seiful" va rămâne deschis timp de 10 secunde. Dacă parola introdusă este greșită se va aprinde LED-ul roșu și buzzer-ul va scoate un sunet diferit. Dacă parola este introdusă de 3 ori la rând greșit, buzzer-ul va scoate un sunet mai pronunțat, iar "seiful" va fi blocat pentru 30 de secunde.
