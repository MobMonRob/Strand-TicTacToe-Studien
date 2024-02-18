#include <Braccio.h>
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

String data = "";

void setup() {
  Braccio.begin();
  Serial.begin(9600);
}

void loop() {
  while (Serial.available() > 0) {
    char receivedChar = Serial.read();

    // Check if the received character is 'A'
    if (receivedChar == 'A') {
      // If it's 'A', print the previous data and split it
      splitAndPrintData(data);

      // Reset the data string
      data = "";
    } else {
      // Otherwise, add the character to the current data
      data += receivedChar;
    }
  }
}

void splitAndPrintData(String inputString) {
  String values[5];    // Create an array to store the split values
  int valueCount = 0;  // Counter for the number of split values
  int startIndex = 0;  // Start index for searching the delimiter

  while (startIndex >= 0 && valueCount < 5) {
    int endIndex = inputString.indexOf(',', startIndex + 1);  // Find the next comma

    if (endIndex >= 0) {
      // Extract the substring between the start and end indexes
      values[valueCount] = inputString.substring(startIndex + 1, endIndex);
    } else {
      // If no more commas are found, extract the remaining string
      values[valueCount] = inputString.substring(startIndex + 1);
    }

    // Move the start index to the character after the last comma found
    startIndex = endIndex;

    // Increment the value count
    valueCount++;
  }
  /*
    Serial.print(values[0]);
    Serial.print(",");
    Serial.print(values[1]);
    Serial.print(",");
    Serial.print(values[2]);
    Serial.print(",");
    Serial.print(values[3]);
    Serial.print(",");
    Serial.print(values[4]);
    Serial.print(",");
    Serial.print(values[5]);
    Serial.println("");
  */
  int M1 = values[0].toInt();
  int M2 = values[1].toInt();
  int M3 = values[2].toInt();
  int M4 = values[3].toInt();
  int M5 = values[4].toInt();
  Controller(M1, M2, M3, M4, M5);
}

void Controller(int M1, int M2, int M3, int M4, int M5) {
  Serial.print("M1:");
  Serial.print(M1);
  Serial.print(",");
  Serial.print("M2:");
  Serial.print(M2);
  Serial.print(",");
  Serial.print("M3:");
  Serial.print(M3);
  Serial.print(",");
  Serial.print("M4:");
  Serial.print(M4);
  Serial.print(",");
  Serial.print("M5:");
  Serial.print(M5);
  Serial.println("");
  if (M1 >= 0 && M2 >= 15 && M3 >= 0 && M4 >= 0 && M5 >= 50) {
    Braccio.ServoMovement(20, M1, M2, M3, M4, M5, 0);
   delay(50);

  }
}
