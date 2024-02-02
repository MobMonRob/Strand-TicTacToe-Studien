int FSR1;
int FSR2;
int FSR3;
int FSR4;
int FSR5;
int FSR6;
int FSR7;
int FSR8;
int FSR9;
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
int LED1 = 53;
int LED2 = 51;
int LED3 = 49;
int LED4 = 47;
int LED5 = 45;
int LED6 = 43;
int LED7 = 41;
int LED8 = 39;
int LED9 = 37;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
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

void loop() {
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
