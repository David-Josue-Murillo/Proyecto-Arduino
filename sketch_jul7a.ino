#include <LiquidCrystal.h>
#include <Servo.h>

int pir = 5;
int buzzer = 7;
int pinRojo = 23;
int pinAmarillo = 25;
int pinVerde = 27;
int echoPin = 13;
int trigPin = 12;
int servoPin = 11;
int numero = 0;

int pinTravelTime;
int i;

LiquidCrystal lcd(3,2,14,15,16,17);
Servo myServo;

void setup() {
  // put your setup code here, to INn once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pinRojo, OUTPUT);
  pinMode(pinAmarillo, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pir, INPUT);

  lcd.begin(16,2);
  myServo.attach(servoPin);
}

void loop() {
  //PIR
  int valor = digitalRead(pir);

  digitalWrite(pinRojo, HIGH);
  digitalWrite(pinAmarillo, LOW);
  digitalWrite(pinVerde, LOW);
  myServo.write(160);
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  pinTravelTime = pulseIn(echoPin, HIGH);
  delay(25);


  //LCD
  lcd.setCursor(4, 0);
  lcd.print("Welcome");

  lcd.setCursor(3, 1);
  lcd.print("My House");

  tone(buzzer,800,3000);
  delay(3000);

  if(pinTravelTime <= 650) {
      digitalWrite(pinRojo, LOW);
    for(i = 0; i < 4; i++){
      digitalWrite(pinAmarillo, HIGH);
      delay(500);
      digitalWrite(pinAmarillo, LOW);
    }
    digitalWrite(pinVerde, HIGH);
    myServo.write(60);
    delay(3000);
  }

  digitalWrite(trigPin, LOW);
  Serial.println(pinTravelTime);
  Serial.println(valor);
  delay(3000);
}
