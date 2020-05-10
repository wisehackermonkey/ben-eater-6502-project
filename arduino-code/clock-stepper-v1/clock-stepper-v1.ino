//arduino version of  Ben Eater's Clock Kit module
// by oran collins
// github.com/wisehackermonkey
// oranbusiness@gmail.com
// 20200507


int potPin = A0;    // select the input pin for the potentiometer
int ledPin = 9;   // select the pin for the LED
int altbutton_pin = 2;
//volatile byte state = HIGH;

int val = 0;       // variable to store the value coming from the sensor
const int buttonPin = 4;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status
int altbutton_state = 0;
int inPin = 2;         // the number of the input pin
int outPin = 9;       // the number of the output pin

int state = HIGH;      // the current state of the output pin
int reading;           // the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long time = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers


void step() {
  reading = digitalRead(inPin);

  //software debounce the button press so it only registers 1 press at a time
  if (reading == HIGH && previous == LOW && millis() - time > debounce) {
   
    digitalWrite(outPin, LOW);
    delay(100);
    digitalWrite(outPin, HIGH);
    delay(100);
    digitalWrite(outPin, LOW);
    delay(100);

    time = millis();
  }

  previous = reading;
}
void setup() {
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);  // declare the ledPin as an OUTPUT
  pinMode(altbutton_pin, INPUT_PULLUP);  // declare the ledPin as an OUTPUT
  Serial.begin(9600);

  pinMode(inPin, INPUT_PULLUP);
  pinMode(outPin, OUTPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  val = analogRead(potPin);    // read the value from the sensorp
  if (buttonState == HIGH) {
    step();




  } else {
    // turn LED off:
    digitalWrite(ledPin, HIGH);  // turn the ledPin on
    delay(val);                  // stop the program for some time
    digitalWrite(ledPin, LOW);   // turn the ledPin off
    delay(val);
  }

}
void blink() {
  state = !state;

}
