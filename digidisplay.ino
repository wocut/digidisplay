//电位器调节速度   120
//吐丝速度         80
//焊机电流         80

// Include the AccelStepper Library
#include <AccelStepper.h>
#include <Bounce2.h>  
// Define pin connections
int welding_flag = 0;
const int dirPin = 5;
const int stepPin = 6;
const int BUTTON_PIN = 12;//按钮连接的针脚
int Button_val = 0;

Bounce2::Button button = Bounce2::Button();//实例化一个抖动对象
int ledState = LOW;
const int ledPin = 13;    // the number of the LED pin
const int weldPin = 7;    //焊机针脚
const int feedPin = 8;    //吐丝机针脚
int clockPin=11;
int latchPin=10;
int dataPin=9;
unsigned char num[]={0xC0, //"0"
                     0xF9, //"1"
                     0xA4, //"2"
                     0xB0, //"3"
                     0x99, //"4"
                     0x92, //"5"
                     0x82, //"6"
                     0xF8, //"7"
                     0x80, //"8"
                     0x90  //"9"
};
const int potPin=A0; //设置电位器模块的连接引脚为A0
// Define motor interface type
#define motorInterfaceType 1
// Creates an instance
AccelStepper myStepper(motorInterfaceType, stepPin, dirPin);
int buttonState = 0;  // variable for reading the pushbutton status
void setup(){
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(weldPin,OUTPUT);
  pinMode(feedPin,OUTPUT);
  pinMode(BUTTON_PIN,INPUT);
  
  digitalWrite(LED_BUILTIN, HIGH);  

  
  button.attach( BUTTON_PIN, INPUT_PULLUP);
  button.interval(5);//间隔是5ms
  myStepper.setMaxSpeed(400);
  myStepper.setAcceleration(800);
  myStepper.setSpeed(400);
  Serial.begin(9600);//用于串口输出
  }
  
void disp(int n){
  int t=3;
  int ge=(int)n%10;
  int shi=((int)n/10)%10;
  int bai=((int)n/100)%10;
  int qian=((int)n/1000)%10;
  shiftOut(dataPin,clockPin,MSBFIRST,num[ge]);  
  shiftOut(dataPin,clockPin,MSBFIRST,0b00000001); 
  digitalWrite(latchPin, HIGH);
  delay(t);
  digitalWrite(latchPin,LOW);
  shiftOut(dataPin,clockPin,MSBFIRST,num[shi]);  
  shiftOut(dataPin,clockPin,MSBFIRST,0b00000010); 
  digitalWrite(latchPin, HIGH);
  delay(t);
  digitalWrite(latchPin,LOW);
  shiftOut(dataPin,clockPin,MSBFIRST,num[bai]);  
  shiftOut(dataPin,clockPin,MSBFIRST,0b00000100); 
  digitalWrite(latchPin, HIGH);
  delay(t);
  digitalWrite(latchPin,LOW);
  shiftOut(dataPin,clockPin,MSBFIRST,num[qian]);  
  shiftOut(dataPin,clockPin,MSBFIRST,0b00001000); 
  digitalWrite(latchPin, HIGH);
  delay(t);
  digitalWrite(latchPin,LOW);
}

void loop(){
  int potVal =analogRead(potPin); //从A0引脚读取模拟值
  int display_potVal;  
   if (abs(display_potVal-potVal)>1)
   {
     display_potVal=potVal;
   }
  disp(display_potVal);
  
//
//button.update();
//    if (button.pressed()){
//      welding_flag ==1;
//      welding(int display_potVal);
//    }

//if (welding_flag == 1){
//  welding(display_potVal);
//  //welding_flag == 0;
//}

//if (button.fell()){
//  digitalWrite(ledPin, LOW);
//  //myStepper.stop();
//}

//if (Button_val ==0)
//{
//  
//  //myStepper.run();  
//  myStepper.moveTo(1000);
//  myStepper.runSpeedToPosition();
//}
//else {
//  digitalWrite(ledPin, LOW);
//}


  
  button.update();//更新 
  if ( button.pressed() ) 
  {
    ledState = !ledState ;    
    digitalWrite(ledPin, HIGH);
    digitalWrite(weldPin, HIGH);
    digitalWrite(feedPin, HIGH);
    myStepper.setAcceleration(display_potVal);   
    myStepper.move(4200);
    myStepper.runToPosition();
    digitalWrite(ledPin, LOW);
    digitalWrite(feedPin, LOW);
    delay(100);
    digitalWrite(weldPin, LOW);
  }

}

void welding(int display_potVal){
        digitalWrite(ledPin, HIGH);
      Button_val = digitalRead(BUTTON_PIN);
      myStepper.setSpeed(display_potVal);
      myStepper.move(4200);
      myStepper.runToPosition();
      digitalWrite(ledPin, LOW);
  //welding_flag == 0;
}
