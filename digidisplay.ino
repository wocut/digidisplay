// Include the AccelStepper Library
#include <AccelStepper.h>
#include <Bounce2.h>  

// Define pin connections
const int dirPin = 5;
const int stepPin = 6;
const int BUTTON_PIN = 12;//按钮连接的针脚
Bounce2::Button button = Bounce2::Button();//实例化一个抖动对象
int ledState = LOW;

const int ledPin = 13;    // the number of the LED pin

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
  digitalWrite(LED_BUILTIN, HIGH);  
  //pinMode(KEY_L,INPUT_PULLUP);  
  //attachInterrupt(0, myStepperRun, RISING);   // 上升沿触发中断 0，调用 testProgram 函数

  button.attach( BUTTON_PIN, INPUT_PULLUP);
  button.interval(5);//间隔是5ms

  myStepper.setMaxSpeed(400);
	myStepper.setAcceleration(400);
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
  //int display_potVal;  
  
  disp(potVal);
    button.update();//更新
  if ( button.pressed() ) 
  {
  ledState = !ledState ;    
  digitalWrite(ledPin, ledState);
  Serial.println(ledState);
  Serial.println(potVal);
  myStepper.setSpeed(potVal); 
  myStepper.setMaxSpeed(potVal); 
  myStepper.setAcceleration(potVal);   
  
  
   //myStepper.runToNewPosition(1600);
   //myStepper.runToNewPosition(0);

   //myStepper.runToNewPosition(1600);
   
    myStepper.move(1600);
    myStepper.runToPosition();
  }
  	
    


    // if (abs(display_potVal-potVal)>2)
    // {
    //   display_potVal=potVal;
      
    // }
    
  
}

