#include <Adafruit_DHT.h>
#include <blynk.h>

// Define la impresión serial y habilita el modo de depuración para Blynk
#define BLYNK_PRINT Serial
#define BLYNK_DEBUG       

// Autorización para conectarse a Blynk
char auth[] = "KfOeGO-hai5_7goWeJaBIygX2gdxTumv";
BlynkTimer timer;

// Define el tipo y el pin del sensor DHT
#define DHTPIN 2
#define DHTTYPE DHT11

// Variables para almacenar la temperatura y la humedad
int temperature;
int humidity;

// Crea un objeto DHT
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    // Inicializa la comunicación serial a 9600 baudios
    Serial.begin(9600);
    // Espera 5 segundos antes de iniciar el código
    delay(5000);
    // Inicializa el objeto DHT
    dht.begin();
    // Inicializa la conexión a Blynk
    Blynk.begin(auth);
}

// Función para actualizar los valores de temperatura y humedad
void updateValues() {
  // Obtiene la temperatura en grados Celsius
  temperature = dht.getTempCelcius();
  // Obtiene la humedad en porcentaje
  humidity = dht.getHumidity();

  // Escribe los valores de temperatura y humedad en los widgets virtuales en la aplicación Blynk
  Blynk.virtualWrite(V5, temperature);
  Blynk.virtualWrite(V6, humidity);

  // Publica los valores de temperatura y humedad en Particle Cloud
  Particle.publish("temperature", String(temperature) + " °C");
  Particle.publish("humidity", String(humidity) + " %");
}

void loop()
{
    // Espera 1 segundo
    delay(1000);
    // Ejecuta Blynk
    Blynk.run();
    // Actualiza los valores de temperatura y humedad
    updateValues();
}
