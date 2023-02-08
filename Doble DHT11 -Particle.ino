
#include <Adafruit_DHT.h>

#define DHTPIN 2     
#define DHTPIN2 3


#define DHTTYPE DHT11
#define DHTTYPE2 DHT11

DHT dht(DHTPIN, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE2);

double h,t,h2,t2;

void setup() {
	Serial.begin(9600); 
	Serial.println("Adquisicion de datos de tempeatura y humedad");

	dht.begin();
	
    Particle.variable("h", 1);
    Particle.variable("t", 1);
	Particle.publish("Ambiente", "{\"Humedad\":"+String(h)+", \"Temperatura\":"+String(t)+"}");
   
    Particle.variable("h2", 1);
    Particle.variable("t2", 1);
	Particle.publish("Ambiente2", "{\"Humedad2\":"+String(h2)+", \"Temperatura2\":"+String(t2)+"}");
}

void loop() {
	delay(5000);
	double h = dht.getHumidity();
	double t = dht.getTempCelcius();

    double h2 = dht2.getHumidity();
	double t2 = dht2.getTempCelcius();
	if (isnan(h) || isnan(t)) {
		Serial.println("ERROR al leer el sensor DHT11 1");
		return;
	}
	if (isnan(h2) || isnan(t2)) {
		Serial.println("ERROR al leer el sensor DHT11 2");
		return;
	}

	Serial.print("Humedad: "); 
	Serial.print(h);
	Serial.print("% - ");
	Serial.print("Temperatura: "); 
	Serial.print(t);
	Serial.print("*C ");
	Serial.print("Humedad 2: "); 
	Serial.print(h2);
	Serial.print("% - ");
	Serial.print("Temperatura 2: "); 
	Serial.print(t2);
	Serial.print("*C ");
	Serial.println(Time.timeStr());
}