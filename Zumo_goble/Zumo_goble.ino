/*********************************************************************
 * DFMobile GoBLE_APP
 *********************************************************************
 * This example is aimed to control DFMobile basic motion by APP GoBle
 * Created 2015-3-12
 * By Gavin
 * 
 * Button ID:
 * SWITCH_UP      -- 1
 * SWITCH_RIGHT   -- 2
 * SWITCH_DOWN    -- 3
 * SWITCH_LEFT    -- 4
 * SWITCH_SELECT  -- 5
 * SWITCH_START   -- 6
 ********************************************************************/
#include <ZumoMotors.h>
#include <ZumoBuzzer.h>

const int LCDdelay=10; // conservative, 2 actually works

#include "DFMobile.h"
#include "Metro.h"
// Speed is modified by mapping vlaue of GamePad Stick


//GoBle configuration library, help user to identify control button and stick on Gamepad
#include "GoBLE.h"
int joystickX, joystickY;
boolean buttonState1;
boolean buttonState2;
boolean buttonState3;
boolean buttonState4;
boolean buttonState5;
boolean buttonState6;
int LeftWheelSpeed;
int RightWheelSpeed;

int ledPin = 13;

ZumoMotors motors;
ZumoBuzzer buzzer;

#include <avr/pgmspace.h>  // this lets us refer to data in program space (i.e. flash)
// store this fugue in program space using the PROGMEM macro.  
// Later we will play it directly from program space, bypassing the need to load it 
// all into RAM first.
const char fugue[] PROGMEM = 
  "! O5 L16 agafaea dac+adaea fa<aa<bac#a dac#adaea f"
  "O6 dcd<b-d<ad<g d<f+d<gd<ad<b- d<dd<ed<f+d<g d<f+d<gd<ad"
  "L8 MS <b-d<b-d MLe-<ge-<g MSc<ac<a ML d<fd<f O5 MS b-gb-g"
  "ML >c#e>c#e MS afaf ML gc#gc# MS fdfd ML e<b-e<b-"
  "O6 L16ragafaea dac#adaea fa<aa<bac#a dac#adaea faeadaca"
  "<b-acadg<b-g egdgcg<b-g <ag<b-gcf<af dfcf<b-f<af"
  "<gf<af<b-e<ge c#e<b-e<ae<ge <fe<ge<ad<fd"
  "O5 e>ee>ef>df>d b->c#b->c#a>df>d e>ee>ef>df>d"
  "e>d>c#>db>d>c#b >c#agaegfe f O6 dc#dfdc#<b c#4";

void setup (){
  pinMode(ledPin,OUTPUT);
  Goble.begin();
  Serial.begin(115200);
  // uncomment one or both of the following lines if your motors' directions need to be flipped
//  motors.flipLeftMotor(true);
//  motors.flipRightMotor(true);

  
}

void loop (){
  if(Goble.available()){
    joystickX = Goble.readJoystickX();  
    joystickY = Goble.readJoystickY();
    Serial.print("joystickX: ");
    Serial.print(joystickX);
    Serial.print("joystickY: ");
    Serial.println(joystickX);

    buttonState1    = Goble.readSwitchUp();
    buttonState2   = Goble.readSwitchLeft();
    buttonState3  = Goble.readSwitchRight();
    buttonState4   = Goble.readSwitchDown();
    buttonState5 = Goble.readSwitchSelect();
    buttonState6  = Goble.readSwitchStart();

    Serial.print("Joystick Value: ");
    Serial.print(joystickX);
    Serial.print("  ");
    Serial.print(joystickY);
    Serial.println("  ");

    //enable to map the value from (1~255) to (-255~255)
    int SpeedX=2*joystickX-256;
    int SpeedY=2*joystickY-256;

    LeftWheelSpeed = 0;
    RightWheelSpeed = 0;
 
    if (SpeedX>100 || SpeedX<-100 || SpeedY>100 || SpeedY<-100){           //when joystick X is pushed up
      LeftWheelSpeed=SpeedX+SpeedY;                 
      RightWheelSpeed=SpeedX-SpeedY;
    }         
    
    motors.setLeftSpeed(LeftWheelSpeed);
    motors.setRightSpeed(RightWheelSpeed);
    
    if (buttonState1 == PRESSED){
        digitalWrite(ledPin,HIGH);
        buzzer.playFromProgramSpace(fugue);  
    }
    if (buttonState1 == RELEASED){
        digitalWrite(ledPin,LOW);
    }
    if (buttonState2 == PRESSED){
        digitalWrite(ledPin,HIGH);
        buzzer.stopPlaying();
    }
  }
}



