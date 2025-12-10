//=======================================  Receiver  =====================================================

//-------------------------------------------------------------------------------------------------------

//RECEIVER

#include <SoftwareSerial.h>
#define LED 11
String incomingString;

SoftwareSerial lora(0,1);

void setup()
{
  pinMode(LED, OUTPUT);
  Serial.begin(57600);
  lora.begin(57600);
  lora.setTimeout(500);
}

void loop()
{
  if (lora.available()) 
  {
    incomingString = lora.readString();
    Serial.print(incomingString); //Complete data frame

    char dataArray[30]; 
    incomingString.toCharArray(dataArray,30);
    char* data = strtok(dataArray, ",");
    data = strtok(NULL, ",");
    data = strtok(NULL, ",");
    Serial.println(data);  //After extracting required characters from the frame
    Serial.println();
     
    if (strcmp(data,"LO") == 0) 
    {
      digitalWrite(LED, LOW);
      delay(50);
    }

    if (strcmp(data,"HI") == 0) 
    {
      digitalWrite(LED, HIGH);
      delay(50);
    }
  }
}


//=============================================================================================================

//--------------------------------------------------------------------------------------------------------------




//============================================  Sender  =======================================================

//----------------------------------------------------------------------------------------------------------------

//TRANSMITTER

#include <SoftwareSerial.h>
  
void setup()
{
  Serial.begin(57600);
}

void loop()
{
  Serial.println("AT+SEND=1,2,LO"); //SEND to RYLR998 address = 1; SEND 2 character
  delay(800);
  Serial.println("AT+SEND=1,2,HI");
  delay(800);
}
