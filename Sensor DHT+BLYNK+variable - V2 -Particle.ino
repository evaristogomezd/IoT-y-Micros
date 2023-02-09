#include <blynk.h>
#include <Adafruit_DHT.h>

#define BLYNK_PRINT Serial  
#define BLYNK_DEBUG       
char auth[] = "KfOeGO-hai5_7goWeJaBIygX2gdxTumv";
BlynkTimer timer;

#define DHTPIN 2
#define DHTTYPE DHT11

int temperature;
int humidity;

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    Serial.begin(9600);
    delay(5000); 
    dht.begin();
    Blynk.begin(auth);
}


void updateValues() {
  temperature = dht.getTempCelcius();
  humidity = dht.getHumidity();

  Blynk.virtualWrite(V5, temperature);
  Blynk.virtualWrite(V6, humidity);

  Particle.publish("temperatura", String(temperature) + " °C");
  Particle.publish("humedad", String(humidity) + " %");

    Particle.variable("humidity", humidity);
    Particle.variable("temperature", temperature);
//	Particle.publish("Ambiente", "{\"Humedad\":"+String(h)+", \"Temperatura\":"+String(t)+"}");
}

void loop()
{
    delay(9000);
    Blynk.run();
    updateValues();
    
	Serial.print("Humedad: "); 
	Serial.print(humidity);
	Serial.print("% - ");
	Serial.print("Temperatura: "); 
	Serial.print(temperature);
	Serial.print("*C ");
	Serial.println(Time.timeStr());
}