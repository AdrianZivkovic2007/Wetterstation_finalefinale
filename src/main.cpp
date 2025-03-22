#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 4      // DHT11 an Pin 4
#define LDRPIN A0     // LDR an analogem Pin A0

#define DHTTYPE DHT11 // DHT11 verwenden

DHT dht(DHTPIN, DHTTYPE);  // DHT11-Sensor
LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD mit I2C-Adresse 0x27

void setup() {
  lcd.init();       // LCD initialisieren
  lcd.backlight();  // LCD Hintergrundbeleuchtung einschalten

  Serial.begin(9600);  // Seriellen Monitor starten
  dht.begin();         // DHT11 initialisieren

  // Anfangsnachricht auf dem LCD anzeigen
  lcd.setCursor(0, 0);
  lcd.print("Wetterstation");
  delay(2000);  // 2 Sekunden warten
  lcd.clear();
}

void loop() {
  // Temperatur und Feuchtigkeit vom DHT11 lesen
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Lichtsensor-Wert lesen
  int lightLevel = analogRead(LDRPIN);

  // Fehlerbehandlung: Wenn Sensorwerte ungültig sind
  if (isnan(temperature) || isnan(humidity)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensorfehler");
  } else {
    // Temperatur und Feuchtigkeit auf LCD anzeigen
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print(" C");

    lcd.setCursor(0, 1);
    lcd.print("Feucht: ");
    lcd.print(humidity);
    lcd.print(" %");
  }

  // Lichtsensor-Wert auf dem LCD anzeigen
  lcd.setCursor(0, 1);
  lcd.print("Licht: ");
  lcd.print(lightLevel);

  // Serielle Ausgabe
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" C, ");
  Serial.print("Feucht: ");
  Serial.print(humidity);
  Serial.print(" %, ");
  Serial.print("Licht: ");
  Serial.println(lightLevel);

  delay(3000);  // 3 Sekunden warten, bevor neue Daten angezeigt werden
  lcd.clear();  // LCD-Bildschirm löschen
}
