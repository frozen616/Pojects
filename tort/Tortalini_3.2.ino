// Depends on the following Arduino libraries:
// - Adafruit Unified Sensor Library: https://github.com/adafruit/Adafruit_Sensor
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>

#define DHTPIN A0//pin which is connected to the DHT sensor.
#define DHTTYPE DHT22 //the type of sensor that is being used. 
#define HumTime 600000

const int delayTime = 1000;
const int heatLamp = 9;
const int humidifier = 8;
int humidifierOnOff = 0;
int tempOnOff = 0;

const float minTemp = 75.0f;
const float maxTemp = 85.0f;
const float minHumidity = 70.0f;
const float maxHumidity = 80.0f;


float hum = 0;
float temp = 0; 
unsigned long currentTime; 






//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;//sets variables to pins
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);//tells the lcd which pins are used

DHT_Unified dht(DHTPIN, DHTTYPE);

//uint32_t delayMS = 1000;//uint32_t means unsigned 32 bit integer

void setup() {

  Serial.begin(115200); 
  // Initialize device.

  pinMode(heatLamp, OUTPUT); //set heat lamp pin 9 to output
  pinMode(humidifier, OUTPUT);//set humidifier pin 8 to output



  //lcd.begin(20, 4);//sets the size of the lcd to 20x4
  //lcd.print("Tort's Terrarium");//prints on the top line of lcd "Tort's Terrarium".
  

  dht.begin(); //turns dht sensor on
  
  sensor_t sensor;
  
}

void loop() {
 

  
  //lcd.setCursor(2, 2);//tells the lcd where to start printing column 2 row 2
  //delay(delayMS);//delays before reading sensor.
  // Get temperature event and print its value.
  sensors_event_t event;  
  dht.temperature().getEvent(&event);

  temp = event.temperature*1.8f+32.0f;

  //isnan is used evaluates if temp is a real number returns false or true
  //if the temp has a nonreal number stored in it then the error statement will pop up. 
  if (isnan(temp)) {
    //Serial.print("Error reading temperature!\n");
  }
  else {

    temp = event.temperature*1.8f+32.0f;
    


    //lcd.print("Temp = ");
    //lcd.print(temp);
    //lcd.print("F       ");
  }

if (temp < minTemp && tempOnOff != 1) {
    digitalWrite(heatLamp, HIGH); 
    //Serial.println("Heat Lamp On"); // if temperature is below minTemp than turn on heat lamp
    tempOnOff = 1;
    }
 
else if (temp > maxTemp && tempOnOff != 2) {
    digitalWrite(heatLamp, LOW); 
    //Serial.println("Heat Lamp OFF"); // if temp is above maxTemp than turn off heat lamp.
    tempOnOff = 2;
    }

  delay (delayTime); 
  
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  hum = event.relative_humidity;
  
  if (isnan(hum)) {
   // Serial.println("Error reading humidity!\n");
  }
  else {
    


    //lcd.print("Humidity = ");
   // lcd.print(hum);
   // lcd.print("%");
    
  }

 if (hum > minHumidity){
  currentTime = millis();
 }
 if (hum < minHumidity && humidifierOnOff != 1)  {
  digitalWrite(humidifier, HIGH);
  //Serial.println("Humidifier On"); // if humidity is below minHumidity than turn on humidifier.
  //lcd.print(" Humidity  On");
  humidifierOnOff = 1;
 
    }
 
  else if (hum > maxHumidity && humidifierOnOff !=2)  {
  digitalWrite(humidifier, LOW);
  //Serial.println("Humidifier Off"); // if humidity is above maxHumidity than turn off humidifier.
  //lcd.print(" Humidity Off");
  humidifierOnOff = 2;
  
    }

   // Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.print(":");
   // Serial.print(" F \n");

   // Serial.print("Humidity: ");
    Serial.print(hum);
   // Serial.print("%");
   Serial.println(" ");
   

    
if (millis()-currentTime > HumTime){
 // Serial.print("FILL HUMIDIFIER \n"); 
}

    
delay(delayTime);//delays program from grabbing readings to fast.






  
}
