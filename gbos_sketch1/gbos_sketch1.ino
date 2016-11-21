/*
 gbos_sketch1

 When motion detected: 
   - Turn on Indicator LED
   - Turn on a Switch (Relay)
   - Write message out Serial

 When motion ends: 
   - Turn off Indicator LED
   - Turn off a Switch (Relay)
   - Write message out Serial
 
 This is used as part of a Demonstration/POC application called 
 "Giant Ball of String".  Details on this application can be found at:
 https://github.com/imapex/gbos_demo 

 */
 
// Pin Variables
const int indicatorPin1 = 8;            // choose the pin for the LED Indicator
const int motion1Pin = 2;               // choose the input pin for PIR sensor
const int switch1Pin = 3;               // pin for main light switch

// State Variables
int motion1State = LOW;           // we start, assuming no motion detected
int valMotion1 = 0;               // variable for reading the motion status
 
void setup() {
  pinMode(indicatorPin1, OUTPUT);      // declare LED as output
  pinMode(switch1Pin, OUTPUT);         // declare Relay as output
  pinMode(motion1Pin, INPUT);          // declare sensor as input
 
  Serial.begin(9600);
}
 
void loop(){
  valMotion1 = digitalRead(motion1Pin);      // read input valMotion1ue

  if (valMotion1 == HIGH) {                  // check if the input is HIGH
    digitalWrite(indicatorPin1, HIGH);       // turn LED ON
    digitalWrite(switch1Pin, HIGH);          // turn Switch 1 ON

    // Output format {"Sensor":"Motion 1","Value":0/1,"Desc":"Motion Detected/Stopped"}    
    if (motion1State == LOW) {               // New Activity Detected
      Serial.println("{\"Sensor\":\"Motion 1\",\"Value\":1,\"Desc\":\"Motion Detected\"}");
      motion1State = HIGH;
    }
  } else {
    digitalWrite(indicatorPin1, LOW);        // turn LED OFF
    digitalWrite(switch1Pin, LOW);           // turn Switch 1 Off
    if (motion1State == HIGH){               // Activity has Ended
      Serial.println("{\"Sensor\":\"Motion 1\",\"Value\":0,\"Desc\":\"Motion Stopped\"}");
      motion1State = LOW;
    }
  }

}
