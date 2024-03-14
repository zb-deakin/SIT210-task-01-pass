int buttonState = 0;
int ledPin = 12;
int buttonPin = 11;

bool buttonHasBeenPressedAtLeastOnce = false;
int buttonIsBeingPressed = false;

int dotDelay = 300;
int dashDelay = 900;

int letterIndex = 0;
int morseCodeIndex = 0;

int lettersInMyName[][4] = {
  { dashDelay, dashDelay, dotDelay, dotDelay },   // z
  { dotDelay, dashDelay },                        // a
  { dashDelay, dotDelay, dashDelay, dashDelay },  // y
  { dashDelay, dotDelay }                         // n
};

int letterDotDashCount() {
  return sizeof(lettersInMyName[letterIndex]) / sizeof(lettersInMyName[letterIndex][morseCodeIndex]);
}

size_t lettersTotalCount = sizeof(lettersInMyName) / sizeof(lettersInMyName[letterIndex]);
size_t dotDashCountForLetterAtIndex = letterDotDashCount();

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  // is the button being pressed
  buttonState = digitalRead(buttonPin);

  // stop and reset everything while the button is being pressed
  if (buttonState == HIGH) {
    digitalWrite(ledPin, LOW);

    buttonHasBeenPressedAtLeastOnce = true;
    letterIndex = 0;
    morseCodeIndex = 0;

    return;
  }

  // wait until the first time the button is pressed before starting to flash LED
  if (!buttonHasBeenPressedAtLeastOnce) {
    return;
  }

  // flash dot/dash
  digitalWrite(ledPin, HIGH);
  delay(lettersInMyName[letterIndex][morseCodeIndex]);
  digitalWrite(ledPin, LOW);
  delay(200);

  // move index to next dot/dash
  morseCodeIndex += 1;

  // count how many dots dashes for this letter
  dotDashCountForLetterAtIndex = letterDotDashCount();

  // if all dots/dashes complete for this letter, move to next letter
  if (morseCodeIndex >= dotDashCountForLetterAtIndex) {
    morseCodeIndex = 0;
    letterIndex += 1;

    // separate letters out a bit with a pause, indicate space using internal LED
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
  }

  // if all letters of my name have displayed already, go back to first letter
  if (letterIndex >= lettersTotalCount) {
    letterIndex = 0;
  }
}
