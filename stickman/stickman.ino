/*
 * STICKMAN ANIMATION DEMO
 * Adapted to use the ST7789_AVR library and user-confirmed settings.
 * Rotation fixed to be right-side up.
 */

// Includes from your working code
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <ST7789_AVR.h>

// Pin definitions from your working code
#define TFT_DC    7
#define TFT_RST   8
#define SCR_WD   240
#define SCR_HT   240

// Initialization from your working code
ST7789_AVR lcd = ST7789_AVR (TFT_DC, TFT_RST);

// Center of the screen
int cx = 120;
int cy = 120;

void setup() {
  lcd.init(SCR_WD, SCR_HT);
  
  // --- THIS IS THE FIX ---
  // Set rotation to 2 for right-side up
  lcd.setRotation(2); 
  // -----------------------
  
  // 1. Set the scene
  lcd.fillScreen(BLACK);
  lcd.setTextColor(YELLOW);
  lcd.setTextSize(3);
  lcd.setCursor(40, 30);
  lcd.println("PIXZZLE!");
  
  // Draw a THICK ground
  lcd.fillRect(0, 220, 240, 20, GREEN);
}

void loop() {
  // Run the animation cycle 5 times (5 * 4 poses * ~1 sec = ~20 sec)
  for (int i = 0; i < 5; i++) {
    // --- FRAME 1: ARMS DOWN, LEGS TOGETHER ---
    drawStickman(1); 
    delay(500); // 0.5 sec delay
    eraseStickman(1); 

    // --- FRAME 2: ARMS MIDDLE, LEGS APART ---
    drawStickman(2);
    delay(500);
    eraseStickman(2);

    // --- FRAME 3: ARMS UP! ---
    drawStickman(3);
    delay(500);
    eraseStickman(3);

    // --- FRAME 2: ARMS MIDDLE (To make it smooth) ---
    drawStickman(2);
    delay(500);
    eraseStickman(2);
  }
  
  // After ~20 seconds, show "Done!"
  lcd.fillScreen(BLACK);
  lcd.setCursor(70, 110);
  lcd.setTextSize(3);
  lcd.println("DONE!");
  delay(10000); // Wait 10 sec before repeating
}

// --- HELPER FUNCTIONS ---

// Helper function to draw a thick line
void drawThickLine(int x1, int y1, int x2, int y2, uint16_t color) {
  lcd.drawLine(x1, y1, x2, y2, color);
  lcd.drawLine(x1+1, y1, x2+1, y2, color);
  lcd.drawLine(x1, y1+1, x2, y2+1, color);
  lcd.drawLine(x1+1, y1+1, x2+1, y2+1, color);
}

// Helper function to draw the stickman
void drawStickman(int pose) {
  // Head is now bigger (radius 25)
  lcd.fillCircle(cx, cy-40, 25, WHITE); 
  // Body is now a thick rectangle
  lcd.fillRect(cx-4, cy-15, 8, 55, WHITE); 
  
  if (pose == 1) { // Arms Down, Legs Together
    drawThickLine(cx, cy-10, cx-30, cy+20, WHITE); // Left Arm
    drawThickLine(cx, cy-10, cx+30, cy+20, WHITE); // Right Arm
    drawThickLine(cx, cy+40, cx-10, cy+100, WHITE); // Left Leg
    drawThickLine(cx, cy+40, cx+10, cy+100, WHITE); // Right Leg
  } 
  else if (pose == 2) { // T-Pose
    drawThickLine(cx, cy-10, cx-40, cy-20, WHITE); 
    drawThickLine(cx, cy-10, cx+40, cy-20, WHITE);
    drawThickLine(cx, cy+40, cx-25, cy+90, WHITE);
    drawThickLine(cx, cy+40, cx+25, cy+90, WHITE);
  }
  else if (pose == 3) { // Arms Up!
    drawThickLine(cx, cy-10, cx-30, cy-50, WHITE); 
    drawThickLine(cx, cy-10, cx+30, cy-50, WHITE);
    drawThickLine(cx, cy+40, cx-25, cy+90, WHITE);
    drawThickLine(cx, cy+40, cx+25, cy+90, WHITE);
  }
}

// Helper function to "Erase" (draw the exact same lines in BLACK)
void eraseStickman(int pose) {
  lcd.fillCircle(cx, cy-40, 25, BLACK);
  lcd.fillRect(cx-4, cy-15, 8, 55, BLACK);
  
  if (pose == 1) {
    drawThickLine(cx, cy-10, cx-30, cy+20, BLACK);
    drawThickLine(cx, cy-10, cx+30, cy+20, BLACK);
    drawThickLine(cx, cy+40, cx-10, cy+100, BLACK);
    drawThickLine(cx, cy+40, cx+10, cy+100, BLACK);
  } 
  else if (pose == 2) {
    drawThickLine(cx, cy-10, cx-40, cy-20, BLACK);
    drawThickLine(cx, cy-10, cx+40, cy-20, BLACK);
    drawThickLine(cx, cy+40, cx-25, cy+90, BLACK);
    drawThickLine(cx, cy+40, cx+25, cy+90, BLACK);
  }
  else if (pose == 3) {
    drawThickLine(cx, cy-10, cx-30, cy-50, BLACK);
    drawThickLine(cx, cy-10, cx+30, cy-50, BLACK);
    drawThickLine(cx, cy+40, cx-25, cy+90, BLACK);
    drawThickLine(cx, cy+40, cx+25, cy+90, BLACK);
  }
}