#include <OneWire.h> 
#include <DallasTemperature.h>

float temp = 0.0;
int j = 1;
int i = 1;

/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 2 
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
 // Start up the library 
 sensors.begin(); 
 pinMode(5, OUTPUT);
} 
void loop(void) 
{ 
 // call sensors.requestTemperatures() to issue a global temperature 
 // request to all devices on the bus 
/********************************************************************/
 //Serial.print(" Requesting temperatures..."); 
 sensors.requestTemperatures(); // Send the command to get temperature readings 
 //Serial.println("DONE"); 
/********************************************************************/
 Serial.print("Temperature is: "); 
 temp=(((sensors.getTempCByIndex(0))*(9/5))+32.0+8.5);
 Serial.println(temp); // Why "byIndex"?  

 if(temp>=80.0&&j==1){
  digitalWrite(5, LOW);
  j=0;
  i=1;
 }

 if(temp<=70.0&&i==1){
  digitalWrite(5,HIGH);
  i=0;
  j=1;
 }
   // You can have more than one DS18B20 on the same bus.  
   // 0 refers to the first IC on the wire 
   delay(400); 
} 
