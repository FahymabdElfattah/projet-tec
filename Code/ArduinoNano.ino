#include<SoftwareSerial.h>
int SiolPin = A1 , LDR = A0;
int const ContSys = 2 ,InPutPin = 4,pombPin = 3;
bool User ;
void setup() {
  Serial.begin(9600);
  for(int i =2;i <=3;i++){
    pinMode(i,OUTPUT);
    digitalWrite(i,LOW);
  }
  pinMode(InPutPin,INPUT);
}
void loop() {
  Serial.println(digitalRead(InPutPin));
  if(digitalRead(InPutPin)== HIGH){
    User = true ;
  }    
  if(digitalRead(InPutPin)== LOW){
     User = false ;
  }
  //analogRead(LDR)
  float Eclr = 200 ;
  if((Eclr <= 500 )||(Eclr > 500 && User == true )){
     digitalWrite(ContSys,HIGH);
     delay(100);
     int SensorValue = analogRead(SiolPin);   
     //float SensorVolts = SensorValue*0.0048828125; 
     float SensorVolts=0.2; 
    // Serial.print("SensorVolts = ");
     //Serial.println(SensorVolts);
     if(((SensorVolts > 1.03)||User == true)){
      digitalWrite(pombPin,HIGH);
      Serial.println("ON");
     }
        
     if(SensorVolts <= 1.03 && User == false ) {
          digitalWrite(pombPin,LOW); 
          Serial.println("OFF");
     }
      
  }
  if( Eclr > 500&& User == false){
    digitalWrite(ContSys,LOW);
    digitalWrite(pombPin,LOW);
    //Serial.print("STOP");
  }  
}
