#include <Arduino.h>
#include <string.h>

class Rfid
{
public :
    Rfid(char numtag[], char plante[], float humidite);
    ~Rfid();
    char* getTag();
    char* getNomPlante();
    float getTauxHumidite();

private :
    char tag[13];
    char nom_plante[30];
    float taux_humidite;
};