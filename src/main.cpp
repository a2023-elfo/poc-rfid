#include <Arduino.h>
#include <LibRobus.h>
#include <SoftwareSerial.h>

const byte rxPin = 10;
const byte txPin = 11;

SoftwareSerial rfid = SoftwareSerial(rxPin, txPin);
char* allowedTags[] = {"0E008E974354", "0415148DE36B"};
char* tagName[] = {"carte", "rondelle"};
int data = 0;
int numberofTags = sizeof(allowedTags)/sizeof(allowedTags[0]);
char tagValue[13];

int findTag(char tagValue[])
{
  for (int i = 0; i < numberofTags; i++)
  {
    if (strcmp(tagValue, allowedTags[i]) == 0)
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
  byte i = 0;
  byte val = 0;
  byte code[6] ;
  byte checksum = 0;
  byte bytesread = 0;
  byte tempbyte = 0;

  if (rfid.available() > 0)
  {
    //On regarde pour le marquer de début STX(StartOfText) (2 est sa valeur ASCII)
    if ((val = rfid.read()) == 2) 
    {
      // On lit les 10 caractères de la puce RFID + les 2 caractères de checksum
      while (bytesread < 12)
      {
        if (rfid.available() > 0)
        {
          val = rfid.read();
          // On check pour être sur qu'on lit le bon type de caractère
          if ((val == 0x0D) || (val == 0x0A) || (val == 0x03) || (val == 0x02))
          {
            // On arrête de lire pcq erreur
            break;
          }
        }

        // On convertit le code RFID hexadecimal
        if ((val >= '0') && (val <= '9'))
        {
          val = val - '0';
        }
        else if ((val >= 'A') && (val <= 'F'))
        {
          val = 10 + val - 'A';
        }

        if (bytesread & 1 == 1)
        {
          code[bytesread >> 1] = (val | (tempbyte << 4));

          if ((bytesread >> 1 != 5))
          {
            checksum ^= code[bytesread >> 1];
          }
        }
        else
        {
          tempbyte = val;
        }
        // On lit le prochain caractère
        bytesread++;
      }

      if (bytesread == 12)
      {
        /*
        Serial.print("5-byte code: ");
        for (int i = 0; i < 5; i++)
        {
          if (code[i] < 16)
          {
            Serial.print("0");
          }
          Serial.print(code[i], HEX);
          Serial.print(" ");
        }
        Serial.println();
        */
        Serial.print("Checksum : ");
        Serial.print(code[5], HEX);
        Serial.print(code[5] == checksum ? " -- passed." : " -- error.");
        Serial.println();
      }
      bytesread = 0;
    }
  }
}