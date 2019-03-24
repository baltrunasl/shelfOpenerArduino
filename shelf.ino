/******************************************************************************
  Simple sketch to drive a bipolar stepper motor,
  using the Easy Driver (http://www.schmalzhaus.com/EasyDriver). 

  Based on SparkFun Easy Driver Basic Demo by 
  Toni Klopfenstein @ SparkFun Electronics
  https://github.com/sparkfun/Easy_Driver
  His example is based off of demos by Brian Schmalz (designer of the Easy Driver).
  http://www.schmalzhaus.com/EasyDriver/Examples/EasyDriverExamples.html

  Development environment specifics:
  Written in Arduino 1.8.9

  This code is beerware; I owe one for Toni :)
  Distributed as-is; no warranty is given.

******************************************************************************/
//Declare pin functions on Arduino
#define stp 2
#define dir 3
#define MS1 4
#define MS2 5
#define EN  6
#define home_switch   8 // Pin 8 connected to Home Switch (MicroSwitch)

#define OPEN_DOOR_STEPS 5000

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
  pinMode(home_switch, INPUT_PULLUP);

  resetEDPins(); //Set step, direction, microstep and enable pins to default states
  Serial.begin(9600); //Open Serial connection for debugging
  Serial.println("Begin motor control");
  Serial.println();
  //Print function list for user selection
  Serial.println("Enter number for control option:");
  Serial.println("1. OpenDoor.");
  Serial.println("2. CloseDoor.");
  Serial.println("3. Turn at 1/8th microstep mode.");
  Serial.println();

  //we start with door closed as it is a known position
  CloseDoor();
}

//Main loop
void loop() {
  while (Serial.available()) {
    user_input = Serial.read(); //Read user input and trigger appropriate function
    digitalWrite(EN, LOW); //Pull enable pin low to allow motor control
    if (user_input == '1')
    {
      OpenDoor();
    }
    else if (user_input == '2')
    {
      CloseDoor();
    }
    else if (user_input == '3')
    {
      SmallStepMode();
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
  Serial.println("Moving forward at default step mode.");
  digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
  for (x = 1; x < OPEN_DOOR_STEPS; x++) //Loop the forward till the door is open
  {
    digitalWrite(stp, HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp, LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
  Serial.println("Enter new option");
  Serial.println();
}

//Reverse default microstep mode function
void CloseDoor()
{
  Serial.println("Moving in reverse at default step mode.");
  digitalWrite(dir, HIGH); //Pull direction pin high to move in "reverse"
  while (digitalRead(home_switch)) //Loop the stepping while the limitin switch is not pressed
  {
    digitalWrite(stp, HIGH); //Trigger one step
    delay(1);
    digitalWrite(stp, LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
  Serial.println("Enter new option");
  Serial.println();
}

// 1/8th microstep foward mode function
void SmallStepMode()
{
  Serial.println("Stepping at 1/8th microstep mode.");
  digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
  digitalWrite(MS1, HIGH); //Pull MS1, and MS2 high to set logic to 1/8th microstep resolution
  digitalWrite(MS2, HIGH);
  for (x = 1; x < 1000; x++) //Loop the forward stepping enough times for motion to be visible
  {
    digitalWrite(stp, HIGH); //Trigger one step forward
    delay(1);
    digitalWrite(stp, LOW); //Pull step pin low so it can be triggered again
    delay(1);
  }
  Serial.println("Enter new option");
  Serial.println();
}
