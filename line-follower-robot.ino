const int IR1_PIN = 15;
const int IR2_PIN = 16;
const int IR3_PIN = 17;
const int IR4_PIN = 18;

const int M1_PIN = 5;
const int M2_PIN = 6;
const int M3_PIN = 7;
const int M4_PIN = 8;

const bool STATE_OFF[] = {0, 0, 0, 0};
const bool STATE_FW[] = {0, 1, 0, 1};
const bool STATE_BW[] = {1, 0, 1, 0};
const bool STATE_LEFT[] = {0, 1, 1, 0};
const bool STATE_LEFT_LIGHT[] = {0, 1, 0, 0};
const bool STATE_RIGHT[] = {1, 0, 0, 1};
const bool STATE_RIGHT_LIGHT[] = {0, 0, 0, 1};

void setup() {
  Serial.begin(9600);

  pinMode(IR1_PIN, INPUT);
  pinMode(IR2_PIN, INPUT);
  pinMode(IR3_PIN, INPUT);
  pinMode(IR4_PIN, INPUT);

  pinMode(M1_PIN, OUTPUT);
  pinMode(M2_PIN, OUTPUT);
  pinMode(M3_PIN, OUTPUT);
  pinMode(M4_PIN, OUTPUT);

  activateMotorState(STATE_OFF);
  
  delay(15000);
}

void loop() {

  bool i1 = digitalRead(IR1_PIN);
  bool i2 = digitalRead(IR2_PIN);
  bool i3 = digitalRead(IR3_PIN);
  bool i4 = digitalRead(IR4_PIN);

  if (!i2 && !i3) {
    activateMotorState(STATE_FW);
  } else if (i2 && !i3) {
    activateMotorState(STATE_LEFT);
  } else if (!i2 && i3) {
    activateMotorState(STATE_RIGHT);
  } else if (!i1 && i2 && i3 && i4) {
    hardRight();
  }else if (i1 && !i2 && i3 && i4) {
    hardRight();
  } else if (i1 && i2 && i3 && !i4) {
    hardLeft();
  } else if (i1 && i2 && !i3 && i4) {
    hardLeft();
  } else if (!i1 && !i2 && !i3 && !i4) {
    activateMotorState(STATE_OFF);
  } else if (!i1 && i2 && i3 && !i4) {
    activateMotorState(STATE_FW);
  }
}

// [M1, M2, M3, M4]
void activateMotorState(bool states[]) {
  digitalWrite(M1_PIN, states[0]);
  digitalWrite(M2_PIN, states[1]);
  digitalWrite(M3_PIN, states[2]);
  digitalWrite(M4_PIN, states[3]);
}

void hardRight() {
  activateMotorState(STATE_RIGHT);
  delay(30);
  activateMotorState(STATE_RIGHT_LIGHT);
  delay(120);
  activateMotorState(STATE_OFF);
}

void hardLeft() {
  activateMotorState(STATE_LEFT);
  delay(30);
  activateMotorState(STATE_LEFT_LIGHT);
  delay(120);
  activateMotorState(STATE_OFF);
}