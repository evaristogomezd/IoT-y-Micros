#include <Adafruit_DHT.h>
#include <blynk.h>
#include <blynk.h>
#include <Adafruit_DHT.h>

#define BLYNK_PRINT Serial  
#define BLYNK_DEBUG       
char auth[] = "Pj-t1iYc8GE934BFpK6EvjfkLX-r1Fpt";
BlynkTimer timer;

#define DHTPIN 2
#define DHTTYPE DHT11

int temperature2;
int humidity2;

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    Serial.begin(9600);
    delay(5000); 
    dht.begin();
    Blynk.begin(auth);
}


void updateValues() {
  temperature2 = dht.getTempCelcius();
  humidity2 = dht.getHumidity();

  Blynk.virtualWrite(V5, temperature2);
  Blynk.virtualWrite(V6, humidity2);

  Particle.publish("temperatura2", String(temperature2) + " °C");
  Particle.publish("humedad2", String(humidity2) + " %");

    Particle.variable("humidity2", humidity2);
    Particle.variable("temperature2", temperature2);
//	Particle.publish("Ambiente", "{\"Humedad\":"+String(h)+", \"Temperatura\":"+String(t)+"}");
}

void loop()
{
    delay(900000);
    Blynk.run();
    updateValues();
    
	Serial.print("Humedad: "); 
	Serial.print(humidity2);
	Serial.print("% - ");
	Serial.print("Temperatura: "); 
	Serial.print(temperature2);
	Serial.print("*C ");
	Serial.println(Time.timeStr());
}