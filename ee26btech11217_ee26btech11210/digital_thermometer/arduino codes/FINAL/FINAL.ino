
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int PT100_PIN = A0;
const float R_FIXED = 4729.0;

// Your custom Least Squares Regression (LSQ) Coefficients
// Formula format: Temperature = (A * R^2) + (B * R) + C
const float LSQ_A = -0.01226;
const float LSQ_B = 5.606669;
const float LSQ_C = -443.678;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);

  lcd.setCursor(0, 0);
  lcd.print("PT100 Calibrated");
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

  // 20-sample averaging over 100ms to eliminate electrical noise
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

  // Calculate the physical resistance of the PT100 sensor
  float resistance = R_FIXED * adcValue / (1023.0 - adcValue);
  
  // Custom LSQ quadratic formula applied here for maximum accuracy
  float temperature = (LSQ_A * resistance * resistance) + (LSQ_B * resistance) + LSQ_C;

  lcd.setCursor(0, 0);
  lcd.print("Temperature:    ");

  lcd.setCursor(0, 1);
  lcd.print(temperature, 1);
  lcd.write((byte)223); // Degree symbol
  lcd.print("C             ");

  Serial.print("Resistance: ");
  Serial.print(resistance, 2);
  Serial.print(" ohm | Temperature: ");
  Serial.print(temperature, 2);
  Serial.println(" C");
}
