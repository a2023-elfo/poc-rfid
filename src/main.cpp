#include <Arduino.h>
#include <LibRobus.h>
#include <SoftwareSerial.h>
#include "rfid.h"

const byte rxPin = 10;
const byte txPin = 11;

SoftwareSerial rfid = SoftwareSerial(rxPin, txPin);
char* allowedTags[] = {"0E008E974354", "0415148DE36B"};
Rfid r1(allowedTags[0], "Marguerite", 30.5);
Rfid r2(allowedTags[1], "Pissenlit", 20.76);
Rfid tags[] = {r1, r2};

int numberofTags = sizeof(allowedTags)/sizeof(allowedTags[0]);

int findTag(char tagValue[])
{
  for (int i = 0; i < numberofTags; i++)
  {
    if (strcmp(tagValue, tags[i].getTag()) == 0)
    {
      return i;
    }
  }
  return -1;
}

void setup() {
  BoardInit();
  Serial.begin(9600); 
  rfid.begin(9600);
}

void loop() 
{
  int valread = 0;
  char val;
  char rfidtag[13];
  int i = 0;
  int tagNumber = 0;

  if (rfid.available() > 0)
  {
    if ((val = rfid.read()) == 2)
    {
      while (valread < 12)
      {
        if (rfid.available() > 0)
        {
          val = rfid.read();
          if ((val == 0x0D) || (val == 0x0A) || (val == 0x03) || (val == 0x02))
          {
            break;
          }
          else
          {
            rfidtag[i] = val;
            i++;
          }
        }
      }
      rfidtag[i] = '\0';
      tagNumber = findTag(rfidtag);
      if (tagNumber == -1)
      {
        //Tag  non trouvé dans la liste
        Serial.println("ERREUR");
      }
      else
      {
        //Tag trouvé dans la liste
        Serial.println(tags[tagNumber].getNomPlante());
      }
    }
  }
}