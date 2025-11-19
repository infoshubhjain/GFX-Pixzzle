/*
ST7789 240x240 IPS (without CS pin) connections (only 6 wires required):
#01 GND -> GND
#02 VCC -> VCC (3.3V only!)
#03 SCL -> D13/SCK
#04 SDA -> D11/MOSI
#05 RES -> D8 or any digital
#06 DC  -> D7 or any digital
#07 BLK -> NC
*/

#define TFT_DC    7  // [cite: 14]
#define TFT_RST   8  // [cite: 15]
#define SCR_WD   240 // [cite: 16]
#define SCR_HT   240 // [cite: 17]

#include <SPI.h>             // [cite: 18]
#include <Adafruit_GFX.h>    // [cite: 19]
#include <ST7789_AVR.h>      // [cite: 20]

// Initialize the screen object [cite: 21]
ST7789_AVR lcd = ST7789_AVR (TFT_DC, TFT_RST);

void setup(void)
{
  Serial.begin(9600);           // [cite: 25]
  lcd.init(SCR_WD, SCR_HT);     // [cite: 26]
  
  // Your original test code
  lcd.fillScreen(BLACK);        // [cite: 27]
  lcd.setCursor(0, 0);          // [cite: 28]
  lcd.setTextColor(WHITE,BLUE); // [cite: 29]
  lcd.setTextSize(3);           // [cite: 30]
  lcd.println("HELLO KIDS!!");   // [cite: 31]
  delay(2000); // Display message for 2 seconds [cite: 32]
}


void loop()
{
  // --- New Graphics Test ---
  // This will run after your "HELLO WORLD" message.

  // 1. Fill screen with a new color
  lcd.fillScreen(BLACK);

  // 2. Draw a Red Rectangle
  // (x, y, width, height, color)
  lcd.drawRect(20, 20, 100, 100, RED);
  delay(1000);

  // 3. Draw a Green Circle
  // (centerX, centerY, radius, color)
  lcd.drawCircle(120, 120, 50, GREEN);
  delay(1000);

  // 4. Draw a filled-in Blue Triangle
  // (x1, y1, x2, y2, x3, y3, color)
  lcd.fillTriangle(120, 220, 20, 120, 220, 120, BLUE);
  delay(1000);

  // 5. Draw some Yellow text
  lcd.setCursor(25, 100);
  lcd.setTextColor(YELLOW);
  lcd.setTextSize(5);
  lcd.println("PIXZZLE");
  delay(2000);
}