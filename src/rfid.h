#include <Arduino.h>

class Rfid
{
public :
    Rfid();
    Rfid(char numtag[], char plante[], float humidite);
    ~Rfid();
    char getNomPlante(char tag[]);
    float getTauxHumidite(char tag[]);
    int findTag(char tag[]);

private :
    char tag[12];
    char nom_plante[12];
    float taux_humidite;
};