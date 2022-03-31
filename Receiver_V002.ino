/***************************************************
DFPlayer - A Mini MP3 Player For Arduino
 <https://www.dfrobot.com/product-1121.html>
 
 ***************************************************
 This example shows the basic function of library for DFPlayer.
 
 Created 2016-12-07
 By [Angelo qiao](Angelo.qiao@dfrobot.com)
 
 GNU Lesser General Public License.
 See <http://www.gnu.org/licenses/> for details.
 All above must be included in any redistribution
 ****************************************************/

/***********Notice and Trouble shooting***************
 1.Connection and Diagram can be found here
 <https://www.dfrobot.com/wiki/index.php/DFPlayer_Mini_SKU:DFR0299#Connection_Diagram>
 2.This code is tested on Arduino Uno, Leonardo, Mega boards.
 ****************************************************/

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <IRremote.h> //This line includes the library

/* HERHAAL HET STUK HIERONDER VOOR ALLE IR ONTVANGERS */
IRrecv irrecv2(13); //This line tells the Arduino to which pin the IR-receiver is connected
decode_results results2; //results2 is a variable to store the incoming message in
/*---------------------------------------------------*/

SoftwareSerial mySoftwareSerial(11, 12); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

long unsigned int lasttrackchange = 0;
int lastreceive=0;
void printDetail(uint8_t type, int value);
void setup()
{
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);
  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
  
  
  /* HERHAAL HET STUK HIERONDER VOOR ALLE IR ONTVANGERS */
  irrecv2.enableIRIn(); // This line starts the receiver.
  /*---------------------------------------------------*/
}

void loop()
{

  int received = irreceive2();
  Serial.println(millis());
  Serial.println(lasttrackchange);
  Serial.println(received);
  if(received != lastreceive && millis() > (lasttrackchange+10000)){ //different song should start playing
    if(received == 3){    // if 0 is received, play 0001.mp3. Add IRreceive of other sensors to this function.
      myDFPlayer.play(1);  //Play 0001.mp3
      lasttrackchange=millis();
      lastreceive = 3;
    }else if(received == 2){ // if 0 is received, play 0002.mp3 . Add IRreceive of other sensors to this function.
      myDFPlayer.play(2);  //Play 0002.mp3
      lasttrackchange=millis();
      lastreceive=2;
    }    
  }

  delay(500);
}

void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
  
}
int irreceive2(){/*This code receives a IR message, from for example a remote. 
 Write int irvalue2 = irreceive2(); in the loopcode 
 The received value is in the variable irvalue2.*/
  if(irrecv2.decode(&results2)){//This line checks if an incoming message is received
    int returnvalue = int(results2.value);//This line translates the incoming message to a number
    irrecv2.resume(); //This line tells the Arduino to start looking for the next message
    return returnvalue;
  }
}
