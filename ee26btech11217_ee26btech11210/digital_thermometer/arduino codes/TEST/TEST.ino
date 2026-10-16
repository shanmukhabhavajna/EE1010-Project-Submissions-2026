#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int PT100_PIN = A0;
const float R_FIXED = 4729.0;
const float R0 = 100.0;
const float ALPHA = 0.00385;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);

  lcd.setCursor(0, 0);
  lcd.print("PT100 Thermometer");
  delay(1500);
  lcd.clear();
}
void loop() {
  static unsigned long lastUpdate = 0;

  if (millis() - lastUpdate < 1000) {
    return;
  }
  lastUpdate = millis();

  long total = 0;

  for (int i = 0; i < 20; i++) {
    total += analogRead(PT100_PIN);
    delay(5);
  }

  float adcValue = total / 20.0;

  Serial.print("ADC: ");
  Serial.println(adcValue);

  if (adcValue <= 0 || adcValue >= 1023) {
    lcd.setCursor(0, 0);
    lcd.print("Check PT100     ");
    lcd.setCursor(0, 1);
    lcd.print("Wiring / Sensor ");
    return;
  }

  float resistance = R_FIXED * adcValue / (1023.0 - adcValue);
  float temperature = (resistance / R0 - 1.0) / ALPHA;

  lcd.setCursor(0, 0);
  lcd.print("Temperature:    ");

  lcd.setCursor(0, 1);
  lcd.print(temperature, 1);
  lcd.write((byte)223);
  lcd.print("C             ");

  Serial.print("Resistance: ");
  Serial.print(resistance, 2);
  Serial.print(" ohm | Temperature: ");
  Serial.print(temperature, 2);
  Serial.println(" C");
}
