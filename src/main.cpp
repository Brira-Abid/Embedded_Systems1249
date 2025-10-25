#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#ifndef PI
#endif

void drawArc(int16_t cx, int16_t cy, int16_t r, float startDeg, float endDeg, uint16_t color);
void smileFace();
void coolFace();
void heartShape();
void moonShape();
void starShape();
void coffeeCup();
void musicNote();

void setup()
{
  Wire.begin(21, 22); // SDA, SCL for ESP32
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR))
  {
    for (;;)
      ;
  }
  display.clearDisplay();
  display.display();
}

void loop()
{
  smileFace();
  delay(1200);
  coolFace();
  delay(1300);
  heartShape();
  delay(1200);
  moonShape();
  delay(1300);
  starShape();
  delay(1200);
  coffeeCup();
  delay(1300);
  musicNote();
  delay(1200);
}

void drawArc(int16_t cx, int16_t cy, int16_t r, float startDeg, float endDeg, uint16_t color)
{
  float start = startDeg * PI / 180.0;
  float end = endDeg * PI / 180.0;
  for (float a = start; a <= end; a += 0.07)
  {
    int16_t x = cx + r * cos(a);
    int16_t y = cy + r * sin(a);
    display.drawPixel(x, y, color);
  }
}

// Emojis

void smileFace()
{
  display.clearDisplay();
  display.drawCircle(64, 20, 12, SSD1306_WHITE); // face
  display.fillCircle(59, 17, 2, SSD1306_WHITE);
  display.fillCircle(69, 17, 2, SSD1306_WHITE);
  drawArc(64, 22, 7, 25, 155, SSD1306_WHITE); // smile
  display.display();
}

void coolFace()
{
  display.clearDisplay();
  display.drawCircle(64, 48, 12, SSD1306_WHITE);
  display.fillRect(55, 45, 18, 4, SSD1306_WHITE); // sunglasses
  display.fillCircle(59, 47, 1, SSD1306_BLACK);
  display.fillCircle(69, 47, 1, SSD1306_BLACK);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(52, 58);
  display.print("COOL!");
  display.display();
}

void heartShape()
{
  display.clearDisplay();
  display.fillCircle(60, 18, 5, SSD1306_WHITE);
  display.fillCircle(68, 18, 5, SSD1306_WHITE);
  display.fillTriangle(55, 20, 73, 20, 64, 35, SSD1306_WHITE);
  display.display();
}

void moonShape()
{
  display.clearDisplay();
  display.fillCircle(60, 45, 12, SSD1306_WHITE);
  display.fillCircle(65, 45, 10, SSD1306_BLACK);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(50, 58);
  display.print("MOON");
  display.display();
}

void starShape()
{
  display.clearDisplay();
  // Draw a star with more arms
  display.drawLine(64, 10, 64, 30, SSD1306_WHITE);
  display.drawLine(54, 20, 74, 20, SSD1306_WHITE);
  display.drawLine(57, 13, 71, 27, SSD1306_WHITE);
  display.drawLine(71, 13, 57, 27, SSD1306_WHITE);
  display.display();
}

void coffeeCup()
{
  display.clearDisplay();
  display.drawRect(54, 38, 20, 14, SSD1306_WHITE); // cup
  display.drawCircle(75, 45, 3, SSD1306_WHITE);    // handle
  // steam lines
  display.drawLine(60, 34, 60, 38, SSD1306_WHITE);
  display.drawLine(64, 33, 64, 38, SSD1306_WHITE);
  display.drawLine(68, 34, 68, 38, SSD1306_WHITE);
  display.display();
}

void musicNote()
{
  display.clearDisplay();
  display.drawLine(62, 15, 62, 45, SSD1306_WHITE);
  display.drawLine(62, 15, 78, 22, SSD1306_WHITE);
  display.drawLine(78, 22, 78, 45, SSD1306_WHITE);
  display.fillCircle(62, 47, 3, SSD1306_WHITE);
  display.fillCircle(78, 49, 3, SSD1306_WHITE);
  display.display();
}
