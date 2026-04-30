/*
  ESP32 Dual Button Motor Controller
  ----------------------------------
  Blue button  -> Low speed
  Blue+Yellow  -> High speed
  No button    -> Stop
*/

struct MotorDriverConfig {
  int pinForwardPWM;
  int pinReversePWM;
  int pwmFreq;
  int pwmResolution;

  int dutyLow;
  int dutyHigh;
};

class DualButton {
  private:
    int pinBlue;
    int pinYellow;

    bool stateBlue;
    bool stateYellow;

  public:
    DualButton(int bluePin, int yellowPin) {
      pinBlue = bluePin;
      pinYellow = yellowPin;

      pinMode(pinBlue, INPUT_PULLUP);
      pinMode(pinYellow, INPUT_PULLUP);

      stateBlue = HIGH;
      stateYellow = HIGH;
    }

    bool readChange() {
      bool currentBlue = digitalRead(pinBlue);
      bool currentYellow = digitalRead(pinYellow);

      if (currentBlue == stateBlue && currentYellow == stateYellow) {
        return false;
      }

      stateBlue = currentBlue;
      stateYellow = currentYellow;
      return true;
    }

    bool isBluePressed()   { return stateBlue   == LOW; }
    bool isYellowPressed() { return stateYellow == LOW; }
};

class DCMotorDriver {
  private:
    MotorDriverConfig cfg;

  public:
    DCMotorDriver(MotorDriverConfig config) {
      cfg = config;
    }

    void begin() {
      ledcAttach(cfg.pinForwardPWM, cfg.pwmFreq, cfg.pwmResolution);
      ledcAttach(cfg.pinReversePWM, cfg.pwmFreq, cfg.pwmResolution);
      stop();
    }

    void forward(int duty) {
      ledcWrite(cfg.pinForwardPWM, duty);
      ledcWrite(cfg.pinReversePWM, 0);
    }

    void lowSpeed()  { forward(cfg.dutyLow); }
    void highSpeed() { forward(cfg.dutyHigh); }

    void stop() {
      ledcWrite(cfg.pinForwardPWM, 0);
      ledcWrite(cfg.pinReversePWM, 0);
    }
};

/* ----------- Hardware Setup ----------- */
DualButton buttons(14, 26);

MotorDriverConfig motorConfig = {
  25,      // forward PWM
  33,      // reverse PWM
  20000,   // PWM frequency
  8,       // resolution
  150,     // low speed duty
  200      // high speed duty
};

DCMotorDriver motor(motorConfig);

/* ----------- Setup ----------- */
void setup() {
  Serial.begin(115200);
  motor.begin();
  Serial.println("Motor Controller Ready");
}

/* ----------- Main Loop ----------- */
void loop() {

  if (!buttons.readChange()) {
    delay(50);
    return;
  }

  bool bluePressed   = buttons.isBluePressed();
  bool yellowPressed = buttons.isYellowPressed();

  if (!bluePressed && !yellowPressed) {
    motor.stop();
    Serial.println("Motor OFF");
  }
  else if (bluePressed && !yellowPressed) {
    motor.lowSpeed();
    Serial.println("Motor LOW SPEED");
  }
  else if (bluePressed && yellowPressed) {
    motor.highSpeed();
    Serial.println("Motor HIGH SPEED");
  }
  else {
    motor.stop();
    Serial.println("State not defined");
  }

  delay(50);
}