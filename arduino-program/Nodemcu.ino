#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h> 

char auth[] = "<token key from blynk>";         //Key From Blynk
char ssid[] = "<wifi name>";                    //Wifi Name
char pass[] = "<wifi password>";                //Wifi Password


int val = 500;
int fwd_state=0, bwd_state=0, tr_state=0, tl_state=0;

BLYNK_CONNECTED(){
    Blynk.syncAll();
}
BLYNK_WRITE(V0){
  val = param.asInt();
}
BLYNK_WRITE(V1){
  fwd_state = param.asInt();
}
BLYNK_WRITE(V2){
  bwd_state = param.asInt();
}
BLYNK_WRITE(V3){
  tr_state = param.asInt();
}
BLYNK_WRITE(V4){
  tl_state = param.asInt();
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  
  pinMode(0, OUTPUT);       
  pinMode(2, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(15, OUTPUT);

}

void loop() {
  Blynk.run();
  if(fwd_state == 1 && bwd_state == 0 && tr_state == 0 && tl_state == 0){
    fwd();
  }
  else if(fwd_state == 0 && bwd_state == 1 && tr_state == 0 && tl_state == 0){
    bwd();
  }
  else if(fwd_state == 0 && bwd_state == 0 && tr_state == 1 && tl_state == 0){
    tr();
  }
  else if(fwd_state == 0 && bwd_state == 0 && tr_state == 0 && tl_state == 1){
    tl();
  }
  else if(fwd_state == 0 && bwd_state == 0 && tr_state == 0 && tl_state == 0){
    stop_m();
  }
  
  Serial.print(val); Serial.print(" ");
  Serial.print(fwd_state); Serial.print(" ");
  Serial.print(bwd_state); Serial.print(" ");
  Serial.print(tr_state); Serial.print(" ");
  Serial.print(tl_state); Serial.print(" ");
  Serial.println();
}

void bwd(){
  analogWrite(0, val);
  digitalWrite(2, LOW);
  digitalWrite(14, HIGH);

  analogWrite(15, val);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
}

void fwd(){
  analogWrite(0, val);
  digitalWrite(2, HIGH);
  digitalWrite(14, LOW);

  analogWrite(15, val);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
}

void tr(){
  analogWrite(0, val);
  digitalWrite(2, LOW);
  digitalWrite(14, HIGH);

  analogWrite(15, val);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
}

void tl(){
  analogWrite(0, val);
  digitalWrite(2, HIGH);
  digitalWrite(14, LOW);

  analogWrite(15, val);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
}
void stop_m(){
  analogWrite(0, 0);
  digitalWrite(2, LOW);
  digitalWrite(14, LOW);

  analogWrite(15, 0);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
}
