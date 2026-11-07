/* Reconstructed, NOT the original uploaded sketch. See docs/provenance.md.
   Educational prototype: humidity is displayed, not actively regulated. */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DFRobot_DHT11.h>
#include "control.h"

constexpr int DHT_PIN = 2, BUZZER_PIN = 4, BULB_PIN = 8, FAN_PIN = 9;
LiquidCrystal_I2C lcd(0x27, 16, 2);
DFRobot_DHT11 sensor;
ControlState state;

void outputs() {
  digitalWrite(BULB_PIN, state.bulb ? LOW : HIGH);
  digitalWrite(FAN_PIN, state.fan ? LOW : HIGH);
}
void beep(int count) {
  for (int i = 0; i < count; ++i) {
    digitalWrite(BUZZER_PIN, HIGH); delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    if (i + 1 < count) delay(200);
  }
}
void setup() {
  // Preload HIGH before enabling the active-LOW relay outputs.
  digitalWrite(BULB_PIN, HIGH); digitalWrite(FAN_PIN, HIGH);
  pinMode(BULB_PIN, OUTPUT); pinMode(FAN_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT); digitalWrite(BUZZER_PIN, LOW);
  lcd.init(); lcd.backlight(); lcd.print("Smart Incubation");
  lcd.setCursor(0, 1); lcd.print("System"); delay(2000);
}
void loop() {
  sensor.read(DHT_PIN);
  const int temperature = sensor.temperature;
  const int humidity = sensor.humidity;
  lcd.clear();
  // This catches implausible values, NOT every sensor fault. See limitations.
  if (temperature < 0 || temperature > 50 || humidity < 0 || humidity > 100) {
    state = ControlState{}; outputs();
    digitalWrite(BUZZER_PIN, LOW); lcd.print("Sensor Error");
  } else {
    const ControlState previous = state;
    state = nextState(state, temperature); outputs();
    if (state.bulb && !previous.bulb) beep(2);
    if (state.fan && !previous.fan) beep(3);
    lcd.print("T:"); lcd.print(temperature); lcd.print((char)223);
    lcd.print("C H:"); lcd.print(humidity); lcd.print('%');
    lcd.setCursor(0, 1);
    lcd.print(state.bulb ? "Light ON" : state.fan ? "Fan ON" : "Ideal Condition!");
  }
  delay(2000);
}
