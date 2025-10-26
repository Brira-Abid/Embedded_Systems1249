/*
  Task 2
  Button Press Type
  Name: Brira Abid
  Reg. No: 23-NTU-CS-1249

  Working:
  - Button 1 cycles through LED modes modes = OFF , BLINK , PWM , ON
  - Button 2 set to OFF
  - OLED displays current mode
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define button 2
#define led 9
#define buzzer 8

bool ledState = false;

void setup()
{
  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Press Now");
  display.display();
}

void loop()
{
  if (digitalRead(button) == LOW)
  {
    unsigned long pressStart = millis();
    while (digitalRead(button) == LOW)
      ; // waiting to release
    unsigned long pressDuration = millis() - pressStart;

    display.clearDisplay();
    display.setCursor(0, 10);

    if (pressDuration > 1500)
    { // Long press
      display.println("Long Press!");
      tone(buzzer, 1000, 500); // play tone for 0.5 sec
    }
    else
    { // Short press
      ledState = !ledState;
      digitalWrite(led, ledState);
      display.println("Short Press!");
    }

    display.display();
    delay(300);
  }
}