const int buttonPin = 2;
const int ledPin = 3;
const int greenPin = 10;
const int bluePin = 11;
const int pressedLevel = HIGH;

// 常亮、慢閃、中速閃、快閃。
const unsigned long blinkIntervals[] = {0, 650, 320, 120};

int mode = 0;
int lastReading;
int stableButton;
bool ledOn = true;
unsigned long buttonChangedAt = 0;
unsigned long lastBlinkAt = 0;

void setup() {
  pinMode(buttonPin, INPUT);
  lastReading = stableButton = digitalRead(buttonPin);

  pinMode(ledPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  digitalWrite(ledPin, LOW);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);
}

void loop() {
  unsigned long now = millis();
  int reading = digitalRead(buttonPin);

  if (reading != lastReading) {
    lastReading = reading;
    buttonChangedAt = now;
  }

  // 讀值穩定 25 毫秒後才接受，避免按一下跳兩格。
  if (reading != stableButton && now - buttonChangedAt >= 25) {
    stableButton = reading;

    if (stableButton == pressedLevel) {
      mode = (mode + 1) % 4;
      ledOn = true;
      lastBlinkAt = now;
    }
  }

  if (mode != 0 && now - lastBlinkAt >= blinkIntervals[mode]) {
    ledOn = !ledOn;
    lastBlinkAt = now;
  }

  digitalWrite(ledPin, ledOn ? LOW : HIGH);
}