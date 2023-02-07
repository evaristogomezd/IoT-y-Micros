#include <Adafruit_BMP280.h>

SYSTEM_MODE(AUTOMATIC); 
#define SEALEVELPRESSURE_HPA (1013.25) 
CE_BME280 bme;
int brightness = 50; 
float bmeTemperature; 
float bmePressure; 
float bmeHumidity; 
float dewpoint; 
float startTime; 

void setup() 
{ 
   delay(2000); 
   if(!bme.begin()){ 
       String errorMessage; 
       errorMessage = "Not found"; 
       Spark.publish("BME280 Error", errorMessage); 
       } 
   startTime = millis(); 
}

void loop(){ 
   if (millis() > startTime + 2000){ 
       startTime = millis(); 
       getBME280Data();
       printValues();
   } 
}


void getBME280Data(){ 
   bmeTemperature = bme.readTemperature() - 3; 
   bmeHumidity = bme.readHumidity(); 
   if (bmeHumidity > 1){ 
   } 
   bmePressure = (bme.readPressure()/100) - 3; 
   dewpoint = bmeTemperature - ((100 - bmeHumidity)/5); 
}

void printValues()
{
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");

    Serial.print("Pressure = ");
    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    Serial.println();
}