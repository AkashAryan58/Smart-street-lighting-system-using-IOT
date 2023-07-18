#define BLYNK_TEMPLATE_ID "TMPLZFMoSodf"
#define BLYNK_DEVICE_NAME "Street Light System"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "4zY-xJ5KZxq-js1sfYlvRoasMyXQ----";
char ssid[] = "Iphone";
char pass[] = "Vaibhav2";

int ledpin3 = D7;
int ledpin2 = D6;
int ledpin1 = D5;
int irsensor1 = D0;
int irsensor2 = D1;
int irsensor3 = D2;
int ldr = A0;
int valuel;//for ldr sensor value

WidgetLED Led1(V0);// Virtual Pin V0
WidgetLED LED2(V1);// Virtual Pin V1
WidgetLED LED3(V2);// Virtual Pin V2
WidgetLCD lcd(V7);
WidgetLCD lcd1(V8);

BlynkTimer timer;

void readl(){
  valuel = analogRead(ldr);
  Blynk.virtualWrite(V3,valuel);  
}


void sensor1(){

  int value = digitalRead(irsensor1);
  int value2 = digitalRead(irsensor2);
  int value3 = digitalRead(irsensor3);



  valuel = analogRead(ldr);
  if(valuel>=800)
  {
    lcd.print(0,0,"NIGHT TIME");
    if(value == LOW){
    Led1.on();
    digitalWrite(ledpin1,HIGH);
    lcd.print(0,1,"LIGHT 1 ON ");
  }
  else{
    Led1.off();
    digitalWrite(ledpin1,LOW);
    lcd.print(0,1,"LIGHT 1 OFF");

  }

    if(value2 == LOW){
    LED2.on();
    digitalWrite(ledpin2,HIGH);
    lcd1.print(0,0,"LIGHT 2 ON ");

  }
  else{
    LED2.off();
    digitalWrite(ledpin2,LOW);
    lcd1.print(0,0,"LIGHT 2 OFF");
  }
  
    if(value3 == LOW){
    LED3.on();
    digitalWrite(ledpin3,HIGH);
    lcd1.print(0,1,"LIGHT 3 ON ");

  }
  else{
    LED3.off();
    digitalWrite(ledpin3,LOW);
        lcd1.print(0,1,"LIGHT 3 OFF");

  }
  }
  else
  {
    Led1.off();
    digitalWrite(ledpin1,LOW);
    
    LED2.off();
    digitalWrite(ledpin2,LOW);
    
    LED3.off();
    digitalWrite(ledpin3,LOW);
    lcd.print(0,0,"DAY TIME  ");
    lcd.print(0,1,"LIGHT 1 OFF");
    lcd1.print(0,0,"LIGHT 2 OFF");
    lcd1.print(0,1,"LIGHT 3 OFF");
  }
}


void setup()
{
  pinMode(ledpin1,OUTPUT);
  pinMode(ledpin2,OUTPUT);
  pinMode(ledpin3,OUTPUT);
  pinMode(irsensor1,INPUT);
  pinMode(irsensor2,INPUT);
  pinMode(irsensor3,INPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(300L,sensor1);
  timer.setInterval(300L,readl);


}

void loop()
{
  Blynk.run();
  timer.run();
}