/********************************************************************/
// Inclusion des librairies de gestion des communications avec le thermomètre et la radio
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <RH_ASK.h>
#include <SPI.h>

// variable de configuration du module radio
RH_ASK driver;

/********************************************************************/
// Les connecteurs utilisés 
#define ONE_WIRE_BUS 5 // Connecteur thermomètre
#define ARDUINO_ID 1 // connecteur radio
/********************************************************************/

// Initialisation du connecteur thermomètre
OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
// Initialisation du capteur
DallasTemperature sensors(&oneWire);
/********************************************************************/ 



void setup(void) 
{ 
 // Initialisation du port série
 Serial.begin(9600); 
 // initialisation du communicateur
 if (!driver.init())
         Serial.println("init failed");

 // Lancement du capteur
 sensors.begin(); 
} 



void loop(void) 
{
 char msg[255]={0}; // Variable de message d'envoi
 
 sensors.requestTemperatures(); // Envoi de la commande pour annoncer la lecture
 float temperature = sensors.getTempCByIndex(0); // Récupération de la température
 
 sprintf(msg,"%f %d",temperature, ARDUINO_ID); // Edition de message à envoyer
 
 driver.send((const uint8_t *)msg, strlen(msg)); // Envoi du message
 driver.waitPacketSent(); // Attente de confirmation de l'envoi

 Serial.print(temperature); // Écriture de la température
 Serial.print(" "); // Écriture d'un espace
 Serial.print(ARDUINO_ID); // Écriture de l'ID de l'Arduino
 Serial.print("\n"); // Fin du message
 
 Serial.flush(); // Confirmation de l'envoi
 
   // Attente de 30s
   delay(30000); 
} 
