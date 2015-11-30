// Created to operate with Android App communicating to Arduino
// via bluetooth. Requires an additional bluetooth chip to be 
// attached
#include <SoftwareSerial.h>
#include <Servo.h>

int bluetoothTx = 50;
int bluetoothRx = 51;
String temp = "";

Servo firstESC, secondESC, thirdESC, fourthESC, LED;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup()
{
  //Setup usb serial connection to computer
  Serial.begin(9600);
  Serial.println("bluetooth connection started");
  //Setup Bluetooth serial connection to android
  bluetooth.begin(9600);
  //Setup ESC connections to Arduino
  firstESC.attach(7);
  secondESC.attach(11);
  thirdESC.attach(10);
  fourthESC.attach(9);
  LED.attach(3);
  LED.writeMicroseconds(1);
}

void loop()
{
  //Read from bluetooth and write to usb serial
  if(bluetooth.available() > 0)
  {
    //Serial.println("entered here");
    char toSend = (char) bluetooth.read();
    if(toSend == 'n') {
      Serial.println(temp);
      int motor1 = (temp.substring(0,5)).toInt();
      int motor2 = (temp.substring(6,10)).toInt();
      int motor3 = (temp.substring(11,15)).toInt();
      int motor4 = (temp.substring(16,20)).toInt();
      //Serial.println(motor1);
      //Serial.println(motor2);
      //Serial.println(motor3);
      //Serial.println(motor4);
      firstESC.writeMicroseconds(motor1);
      secondESC.writeMicroseconds(motor2);
      thirdESC.writeMicroseconds(motor3);
      fourthESC.writeMicroseconds(motor4);
      LED.writeMicroseconds(motor1);
      temp = "";
    } else {
      temp += toSend; 
    }
    //Serial.println(temp);
    //Serial.println(toSend);
  }
}
