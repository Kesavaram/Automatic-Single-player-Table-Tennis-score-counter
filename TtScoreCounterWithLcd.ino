/*

  The circuit:
   LCD RS pin to digital pin 12
   LCD Enable pin to digital pin 11
   LCD D4 pin to digital pin 5
   LCD D5 pin to digital pin 4
   LCD D6 pin to digital pin 3
   LCD D7 pin to digital pin 2
   LCD R/W pin to ground
   LCD VSS pin to ground
   LCD VCC pin to 5V
   10K resistor:
   ends to +5V and ground
   wiper to LCD VO pin (pin 3)

  Library originally added 18 Apr 2008
  by David A. Mellis
  library modified 5 Jul 2009
  by Limor Fried (http://www.ladyada.net)
  example added 9 Jul 2009
  by Tom Igoe
  modified 22 Nov 2010
  by Tom Igoe
  modified 7 Nov 2016
  by Arturo Guadalupi

*/

// include the library code:
#define SerialDebug false
#include <LiquidCrystal.h>
#include "TTScoreCounter.hpp"
#define PinChangeInterrupt A3


const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


unsigned long when = 0;

TTScoreCounter scoreCounterObj(PinChangeInterrupt);
void setup()
{


  if (SerialDebug)
  {
    Serial.begin(9600);
    Serial.println("program started");
  }




  lcd.begin(16, 2);
  lcd.print("  TT score");
  lcd.setCursor(0, 1);
  lcd.print("   counter");

  delay(2000);
  lcd.clear();
  lcd.print("Kesavaram");
  lcd.setCursor(0, 1);
  lcd.print("Krishnamoorthy");
  delay(2000);

  lcd.clear();

  lcd.print("TT score:");

}

void loop()
{

  if (scoreCounterObj.run())
  {

    if (SerialDebug)
    {
      Serial.println("millis = " + (String)millis() + " score value = " + (String)scoreCounterObj.getScore() + "consecutive balls" + (String) scoreCounterObj.getConsecutiveBalls());
    }


    lcd.setCursor(0, 1);
    lcd.print(scoreCounterObj.getScore());

  }


  delay(10);

}
