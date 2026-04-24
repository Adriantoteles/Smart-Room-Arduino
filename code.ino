#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo windowServo;

// PIN
#define LDR A0
#define LED 3

#define ENA 10
#define IN1 7
#define IN2 8

#define SERVO_PIN 9

#define BTN_MODE 2
#define BTN_WINDOW 4
#define BTN_CURTAIN 5

bool autoMode = true;
bool windowOpen = false;
bool curtainOpen = false;

int lastCondition = -1;

unsigned long motorStartTime = 0;
bool motorRunning = false;

// ================= MOTOR =================
void stopMotor() {
  analogWrite(ENA, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  motorRunning = false;
}

void startForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 200);
  motorStartTime = millis();
  motorRunning = true;
}

void startReverse() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 200);
  motorStartTime = millis();
  motorRunning = true;
}

// ================= SETUP =================
void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(LED, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(BTN_MODE, INPUT_PULLUP);
  pinMode(BTN_WINDOW, INPUT_PULLUP);
  pinMode(BTN_CURTAIN, INPUT_PULLUP);

  windowServo.attach(SERVO_PIN);

  stopMotor();

  lcd.print("SMART ROOM");
  delay(2000);
  lcd.clear();
}

// ================= LOOP =================
void loop() {

  // ===== BUTTON MODE =====
  if (digitalRead(BTN_MODE) == LOW) {
    delay(200);
    autoMode = !autoMode;
    lcd.clear();
    while (digitalRead(BTN_MODE) == LOW);
  }

  int ldr = analogRead(LDR);
  int condition;

  if (ldr < 300) condition = 1;        // bright
  else if (ldr > 700) condition = 2;   // dark
  else condition = 0;                  // normal

  // ================= AUTO MODE =================
  if (autoMode) {

    lcd.setCursor(10,0);
    lcd.print("AUTO");

    if (condition != lastCondition) {

      if (condition == 1) {
        analogWrite(LED, 0);
        windowServo.write(90);
        startForward();
        lcd.setCursor(0,1);
        lcd.print("Bright Mode    ");
      }

      else if (condition == 2) {
        analogWrite(LED, 255);
        windowServo.write(0);
        startReverse();
        lcd.setCursor(0,1);
        lcd.print("Dark Mode      ");
      }

      else {
        analogWrite(LED, 120);
        windowServo.write(45);
        stopMotor();
        lcd.setCursor(0,1);
        lcd.print("Normal Mode    ");
      }

      lastCondition = condition;
    }

    // STOP otomatis
    if (motorRunning && millis() - motorStartTime > 3000) {
      stopMotor();
    }
  }

  // ================= MANUAL MODE =================
  else {

    lcd.setCursor(10,0);
    lcd.print("MAN ");

    lcd.setCursor(0,1);
    lcd.print("W:");
    lcd.print(windowOpen ? "O" : "C");
    lcd.print(" C:");
    lcd.print(curtainOpen ? "O" : "C");

    // ===== WINDOW BUTTON =====
    if (digitalRead(BTN_WINDOW) == LOW) {
      delay(200);
      windowOpen = !windowOpen;

      if (windowOpen) windowServo.write(90);
      else windowServo.write(0);

      while (digitalRead(BTN_WINDOW) == LOW);
    }

    // ===== CURTAIN BUTTON =====
    if (digitalRead(BTN_CURTAIN) == LOW) {
      delay(200);
      curtainOpen = !curtainOpen;

      if (curtainOpen) {
        startForward();
      } else {
        startReverse();
      }

      while (digitalRead(BTN_CURTAIN) == LOW);
    }

    // stop motor otomatis
    if (motorRunning && millis() - motorStartTime > 3000) {
      stopMotor();
    }
  }

  // ===== DISPLAY LDR =====
  lcd.setCursor(0,0);
  lcd.print("L:");
  lcd.print(ldr);
  lcd.print("   ");

  delay(100);
}
