//Temperature & Humidity monitoring system
//-Read data from sensor- "DHT22"
//-Display output on OLED 
//-Microcontroller- "ESP32"

//Library including
#include <DHT.h>  // sensor library
// OLED library
#include <Wire.h>

#include <Adafruit_BusIO_Register.h>
#include <Adafruit_GenericDevice.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>

#include <Adafruit_GFX.h>

#include <Adafruit_SSD1306.h>
#include <splash.h>

// DHT sensor settings
#define DHTPIN 4        // GPIO connected to DHT22
#define DHTTYPE DHT22   
DHT dht (DHTPIN, DHTTYPE); // DHT sensor object

// OLED settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()
  {
    // serial monitor and sensor initializaton
    Serial.begin(115200);
    dht.begin();

    //OLED init
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
      {
        Serial.println("OLED not found");
        for(;;); // Don't proceed
      }

      display.clearDisplay();
      display.setTextColor(SSD1306_WHITE);
      display.setTextSize(1);
      display.setCursor(0,0);
      display.println("Initializing..");
      display.display();
      delay(2000);
  }

void loop()
  {
    float temp = dht.readTemperature();
    float humi = dht.readHumidity();

    // check if reads failed
    if (isnan(temp) || isnan(humi))
      {
        Serial.println("Failed to read!");
        return;
      }
      // print on serial monitor
      Serial.print("Temp: ");
      Serial.print(temp);
      Serial.println(" C");
      Serial.print("Humi: ");
      Serial.print(humi);
      Serial.println(" %");

      // display on OLED
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextSize(1);
      display.print("DHT22 sensor reading: ");

      display.setTextSize(2);
      display.setCursor(0, 20);
      display.print("Temp: ");
      display.print(temp);
      display.print(" C");
    
      display.setCursor(0, 45);
      display.print("Humi: ");
      display.print(humi);
      display.print(" %");

      display.display();
      delay(2000);

  }