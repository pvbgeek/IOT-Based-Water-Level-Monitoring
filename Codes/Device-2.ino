// This example sends data to multiple variables to
// Ubidots through HTTP protocol.

/****************************************
 * Include Libraries
 ****************************************/

#include "Ubidots.h"
#include <LiquidCrystal_I2C.h>

/****************************************
 * Define Instances and Constants
 ****************************************/
int Sensor_pin = A0;
int Buzzer_pin = D3;

const char* UBIDOTS_TOKEN = "BBFF-UAXxUtHas9X4kOVBuoOWNsJQUTeUHF";  // Put here your Ubidots TOKEN
const char* WIFI_SSID = "Galaxy M31s85EE";      // Put here your Wi-Fi SSID
const char* WIFI_PASS = "qwert12345";      // Put here your Wi-Fi password

Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);
LiquidCrystal_I2C lcd(0x27, 16, 2);

/****************************************
 * Auxiliar Functions
 ****************************************/

// Put here your auxiliar functions

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  Serial.begin(115200);

  //----CONNECTING TO WIFI----//
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  // ubidots.setDebug(true);  // Uncomment this line for printing debug messages

  //----SETTING PIN CONFIGURATIONS----//
  pinMode(Sensor_pin, INPUT);
  pinMode(Buzzer_pin, OUTPUT);

  //----LCD INITIALIZATION----//
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);         // move cursor to   (0, 0)
  lcd.print("Setup Completed");
  delay(1000);
}

void loop() {

  //----READING VALUE FROM SENSOR----//
  float water_value = analogRead(Sensor_pin); //analogRead(Sensor_pin)
  float water_value1 = digitalRead(D0);
  
  Serial.print("Water level = ");
  Serial.print(water_value);
  Serial.print("  ");
  Serial.println(water_value1);

  water_value = map(water_value, 525, 1024, 88, 0);
  Serial.println(water_value);
  digitalWrite(Buzzer_pin, water_value1);


  //----LCD INTERFACING----//
  lcd.clear();// clear previous values from screen
  lcd.setCursor(0,0);
  lcd.print("Device 2");
  lcd.setCursor(0,1);
  lcd.print("Water Level:");
  lcd.print(int(water_value));
  lcd.print("%");

  //----UPDATING VARIABLE VALUE ON UBIDOTS----//
  ubidots.add("Device2-v1", water_value);  // Change for your variable name

  bool bufferSent = false;
  bufferSent = ubidots.send();  // Will send data to a device label that matches the device Id

  if (bufferSent) {
    // Do something if values were sent properly
    Serial.println("Values sent by the device");
  }
  
  delay(500);
}
