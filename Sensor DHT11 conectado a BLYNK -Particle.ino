#include <Adafruit_DHT.h>

#include <blynk.h>

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

  Particle.publish("temperature", String(temperature) + " °C");
  Particle.publish("humidity", String(humidity) + " %");
}

void loop()
{
    delay(1000);
    Blynk.run();
    updateValues();
}