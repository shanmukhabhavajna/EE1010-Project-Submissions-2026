// ============================================================ //
// 4-DIGIT/6-DIGIT DIGITAL CLOCK USING 4x4 K-MAP TO 7447 LOGIC  //
// Common-Anode 7-segment displays via 7447 Decoder           //
// ============================================================ //

// BCD OUTPUTS TO 7447
const int bcdA = 2;   // Out_A = LSB
const int bcdB = 3;   // Out_B
const int bcdC = 4;   // Out_C
const int bcdD = 5;   // Out_D = MSB

// Push buttons
const int minUpBtnPin   = 7;
const int hourUpBtnPin  = 6;
const int minDownBtnPin = A0;
const int hourDownBtnPin = A1;

// Digit enable pins
const int digitHourTens  = 8;
const int digitHourUnits = 9;
const int digitMinTens   = 10;
const int digitMinUnits  = 11;
const int digitSecTens   = 12;
const int digitSecUnits  = 13;

// Time variables
int hours = 12;
int minutes = 0;
int seconds = 0;
unsigned long previousMillis = 0;
const unsigned long interval = 1000;

// Button states
bool lastMinUpState = HIGH;
bool lastHourUpState = HIGH;
bool lastMinDownState = HIGH;
bool lastHourDownState = HIGH;

// ============================================================ //
// SETUP                                                        //
// ============================================================ //
void setup() {
  pinMode(bcdA, OUTPUT);
  pinMode(bcdB, OUTPUT);
  pinMode(bcdC, OUTPUT);
  pinMode(bcdD, OUTPUT);
  
  pinMode(digitHourTens, OUTPUT);
  pinMode(digitHourUnits, OUTPUT);
  pinMode(digitMinTens, OUTPUT);
  pinMode(digitMinUnits, OUTPUT);
  pinMode(digitSecTens, OUTPUT);
  pinMode(digitSecUnits, OUTPUT);
  
  pinMode(minUpBtnPin, INPUT_PULLUP);
  pinMode(hourUpBtnPin, INPUT_PULLUP);
  pinMode(minDownBtnPin, INPUT_PULLUP);
  pinMode(hourDownBtnPin, INPUT_PULLUP);
  
  allDigitsOff();
}

// ============================================================ //
// MAIN LOOP                                                    //
// ============================================================ //
void loop() {
  unsigned long currentMillis = millis();

  // -------- 1 SECOND CLOCK --------
  if (currentMillis - previousMillis >= interval) {
    previousMillis += interval;
    seconds++;
    if (seconds >= 60) {
      seconds = 0;
      minutes++;
      if (minutes >= 60) {
        minutes = 0;
        hours++;
        if (hours > 12) {
          hours = 1;
        }
      }
    }
  }

  // -------- BUTTONS --------
  checkButtons();

  // -------- DISPLAY --------
  updateDisplay();
}

// ============================================================ //
// BUTTON CONTROL (FIXED SCOPE BRACKETS)                        //
// ============================================================ //
void checkButtons() {
  bool currentMinUp   = digitalRead(minUpBtnPin);
  bool currentHourUp  = digitalRead(hourUpBtnPin);
  bool currentMinDown = digitalRead(minDownBtnPin);
  bool currentHourDown = digitalRead(hourDownBtnPin);
  bool changed = false;

  // -------- Minutes UP --------
  if (lastMinUpState == HIGH && currentMinUp == LOW) {
    minutes++;
    if (minutes >= 60) {
      minutes = 0;
    }
    seconds = 0;
    changed = true;
  }

  // -------- Minutes DOWN --------
  if (lastMinDownState == HIGH && currentMinDown == LOW) {
    minutes--;
    if (minutes < 0) {
      minutes = 59;
    }
    seconds = 0;
    changed = true;
  }

  // -------- Hours UP --------
  if (lastHourUpState == HIGH && currentHourUp == LOW) {
    hours++;
    if (hours > 12) {
      hours = 1;
    }
    seconds = 0;
    changed = true;
  }

  // -------- Hours DOWN --------
  if (lastHourDownState == HIGH && currentHourDown == LOW) {
    hours--;
    if (hours < 1) {
      hours = 12;
    }
    seconds = 0;
    changed = true;
  }

  // Save the states for the next loop run
  lastMinUpState = currentMinUp;
  lastHourUpState = currentHourUp;
  lastMinDownState = currentMinDown;
  lastHourDownState = currentHourDown;

  // Only debounce if an action actually happened
  if (changed) {
    delay(150); 
  }
}

// ============================================================ //
// DISPLAY MULTIPLEXING                                         //
// ============================================================ //
void updateDisplay() {
  int hTens  = hours / 10;
  int hUnits = hours % 10;
  int mTens  = minutes / 10;
  int mUnits = minutes % 10;
  int sTens  = seconds / 10;
  int sUnits = seconds % 10;

  showDigit(hTens, digitHourTens);
  showDigit(hUnits, digitHourUnits);
  showDigit(mTens, digitMinTens);
  showDigit(mUnits, digitMinUnits);
  showDigit(sTens, digitSecTens);
  showDigit(sUnits, digitSecUnits);
}

// ============================================================ //
// 4-INPUT / 4-OUTPUT K-MAP BCD LOGIC                           //
// ============================================================ //
void showDigit(int n, int digitPin) {
  // 1. Clear old data by turning off ALL digits first (prevents ghosting)
  allDigitsOff(); 

  // 2. 4 Inputs extracted from the number (0-9)
  bool A = n & 1; // LSB (2^0)
  bool B = n & 2; //     (2^1)
  bool C = n & 4; //     (2^2)
  bool D = n & 8; // MSB (2^3)

  // 3. K-Map Minimised Equations for BCD-to-BCD conversion (0-9)
  // These equations evaluate standard BCD passing through to the 7447.
  bool outA = A; 
  bool outB = B && !D; 
  bool outC = C && !D;
  bool outD = D;

  // 4. Send the 4 K-Map processed outputs to the 7447 decoder
  digitalWrite(bcdA, outA);
  digitalWrite(bcdB, outB);
  digitalWrite(bcdC, outC);
  digitalWrite(bcdD, outD);

  // 5. Turn ON the specific target digit display
  digitalWrite(digitPin, HIGH);
  
  // 6. Multiplexing view delay
  delay(2); 
}

// ============================================================ //
// TURN OFF ALL DIGITS                                          //
// ============================================================ //
void allDigitsOff() {
  digitalWrite(digitHourTens, LOW);
  digitalWrite(digitHourUnits, LOW);
  digitalWrite(digitMinTens, LOW);
  digitalWrite(digitMinUnits, LOW);
  digitalWrite(digitSecTens, LOW);
  digitalWrite(digitSecUnits, LOW);
}
