#define CH_STEER 2
#define CH_THROTTLE 4

#define IN1 9
#define IN2 8
#define IN3 7
#define IN4 6
#define ENA 3
#define ENB 11

void setup() {
  pinMode(CH_STEER, INPUT);
  pinMode(CH_THROTTLE, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int steer = pulseIn(CH_STEER, HIGH, 30000);     // CH1
  int throttle = pulseIn(CH_THROTTLE, HIGH, 30000); // CH2

  if (steer == 0 || throttle == 0) return;

  int speed = map(throttle, 1000, 2000, -255, 255);
  int turn = map(steer, 1000, 2000, -100, 100);

  int leftSpeed = speed - turn;
  int rightSpeed = speed + turn;

  leftSpeed = constrain(leftSpeed, -255, 255);
  rightSpeed = constrain(rightSpeed, -255, 255);

  if (leftSpeed >= 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    leftSpeed = -leftSpeed;
  }

  if (rightSpeed >= 0) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    rightSpeed = -rightSpeed;
  }

  analogWrite(ENA, leftSpeed);
  analogWrite(ENB, rightSpeed);

  Serial.print("Throttle: "); Serial.print(throttle);
  Serial.print(" | Steer: "); Serial.print(steer);
  Serial.print(" | Left: "); Serial.print(leftSpeed);
  Serial.print(" | Right: "); Serial.println(rightSpeed);

  delay(50);
}
