#include <SoftwareSerial.h>

#define LED_ONE 5 
#define LED_TWO 6 
#define LED_THREE 9 
#define LED_FOUR 10 
#define LED_FIVE 11 
#define FADE_AMOUNT 10

SoftwareSerial mySerial(0, 1); // RX, TX
int maxPriority;
int prevLEDPin;
int brightness;
int maxBrightness;
int fadeAmount;

void setup() {
  mySerial.begin(9600);
  mySerial.println("Starting programm");

  pinMode(LED_ONE, OUTPUT);
  pinMode(LED_TWO, OUTPUT);
  pinMode(LED_THREE, OUTPUT);
  pinMode(LED_FOUR, OUTPUT);
  pinMode(LED_FIVE, OUTPUT);

  turnOffLEDs();
  // initialising variables
  maxPriority = 0;
  prevLEDPin = LED_ONE;
  brightness = 0;
  fadeAmount = FADE_AMOUNT;

  maxBrightness = (255/FADE_AMOUNT)*(FADE_AMOUNT);
}

void turnOffLEDs() {
  analogWrite(LED_ONE, 0);
  analogWrite(LED_TWO, 0);
  analogWrite(LED_THREE, 0);
  analogWrite(LED_FOUR, 0);
  analogWrite(LED_FIVE, 0);
}

int findLEDPin(int ledNo) {
  switch (ledNo) {
    case 1:
      return LED_ONE;
    case 2:
      return LED_TWO;
    case 3: 
      return LED_THREE;
    case 4: 
      return LED_FOUR;
    case 5:
      return LED_FIVE;
    default:
      return LED_ONE;
  }
}

void resetLEDFade() {
  brightness = 0;
  fadeAmount = FADE_AMOUNT;
}

void loop() {
  if (mySerial.available() > 0) {
    String receivedData = mySerial.readStringUntil('\n');
    mySerial.println("received data: " + receivedData);

    int delimiterIndex = receivedData.indexOf('-');
    
    if (delimiterIndex != -1) {
      int currPriority = receivedData.substring(0, delimiterIndex).toInt();
      int ledNo = receivedData.substring(delimiterIndex+1).toInt();
      int currLEDPin = findLEDPin(ledNo);

      mySerial.println("curr priority: " + String(currPriority));
      mySerial.println("max priority: " + String(maxPriority));
      mySerial.println("curr ledNo: " + String(ledNo));
      mySerial.println("curr led pin: " + String(currLEDPin));

      // handle clear notifications
      if (currPriority == 0) {
        mySerial.println("Clearing Notifications");
        turnOffLEDs();
        resetLEDFade();
        maxPriority = 0;
        prevLEDPin = LED_ONE;
      }

      else if (currPriority > maxPriority) {
        // mySerial.println("turning led with pin no: " + String(currLEDPin));
        // update max priority
        maxPriority = currPriority;

        // turn off previously on LED
        analogWrite(prevLEDPin, 0);
        resetLEDFade();

        // update previous LED PIN for next iteration
        prevLEDPin = currLEDPin;

        mySerial.println("LED turned on");
      }
    }
  }

  if (maxPriority != 0) {
    analogWrite(prevLEDPin, brightness);

    brightness = brightness + fadeAmount;

    if (brightness <= 0 || brightness >= maxBrightness) {
      fadeAmount = -fadeAmount;
    }
  }

  delay(50);
}
