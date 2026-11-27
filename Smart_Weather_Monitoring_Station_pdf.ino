
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <KiwisIoT.h>

// WiFi Credentials
const char* ssid = "YOUR_WIFI_NAME";
const char* pass = "YOUR_WIFI_PASSWORD";

// KiwisIoT Dashboard ID
const char* topic = "dash_1795674891703";

// DHT11 Sensor
#define DHTPIN D2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// KiwisIoT
KiwisIoT kiwisiot(ssid, pass, topic);

void setup()
{
  Serial.begin(9600);

  dht.begin();

  Serial.println("SMART WEATHER MONITORING");
  Serial.println("------------------------");

  kiwisiot.begin();

  Serial.println("KiwisIoT Started");
}

void loop()
{
  kiwisiot.run();

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity))
  {
    Serial.println("DHT11 Sensor Error!");
    delay(2000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.println(temperature);

  Serial.print("Humidity: ");
  Serial.println(humidity);

  // Send data to KiwisIoT
  kiwisiot.send("0", temperature);
  kiwisiot.send("1", humidity);

  Serial.println("Data Sent to KiwisIoT");

  delay(3000);
}
