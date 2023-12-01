#include <Arduino.h>
#include <LibRobus.h>
#include <SoftwareSerial.h>
#include "rfid.h"

const byte ledPin = 22;

char* allowedTags[] = {"0E008E974354", "1600C3C98A96", "1600BF97BA84"};
Rfid r1(allowedTags[0], "Gazania", 50.0);
Rfid r2(allowedTags[1], "Cactus", 0.0);
Rfid r3(allowedTags[2], "Marguerite", 30.0);
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
  pinMode(ledPin, INPUT);
  BoardInit();
  Serial.begin(9600); 
  //rfid.begin(9600);
}

void loop() 
{
  int valread = 0;
  char val;
  char rfidtag[13];
  int i = 0;
  int tagNumber = 0;

  if (Serial.available() > 0)
  {
    if ((val = Serial.read()) == 2)
    {
      while (valread < 12)
      {
        if (Serial.available() > 0)
        {
          val = Serial.read();
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
        // Tag non trouvé dans la liste
        for (int i = 0; i < 12; i++)
        {
          Serial.print(rfidtag[i]);
        }
      }
      else
      {
        // Tag trouvé dans la liste
        Serial.println(tags[tagNumber].getTag());
        Serial.print("Nom de la plante associée au tag : ");
        Serial.println(tags[tagNumber].getNomPlante());
        Serial.print("Taux d'humidité requis : ");
        Serial.println(tags[tagNumber].getTauxHumidite());
      }
    }
  }
}