/*
  Task 1
  LED Mode Controller with OLED Display
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

// Pin definitions
#define BTN_MODE 2
#define BTN_RESET 3
#define LED1 9
#define LED2 10
#define BUZZER 8

int mode = 0;
bool lastButtonState = HIGH;

void setup()
{
  pinMode(BTN_MODE, INPUT_PULLUP);
  pinMode(BTN_RESET, INPUT_PULLUP);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  showMode();
}

void loop()
{
  bool currentButton = digitalRead(BTN_MODE);

  // Mode button pressed
  if (currentButton == LOW && lastButtonState == HIGH)
  {
    delay(50); // debounce
    mode = (mode + 1) % 4;
    showMode();
  }
  lastButtonState = currentButton;

  // Reset button pressed
  if (digitalRead(BTN_RESET) == LOW)
  {
    mode = 0;
    showMode();
  }

  // Mode behaviors
  if (mode == 0)
  { // OFF
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  }
  else if (mode == 1)
  { // BLINK
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    delay(100);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    delay(100);
  }
  else if (mode == 2)
  { // ON
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
  }
  else if (mode == 3)
  { // PWM FADE
    for (int i = 0; i <= 255; i++)
    {
      analogWrite(LED1, i);
      analogWrite(LED2, 255 - i);
      delay(2);
    }
    for (int i = 255; i >= 0; i--)
    {
      analogWrite(LED1, i);
      analogWrite(LED2, 255 - i);
      delay(2);
    }
  }
}

void showMode()
{
  display.clearDisplay();
  display.setCursor(0, 10);
  display.print("Current Mode: ");

  if (mode == 0)
    display.println("OFF");
  else if (mode == 1)
    display.println("BLINK");
  else if (mode == 2)
    display.println("ON");
  else if (mode == 3)
    display.println("PWM Fade");

  display.display();
}