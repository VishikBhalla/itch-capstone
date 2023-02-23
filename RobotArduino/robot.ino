const int analogPin = A0; // set analog input pin
int sensorValue = 0; // variable to store sensor value
float resistance = 0.0; // variable to store calculated resistance

//Struct containing resistance, command type and command
typedef struct { 
  uint8_t resistance;
  char* type;
  char* movement;
} robotDict;

const robotDict robotDictArr[]
    {0, "statement+argument", "Rotate"},
    {100, "argument", "1"},
    {200, "argument", "2"},
    {300, "argument", "3"},
    {400, "argument", "4"},
    {500, "statement+argument", "repeat x times"},
    {1000, "statement+argument", "move forward x"},
    {1500, "statement+argument", "move backward x"},
    {2000, "statement+argument", "if x then do"},
    {2500, "statement+argument", "until x do"},
    {4000, "statement", "stop"},
    {5000, "statement", "hook up"},
    {6000, "statement", "hook down"},
    {7000, "statement", "otherwise do"},
    {8000, "statement", "forever do"},
    {9000, "statement", "}"}
    
    
};

void setup() {
  Serial.begin(9600); // initialize serial communication
  
}

void loop() {
  sensorValue = analogRead(analogPin); // read analog input value
  resistance = ((float)sensorValue / 1023.0) * 10000.0; // calculate resistance in ohms
  if(resistance > 9000) {
    //send rotation command to robot
  }
  for(uint8_t i = 0; i < sizeof(robotDictArr)/sizeof(robotDict); ++i) {
      if(myDictionaryArr[i].resistance == resistance){
        //send myDictionaryArr[i].type and movement to robot
      }
      
  }
  delay(1000); // wait for a second before reading again
}
