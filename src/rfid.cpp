#include "rfid.h"

Rfid::Rfid(char numtag[], char plante[], float humidite)
{
    strcpy(this->tag, numtag);
    strcpy(this->nom_plante, plante);
    this->taux_humidite = humidite;
}

Rfid::~Rfid()
{

}

char* Rfid::getTag()
{
    return this->tag;
}

char* Rfid::getNomPlante()
{
    return this->nom_plante;
}

float Rfid::getTauxHumidite()
{
    return this->taux_humidite;
}