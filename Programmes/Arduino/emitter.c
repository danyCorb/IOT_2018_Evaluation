/********************************************************************/
// First we include the libraries
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;

/********************************************************************/
// Data wire is plugged into pin 5 on the Arduino 
#define ONE_WIRE_BUS 5
#define ARDUINO_ID 1
/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
/********************************************************************/ 
void setup(void) 
{ 
   // start serial port 
   Serial.begin(9600); 
   Serial.println("Dallas Temperature IC Control Library Demo"); 
   if (!driver.init())
           Serial.println("init failed");

   // Start up the library 
   sensors.begin(); 
} 
void loop(void) 
{ 
   // call sensors.requestTemperatures() to issue a global temperature 
   // request to all devices on the bus 
  /********************************************************************/
   sensors.requestTemperatures(); // Send the command to get temperature readings 
  /********************************************************************/
   Serial.print("\nTemperature is: "); 
   //float temperature = sensors.getTempCByIndex(0);
   float temperature = 25.6; 
   char msg[255]={0};
   sprintf(msg,"%f %d",temperature, ARDUINO_ID);
   driver.send((const uint8_t *)msg, strlen(msg));
      driver.waitPacketSent();

   Serial.print(temperature); // Why "byIndex"?  
   Serial.flush();
   // You can have more than one DS18B20 on the same bus.  
   // 0 refers to the first IC on the wire 
   delay(1000); 
} 
