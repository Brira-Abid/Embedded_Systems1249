#include <WiFi.h>

// Blynk
#define BLYNK_TEMPLATE_ID "TMPL6cd1RFkOJ"
#define BLYNK_TEMPLATE_NAME "Blind Stick"
#define BLYNK_DEVICE_NAME "Blind Stick"
#define BLYNK_AUTH_TOKEN "dYy2xBpszHE0clwYiTBXAz0KKZY1Nj26"

#include <BlynkSimpleEsp32.h>

// ================= USER CONFIGURATION =================
char ssid[] = "OPPO";
char pass[] = "brirathebest";

// ================= PIN DEFINITIONS =================
#define TRIG_PIN 13
#define ECHO_PIN 12
#define BUZZER_PIN 14
#define PANIC_BUTTON_PIN 27

// ================= VARIABLES =================
long duration;
int distance;
bool lastPanicState = HIGH; // ADD THIS LINE - CRITICAL!

void setup()
{
  Serial.begin(115200);

  // Sensor and Output Setup
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(PANIC_BUTTON_PIN, INPUT_PULLUP);

  // Initial state
  digitalWrite(TRIG_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // Connect to Wi-Fi and Blynk
  Serial.print("Connecting to Wi-Fi...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Buzz once to show startup is complete
  digitalWrite(BUZZER_PIN, HIGH);
  delay(200);
  digitalWrite(BUZZER_PIN, LOW);
  Serial.println("Setup Complete!");
}

void loop()
{
  Blynk.run();

  // --- OBSTACLE DETECTION ---
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0)
  {
    Serial.println("No echo received - check wiring/voltage!");
    digitalWrite(BUZZER_PIN, LOW);
  }
  else
  {
    distance = duration * 0.034 / 2;

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Send distance to Blynk (Virtual Pin V1)
    Blynk.virtualWrite(V1, distance);

    if (distance > 0 && distance < 50)
    {
      digitalWrite(BUZZER_PIN, HIGH);
      delay(100);
      digitalWrite(BUZZER_PIN, LOW);

      if (distance < 20)
        delay(100);
      else
        delay(400);
    }
    else
    {
      digitalWrite(BUZZER_PIN, LOW);
    }
  }

  // --- PANIC BUTTON LOGIC ---
  bool panicPressed = (digitalRead(PANIC_BUTTON_PIN) == LOW);

  if (panicPressed && !lastPanicState)
  {
    Serial.println("PANIC BUTTON PRESSED!");

    // 1. TRIGGER EVENT - Send to V0
    Blynk.virtualWrite(V0, 1);

    // 2. Also log event
    Blynk.logEvent("panic_button", "Emergency! Help needed!");

    // 3. Buzzer alert
    for (int i = 0; i < 3; i++)
    {
      digitalWrite(BUZZER_PIN, HIGH);
      delay(300);
      digitalWrite(BUZZER_PIN, LOW);
      delay(200);
    }

    // Reset V0 after 2 seconds
    delay(2000);
    Blynk.virtualWrite(V0, 0);
  }

  lastPanicState = panicPressed;

  delay(100); // Small delay between loops
}