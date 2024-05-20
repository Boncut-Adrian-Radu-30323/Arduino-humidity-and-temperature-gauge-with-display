#include <LiquidCrystal.h>
#include "DHT.h"

#define DHTPIN 8
#define LED_PIN 7

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

unsigned long previousMillis = 0;
const long interval = 1000;
bool ledState = false;

void setup() 
{
  lcd.begin(16, 2);
  dht.begin();
  lcd.print("Temp: Umiditate:");
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  unsigned long currentMillis = millis(); 
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }
  lcd.setCursor(0, 1);
  float h = dht.readHumidity();
  float f = dht.readTemperature();
  if (isnan(h) || isnan(f)) {
    lcd.print("ERROR");
    return;
  }

  lcd.print(f);
  lcd.setCursor(8,1);
  lcd.print(h);
}
