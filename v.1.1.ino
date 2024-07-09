#include <LiquidCrystal.h>
#include <Servo.h>

int led_pir = 43;
int pir = 41;
int valorPIR = 0;

int valorLDR = 0;
int led_1 = 46;
int led_2 = 48;
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
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(pir, INPUT);
  pinMode(led_pir, INPUT);

  lcd.begin(16,2);
  myServo.attach(servoPin);
}

void loop() {
  //LDR - FOTORESISTENCIA
  valorLDR = analogRead(A1);
  Serial.print("Valor de la fotoresistencia: ");
  Serial.println(valorLDR);

  // Luces de compuertas - Garage
  digitalWrite(pinRojo, HIGH);
  digitalWrite(pinAmarillo, LOW);
  digitalWrite(pinVerde, LOW);
  
  // Posicion del servo motor
  myServo.write(160);
  
  // Sensor ultrasonico
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  pinTravelTime = pulseIn(echoPin, HIGH);
  delay(25);

  //LCD
  lcd.setCursor(4, 0);
  lcd.print("Welcome");

  lcd.setCursor(3, 1);
  lcd.print("My House");

  // Buzzer
  tone(buzzer,800,3000);

  // Sensor de aproximidad y servoMotor
  if(pinTravelTime <= 650) {
      digitalWrite(pinRojo, LOW); // No hay objeto al frente - led rojo encendido
    for(i = 0; i < 4; i++){
      digitalWrite(pinAmarillo, HIGH); // Advertencia de que se va abrir el garage
      delay(500);
      digitalWrite(pinAmarillo, LOW);
    }
    digitalWrite(pinVerde, HIGH); // Garage abierto
    myServo.write(60);
    delay(3000); // Tiempo en que el garage permanecera abierto
  }
  
  digitalWrite(trigPin, LOW);
  Serial.print("Valor del Soud: ");
  Serial.println(pinTravelTime);

  // FOTORESISTENCIA
  if(valorLDR >= 999){
    // Encendiendo led si hay poca luz
    digitalWrite(led_1, HIGH);
    digitalWrite(led_2, HIGH);
    delay(5000);
  }

  // Apagando leds si hay luz
  digitalWrite(led_1, LOW);
  digitalWrite(led_2, LOW);

  
  //PIR SENSOR
  valorPIR = digitalRead(pir);
  Serial.print("Valor del sensor PIR: ");
  Serial.println(valorPIR);

  if(valorPIR) {
    digitalWrite(led_pir, HIGH);
    Serial.println("Encendido... Hay Movimientos....");
    delay(2000);
  }

  digitalWrite(led_pir, LOW);
}
