//https://circuitdigest.com/microcontroller-projects/arduino-gps-speedometer-using-oled
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_SH1106.h>
#define OLED_ADDRESS   0x3C
#define OLED_RESET -1
Adafruit_SH1106 display(OLED_RESET);
int RX = 2, TX = 3;
TinyGPSPlus gps;
SoftwareSerial gpssoft(RX, TX);
void setup()
{
  Serial.begin(9600);
  gpssoft.begin(9600);
  display.begin(SH1106_SWITCHCAPVCC, OLED_ADDRESS);
  display.clearDisplay();
  display.display();
}
void loop()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(27, 2);
  display.print("CIRCUIT DIGEST");
  display.setTextSize(1);
  display.setCursor(35, 20);
  display.print("SPEED(KMPH)");
  display.display();
  while (gpssoft.available() > 0)
    if (gps.encode(gpssoft.read()))
      displayspeed();
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    display.setTextSize(1);
    display.setCursor(35, 40);
    display.print("carspeed");
    display.display();
    while (true);
  }
}
void displayspeed()
{
  if (gps.speed.isValid())
  {
    display.setTextSize(2);
    display.setCursor(40, 40);
    display.print(gps.speed.kmph());
    display.display();
  }
  else
  {
    display.setTextSize(1);
    display.setCursor(35, 40);
    display.print("No Data!!!");
    display.display();
  }
  delay(100);
}
