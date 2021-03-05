#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "Pz-sDCrbJs4bTWu8cYCj8s0tvZfVgoGY";
char ssid[]= "aakash";
char pass[]= "147147147";

int irPin1=5;
int irPin2=4;
int buzzer = D0;
int ledPin = D7;
int count=0;

boolean state1 = true;
boolean state2 = true;
boolean insideState = false;
boolean outsideIr=false;
boolean isPeopleExiting=false;
int i=1;

void setup() {

  Blynk.begin(auth, ssid, pass);  // Connection with Blynk server
  Blynk.notify("Your System is ready to use.");
pinMode(irPin1, INPUT);
pinMode(irPin2, INPUT);
pinMode (buzzer, OUTPUT);
pinMode (ledPin, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  Blynk.run();
  if (!digitalRead(irPin1) && i==1 && state1){
     outsideIr=true;
     delay(100);
     i++;
     state1 = false;
  }
   if (!digitalRead(irPin2) && i==2 &&   state2){
     Serial.println("Entering into room");
     outsideIr=true;
     delay(100);
     
     i = 1 ;
     count++;
     digitalWrite(ledPin, HIGH);
     delay(1000);
     digitalWrite(ledPin, LOW);
     digitalWrite(buzzer,HIGH);
     delay(1000);
       digitalWrite(buzzer,LOW); 
     Serial.print("No of persons inside the room: ");
     Serial.println(count);
     state2 = false;
  }

   if (!digitalRead(irPin2) && i==1 && state2 ){
     outsideIr=true;
     delay(100);
     i = 2 ;
     state2 = false;
  }

  if (!digitalRead(irPin1) && i==2 && state1 ){
     Serial.println("Exiting from room");
     outsideIr=true;
     delay(100);
     count--;
     digitalWrite(ledPin, HIGH);
     delay(500);
     digitalWrite(ledPin, LOW);
     delay(500);
     digitalWrite(ledPin, HIGH);
     delay(500);
     digitalWrite(ledPin, LOW);
      digitalWrite(buzzer,HIGH);
     delay(500);
       digitalWrite(buzzer,LOW); 
        delay(500);
       digitalWrite(buzzer,HIGH); 
        delay(500);
       digitalWrite(buzzer,LOW); 
       
       Serial.print("No of persons inside the room: ");
       Serial.println(count);
     i = 1;
     state1 = false;
  }  
    if (digitalRead(irPin1)){
     state1 = true;
    }
     if (digitalRead(irPin2)){
     state2 = true;
    }
     Blynk.virtualWrite(V0, count); 
}
