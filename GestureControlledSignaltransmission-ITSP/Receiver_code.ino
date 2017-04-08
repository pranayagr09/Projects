#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
#include<Servo.h>

typedef struct{
  int yaw;
  int pitch;
  int roll;
  int throttle;
}
Quad_R;

int yaw_old=0;
int pitch_old=0;
int roll_old=0;
int throttle_old=0;
int yaw_transmit=0;
int pitch_transmit=0;
int roll_transmit=0;
int throttle_transmit=0;
int i=0;
int j=1;
int m=j;
//i,j and m are variables defined so as to calibrate flightmode in OpenPilot software as it will not detect it otherwise
 
Quad_R reading ;
RF24 radio(7,8);
const uint64_t pipe = 0xE8E8F0F0E1LL;
Servo yaw;
Servo pitch;
Servo roll;
Servo throttle;
Servo Flightmode;


void setup(void){
  yaw.attach(3);//gives PWM output of yaw of Servo type on pin 3
  pitch.attach(5);//gives PWM output of pitch of Servo type on pin 5
  roll.attach(6);//gives PWM output of roll of Servo type on pin 6
  throttle.attach(9);//gives PWM output of throttle of Servo type on pin 9
  Flightmode.attach(10);//gives PWM output of flightmode of Servo type on pin 10
  Serial.begin(115200);
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
}

 
void loop(void){
  if (radio.available()){
    bool done=false;
    while(!done){
      i++;
      radio.read(&reading,sizeof(reading));//data received at receiver as a struct
     
      if(reading.yaw>=0){
         reading.yaw=reading.yaw/10;
         reading.yaw=reading.yaw*10;
      }
      else{
        reading.yaw=reading.yaw/10;
        reading.yaw=reading.yaw*10-10;
        
      }
      if(reading.pitch>=0){
         reading.pitch=reading.pitch/10;
         reading.pitch=reading.pitch*10;
      }
      else{
        reading.pitch=reading.pitch/10;
        reading.pitch=reading.pitch*10-10;
        
      }
      if(reading.roll>=0){
         reading.roll=reading.roll/10;
         reading.roll=reading.roll*10;
      }
      else{
        reading.roll=reading.roll/10;
        reading.roll=reading.roll*10-10;
        
      }
      reading.throttle=reading.throttle/10;
      reading.throttle=reading.throttle*10;
     //the procedure above converts the reading of yaw, pitch, roll and throttle in multiples of 10
      
      if(reading.throttle!=0 && abs(reading.yaw-yaw_old)<=20 && abs(reading.pitch-pitch_old)<=20 && abs(reading.roll-roll_old)<=20){
        yaw_old=reading.yaw;
        pitch_old=reading.pitch;
        roll_old=reading.roll;
        throttle_old=reading.throttle;
      }
      //this is done to avoid fluctuations in readings as in that case it will take the previous reading 
      
      Serial.print(yaw_old);                     
      Serial.print("\t");
      Serial.print(pitch_old);
      Serial.print("\t");
      Serial.print(roll_old);
      Serial.print("\t");
      Serial.print(throttle_old);
      Serial.println("\t");
      
      yaw_transmit=yaw_old;
      roll_transmit=roll_old;
      pitch_transmit=pitch_old;
      throttle_transmit=throttle_old;
      //this assignment is done to ensure that the values don`t get affected as map and constrain functions in Servo library  can change them and could result in junk values

      //Constraints setup
      yaw_transmit=constrain(yaw_transmit,-60,60);
      pitch_transmit=constrain(pitch_transmit,-80,80);
      roll_transmit=constrain(roll_transmit,-90,90);
      throttle_transmit=constrain(throttle_transmit,825,915);

      //Mapping for Servo
      yaw_transmit=map(yaw_transmit,-60,60,0,180);
      pitch_transmit=map(pitch_transmit,-80,80,0,180);
      roll_transmit=map(roll_transmit,-90,90,0,180);
      throttle_transmit=map(throttle_transmit,825,915,0,180);
      
      //Flight Mode PWM Output 
      m=j;
      m=map(m,1,3,0,180);
      if((i/10)%2 == 0)
      {
        if(j==3) j=1;
        else j++;
      }
      else 
      {
        j=2;
      }
      Serial.println(j);
      Serial.println("\t");
      
      //Witing data on Servo Variables
      yaw.write(yaw_transmit);
      pitch.write(pitch_transmit);
      roll.write(roll_transmit);
      throttle.write(throttle_transmit);
      Flightmode.write(m);
      
      delay(100);//done so as to match the frequency of data being transmitted and received
    }
  }
}
