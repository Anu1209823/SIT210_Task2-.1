/*These lines define the pin numbers for the external LED (externalLedPin) and the push button (buttonPin).*/

const int externalLedPin = 3; 
const int buttonPin = 2; 

// Morse code representation of my first name
const char* morseCode = ".- -. ..- ... .... .. -.- .-   -.-. .... .- ..- .... .- -.";

/*These lines define the timing values for different elements of Morse code. dotDuration is the duration of a dot, 
dashDuration is the duration of a dash (3 times a dot), and symbolGapDuration is the gap between symbols (same as dot duration).*/
const int dotDuration = 200; // milliseconds
const int dashDuration = 3 * dotDuration; // 3 times the dot duration
const int symbolGapDuration = dotDuration; // Same as dot duration

/*This line defines the gap duration between letters (3 times the dot duration).*/
const int letterGapDuration = 3 * dotDuration; 


//These lines define variables related to tracking the state of the push button and handling button debouncing. 

int buttonState = HIGH;//It helps us keep track of what the button is doing right now.
int lastButtonState = HIGH;// This variable remembers the state the button was in the last time we checked.

/*This variable remembers the time when the button's state last changed. 
This is useful because sometimes, when you press a button, it might "bounce" a little bit due to the physical mechanics 
of the button.*/
unsigned long lastDebounceTime = 0;
 
/*This is the amount of time we wait before deciding that a button press is for real.
 When you press a button, it might not settle immediately due to that bouncing I mentioned.*/
const unsigned long debounceDelay = 50; 

/*The setup() function is executed once when the Arduino starts. 
It sets up the external LED pin as an output, the push button pin as an input with internal pull-up resistor, 
and initializes the external LED to be turned off. It also starts the serial communication at a baud rate of 9600.*/

void setup() {
  pinMode(externalLedPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  digitalWrite(externalLedPin, LOW); // Turn off the external LED
  Serial.begin(9600);
}

/*The loop() function is executed repeatedly after the setup() function. 
It reads the current state of the push button using digitalRead().
It implements button debouncing logic using the lastDebounceTime and debounceDelay. 
If the button state has changed and the debounce time has passed, it checks if the button is pressed (buttonState == LOW). 
If the button is pressed, it calls the blinkMorseCode() function.*/

void loop() {
  int reading = digitalRead(buttonPin);
  
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      
      if (buttonState == LOW) {
        // Button is pressed
        blinkMorseCode();
      }
    }
  }
  
  lastButtonState = reading;
}

/*The blinkMorseCode() function is responsible for blinking the Morse code representation stored in the morseCode string.
It uses a for loop to iterate through each character in the morseCode string. It checks whether the character is a dot (.) 
or a dash (-), and blinks the external LED accordingly with the specified durations (dotDuration or dashDuration).
After each symbol is blinked, it introduces a gap (symbolGapDuration) between symbols.
After each letter is blinked, it introduces a longer gap (letterGapDuration) between letters.*/

void blinkMorseCode() {
  for (int i = 0; morseCode[i] != '\0'; i++) {
    if (morseCode[i] == '.') {
      digitalWrite(externalLedPin, HIGH);
      delay(dotDuration);
      digitalWrite(externalLedPin, LOW);
    } else if (morseCode[i] == '-') {
      digitalWrite(externalLedPin, HIGH);
      delay(dashDuration);
      digitalWrite(externalLedPin, LOW);
    }
    
    delay(symbolGapDuration);
  }
  
  delay(letterGapDuration);
}