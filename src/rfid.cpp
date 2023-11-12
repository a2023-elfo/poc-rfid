#include "rfid.h"

Rfid::Rfid(char tags[], char nom[], float humidite)
{
    strcpy(this->tag, tags);
    strcpy(this->nom_plante, nom);
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