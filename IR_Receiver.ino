/*
MIT License
Copyright 2021 Michael Schoeffler (https://www.mschoeffler.com)
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
/*
 * This is an example source code of a tutorial on how to do IR communication with the Arduino Uno. 
 * This program is for a receiving Arduino Uno that receives IR signals.
 */

#include <IRremote.h> // >v3.0.0
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
                                           
#define PIN_RECV 2

SoftwareSerial mySoftwareSerial(1, 0); // RX, TX, was 10,11 on UNO
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

void setup()  
{  
  Serial.begin(9600); //initialize serial connection to print on the Serial Monitor of the Arduino IDE
  IrReceiver.begin(PIN_RECV); // Initializes the IR receiver object
  mySoftwareSerial.begin(9600);

   
}  
                               
void loop()  
 
{  if (IrReceiver.decode()) {
    Serial.println("Receiveded");    
    IrReceiver.printIRResultShort(&Serial); // Prints a summary of the received data
    Serial.println();
    IrReceiver.resume(); // Important, enables to receive the next IR signal
  }
    if (IrReceiver.decode()){     
int value = results.value;     
Serial.println(value); 
        switch(value){     
        case 0x1: //Keypad button "1"     
        myDFPlayer.volume(10);  //Set volume value. From 0 to 30
        myDFPlayer.play(1);  //Play the first mp3
         
  }  }}


  
  
