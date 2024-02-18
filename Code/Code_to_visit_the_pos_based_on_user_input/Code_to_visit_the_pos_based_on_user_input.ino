#include <Braccio.h>
#include <Servo.h>


int FSR1;
int FSR2;
int FSR3;
int FSR4;
int FSR5;
int FSR6;
int FSR7;
int FSR8;
int FSR9;

int steps = 0;
int LED1 = 53;
int LED2 = 51;
int LED3 = 49;
int LED4 = 47;
int LED5 = 45;
int LED6 = 43;
int LED7 = 41;
int LED8 = 39;
int LED9 = 37;
int THRESHOLD = 0;


bool ObjectAbove1 = false;
bool ObjectAbove2 = false;
bool ObjectAbove3 = false;
bool ObjectAbove4 = false;
bool ObjectAbove5 = false;
bool ObjectAbove6 = false;
bool ObjectAbove7 = false;
bool ObjectAbove8 = false;
bool ObjectAbove9 = false;
bool start = true;

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

int pos1[][5] = {
  {69, 90, 90, 90, 100},
  {69, 90, 15, 90, 100},
  {69, 90, 15, 10, 100},
  {69, 70, 15, 10, 90},
  {69, 90, 15, 10, 90},
  {69, 90, 15, 90, 90},
  {69, 90, 90, 90, 90}
};

int pos2[][5] = {
  {50, 90, 90, 90, 100},
  {50, 90, 10, 90, 100},
  {50, 90, 10, 10, 100},
  {50, 75, 10, 10, 90},
  {50, 90, 10, 10, 90},
  {50, 80, 10, 90, 90},
  {50, 80, 90, 90, 90}
};

int pos3[][5] = {
  {20, 90, 90, 90, 100},
  {20, 90,  10, 90, 100},
  {20, 90,  10,  5, 100},
  {20, 65,  10,  5, 90},
  {20, 90,  10,  5, 90},
  {20, 90,  10, 90, 90},
  {20, 90, 90, 90, 90}
};

int pos4[][5] = {
  {60, 90, 90, 90, 100},
  {60, 90, 30, 90, 100},
  {60, 90, 30, 20, 100},
  {60, 55, 30, 20, 90},
  {60, 90, 30, 20, 90},
  {60, 90, 30, 90, 90},
  {60, 90, 90, 90, 90}
};

int pos5[][5] = {
  {40, 90, 90, 90, 100},
  {40, 90, 20, 90, 100},
  {40, 90, 20, 20, 100},
  {40, 60, 20, 20, 90},
  {40, 90, 20, 20, 90},
  {40, 90, 20, 90, 90},
  {40, 90, 90, 90, 90}
};

int pos6[][5] = {
  {22, 90, 90, 90, 100},
  {22, 90, 15, 90, 100},
  {22, 90, 15, 25, 100},
  {22, 60, 15, 25, 90},
  {22, 90, 15, 25, 90},
  {22, 90, 15, 90, 90},
  {22, 90, 90, 90, 90}
};

int pos7[][5] = {
  {58, 90, 90, 90, 100},
  {58, 90, 35, 90, 100},
  {58, 90, 35, 35, 100},
  {58, 45, 35, 35, 90},
  {58, 90, 35, 35, 90},
  {58, 90, 35, 90, 90},
  {58, 90, 90, 90, 90}
};

int pos8[][5] = {
  {43, 90, 90, 90, 100},
  {43, 90, 30, 90, 100},
  {43, 90, 30, 30, 100},
  {43, 50, 30, 30, 90},
  {43, 90, 30, 30, 90},
  {43, 90, 30, 90, 90},
  {43, 90, 90, 90, 90}
};

int pos9[][5] = {
  {22, 90, 90, 90, 100},
  {22, 90, 30, 90, 100},
  {22, 90, 30, 35, 100},
  {22, 45, 30, 35, 90},
  {22, 90, 30, 35, 90},
  {22, 90, 30, 90, 90},
  {22, 90, 90, 90, 90}
};

void setup() {
  Serial.begin(9600);
  Braccio.begin();
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED8, OUTPUT);
  pinMode(LED9, OUTPUT);
}

void MoveInit()
{
  Braccio.ServoMovement(20, 45, 90, 90, 90, 90, 0);
  Braccio.ServoMovement(20, 0, 90, 90, 90, 90, 0);
  Braccio.ServoMovement(20, 45, 90, 90, 90, 90, 0);
}


void MoveController(int pos)
{
  if (pos == 0) {
    MoveInit();
  }
  if (pos == 1) {
    for (int i = 0; i < 7; i++) {
      Braccio.ServoMovement(20, pos1[i][0], pos1[i][1], pos1[i][2], pos1[i][3], pos1[i][4], 0);
      checkSensor();
    }

    MoveInit();
  }
  if (pos == 2) {
    for (int i = 0; i < 7; i++) {
      Braccio.ServoMovement(20, pos2[i][0], pos2[i][1], pos2[i][2], pos2[i][3], pos2[i][4], 0);
      checkSensor();
    }
    MoveInit();
  }
  if (pos == 3) {
    for (int i = 0; i < 7; i++) {
      Braccio.ServoMovement(20, pos3[i][0], pos3[i][1], pos3[i][2], pos3[i][3], pos3[i][4], 0);
       checkSensor();
    }
    MoveInit();
  }
  if (pos == 4) {
    for (int i = 0; i < 7; i++) {
      Braccio.ServoMovement(20, pos4[i][0], pos4[i][1], pos4[i][2], pos4[i][3], pos4[i][4], 0);
      checkSensor();
    }
    MoveInit();
  }
  if (pos == 5) {
    for (int i = 0; i < 7; i++) {
      Braccio.ServoMovement(20, pos5[i][0], pos5[i][1], pos5[i][2], pos5[i][3], pos5[i][4], 0);
      checkSensor();
    }
    MoveInit();
  }
  if (pos == 6) {
    for (int i = 0; i < 7; i++) {
      Braccio.ServoMovement(20, pos6[i][0], pos6[i][1], pos6[i][2], pos6[i][3], pos6[i][4], 0);
      checkSensor();
    }
    MoveInit();
  }
  if (pos == 7) {
    for (int i = 0; i < 7; i++) {
      Braccio.ServoMovement(20, pos7[i][0], pos7[i][1], pos7[i][2], pos7[i][3], pos7[i][4], 0);
      checkSensor();
    }
    MoveInit();
  }
  if (pos == 8) {
    for (int i = 0; i < 7; i++) {
      Braccio.ServoMovement(20, pos8[i][0], pos8[i][1], pos8[i][2], pos8[i][3], pos8[i][4], 0);
      checkSensor();
    }
    MoveInit();
  }
  if (pos == 9) {
    for (int i = 0; i < 7; i++) {
      Braccio.ServoMovement(20, pos9[i][0], pos9[i][1], pos9[i][2], pos9[i][3], pos9[i][4], 0);
      checkSensor();
    }
    MoveInit();
  }
}

void checkSensor()
{
  FSR1 = 1023 - analogRead(A10);
  FSR2 = 1023 - analogRead(A9);
  FSR3 = 1023 - analogRead(A8);
  FSR4 = 1023 - analogRead(A5);
  FSR5 = 1023 - analogRead(A4);
  FSR6 = 1023 - analogRead(A3);
  FSR7 = 1023 - analogRead(A2);
  FSR8 = 1023 - analogRead(A1);
  FSR9 = 1023 - analogRead(A0);

  if (FSR1 > THRESHOLD && !ObjectAbove1) {
    Serial.println(">> just visit the position : 1");
    ObjectAbove1 = true;
    digitalWrite(LED1, HIGH);
  }

  if (FSR2 > THRESHOLD && !ObjectAbove2) {
    Serial.println(">> just visit the position : 2");
    ObjectAbove2 = true;
    digitalWrite(LED2, HIGH);

  }

  if (FSR3 > THRESHOLD && !ObjectAbove3) {
    Serial.println(">> just visit the position : 3");
    ObjectAbove3 = true;
    digitalWrite(LED3, HIGH);

  }
  if (FSR4 > THRESHOLD && !ObjectAbove4) {
    Serial.println(">> just visit the position : 4");
    ObjectAbove4 = true;
    digitalWrite(LED4, HIGH);

  }

  if (FSR5 > THRESHOLD && !ObjectAbove5) {
    Serial.println(">> just visit the position : 5");
    ObjectAbove5 = true;
    digitalWrite(LED5, HIGH);

  }

  if (FSR6 > THRESHOLD && !ObjectAbove6) {
    Serial.println(">> just visit the position : 6");
    ObjectAbove6 = true;
    digitalWrite(LED6, HIGH);
  }

  if (FSR7 > THRESHOLD && !ObjectAbove7) {
    Serial.println(">> just visit the position : 7");
    ObjectAbove7 = true;
    digitalWrite(LED7, HIGH);

  }

  
  if (FSR8 > THRESHOLD && !ObjectAbove8) {
    Serial.println(">> just visit the position : 8");
    ObjectAbove8 = true;
    digitalWrite(LED8, HIGH);

  }
  if (FSR9 > THRESHOLD && !ObjectAbove9) {
    Serial.println(">> just visit the position : 9");
    ObjectAbove9 = true;
    digitalWrite(LED9, HIGH);
  }

}

int getUserInput() {
  Serial.println("Enter the position you want to visit (1-9): ");
  while (Serial.available() == 0) {
    // Wait for user input
  }

  int selectedPosition = Serial.parseInt(); // Read the user input as an integer
  Serial.read(); // Clear the serial buffer

  // Return the selected position if it's valid
  if (selectedPosition >= 1 && selectedPosition <= 9) {
    Serial.println("Visiting Position: " + String(selectedPosition));
    return selectedPosition;
  } else {
    // If the input is not valid, return a special value (e.g., -1) to indicate an error
    Serial.println("Invalid input. Please enter a number between 1 and 9.");
    return -1;
  }
}

void loop() {


  if (start == true)
  {
    Serial.println("Ready");
    start = false;
    MoveInit();
  }

  int input = getUserInput();
  MoveController(input);
}
