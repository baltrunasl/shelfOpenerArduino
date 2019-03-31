/****************************************************************************** 
SparkFun Easy Driver Basic Demo
Toni Klopfenstein @ SparkFun Electronics
March 2015
https://github.com/sparkfun/Easy_Driver

Simple demo sketch to demonstrate how 5 digital pins can drive a bipolar stepper motor,
using the Easy Driver (https://www.sparkfun.com/products/12779). Also shows the ability to change
microstep size, and direction of motor movement.

Development environment specifics:
Written in Arduino 1.6.0

This code is beerware; if you see me (or any other SparkFun employee) at the local, and you've found our code helpful, please buy us a round!
Distributed as-is; no warranty is given.

Example based off of demos by Brian Schmalz (designer of the Easy Driver).
http://www.schmalzhaus.com/EasyDriver/Examples/EasyDriverExamples.html
******************************************************************************/
//Declare pin functions on Redboard
#define stp 2
#define dir 3
#define MS1 4
#define MS2 5
#define EN  6
#define HOME_SWITCH   8 // Pin 8 connected to Home Switch (MicroSwitch)
#define BUTTON_PIN    9 // Pin 9 is connected to a button, that is always true. When pressed it goes to false

#define OPEN_DOOR_STEPS 30000

#define MICROSECONDS_DELAY 200

//Declare variables for functions
char user_input;
int x;
int y;
int state;

void setup() {
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(EN, OUTPUT);
  pinMode(HOME_SWITCH, INPUT_PULLUP);
  pinMode(BUTTON_PIN, INPUT_PULLUP);


  resetEDPins(); //Set step, direction, microstep and enable pins to default states
  Serial.begin(9600); //Open Serial connection for debugging
  Serial.println("Begin motor control");
  Serial.println();
  //Print function list for user selection
  Serial.println("Enter number for control option:");
  Serial.println("1. OpenDoor.");
  Serial.println("2. CloseDoor.");
  Serial.println();

  //we start with door closed as it is a known position
  delay(100);
  digitalWrite(EN, LOW); //Pull enable pin low to allow motor control
  CloseDoor();
}

//Main loop
void loop() {
  while (Serial.available()) {
      user_input = Serial.read(); //Read user input and trigger appropriate function
      digitalWrite(EN, LOW); //Pull enable pin low to allow motor control

      if (user_input =='1')
      {
         OpenDoor();
      }
      else if(user_input =='2')
      {
        CloseDoor();
      }
      else
      {
        Serial.println("Invalid option entered.");
      }
      resetEDPins();
  }
}

//Reset Easy Driver pins to default states
void resetEDPins()
{
  digitalWrite(stp, LOW);
  digitalWrite(dir, LOW);
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, LOW);
  digitalWrite(EN, HIGH);
}

//Default microstep mode function
void OpenDoor()
{
  Serial.println("Opening Door.");
  digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
  for(x= 1; x<OPEN_DOOR_STEPS; x++)  //Loop the forward till the door is open
  {
    digitalWrite(stp,HIGH); //Trigger one step forward
    delayMicroseconds(MICROSECONDS_DELAY);
    digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
    delayMicroseconds(MICROSECONDS_DELAY);
  }
  Serial.println("Enter new option");
  Serial.println();
}

/**
 * If the switch is disconnected or is pressed it will return true.
 * Otherwise it will return false.
 */
bool isDoorClosed(){
  return digitalRead(HOME_SWITCH);
}

bool isButtonPressed(){
  return !digitalRead(BUTTON_PIN);
}

//Reverse default microstep mode function
void CloseDoor()
{
  Serial.println("Closing Door. But was it closed?");
  Serial.println(isDoorClosed());
  digitalWrite(dir, HIGH); //Pull direction pin high to move in "reverse"
  while(!isDoorClosed())  //Loop the stepping while the limitin switch is not pressed
  {
      digitalWrite(stp,HIGH); //Trigger one step
      delayMicroseconds(MICROSECONDS_DELAY);
      digitalWrite(stp,LOW); //Pull step pin low so it can be triggered again
      delayMicroseconds(MICROSECONDS_DELAY);
  }
  Serial.println("Enter new option");
  Serial.println();
}
