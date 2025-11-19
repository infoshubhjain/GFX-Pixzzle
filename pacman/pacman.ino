/*
 * PAC-MAN ANIMATION DEMO
 * Adapted to use the ST7789_AVR library.
 * Rotation is fixed, and animation is ~20 seconds.
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

// --- Global variables for animation ---
bool mouthOpen = false; // To track Pac-Man's mouth
int pacManY = 120; // Pac-Man's vertical position
int dotSize = 6;  // Make the dots big and visible

void setup() {
  lcd.init(SCR_WD, SCR_HT);
  
  // --- FIX ---
  // Set rotation to 2 for right-side up
  lcd.setRotation(2); 
  
  // Draw the stage once at the beginning
  drawStage();
}

void loop() {
  // This loop will run the animation 3 times (for ~20 seconds)
  for (int run = 0; run < 3; run++) {
    
    // Animate Pac-Man moving from x=30 to x=220
    for (int pacX = 30; pacX < 220; pacX += 10) {
      
      // 1. Erase the previous frame (at the old position)
      erasePacman(pacX - 10, !mouthOpen); 

      // 2. Draw the new frame (at the new position)
      drawPacman(pacX, mouthOpen);
      
      // 3. "Eat" the dot if we are on one
      // (This just draws a black circle over the dot)
      if (pacX == 60 || pacX == 90 || pacX == 120 || pacX == 150 || pacX == 180) {
        lcd.fillCircle(pacX, pacManY, dotSize, BLACK);
      }
      
      // 4. Toggle the mouth for the next frame
      mouthOpen = !mouthOpen;
      
      // 5. Delay to control speed
      delay(300); // 0.3 second delay per frame
    }
    
    // Erase the last frame
    erasePacman(210, mouthOpen);
    delay(1000); // Pause at the end
    drawStage(); // Redraw the stage to reset the dots
  }
}

// --- HELPER FUNCTIONS ---

// Draws the initial stage
void drawStage() {
  lcd.fillScreen(BLACK);
  lcd.setTextColor(YELLOW);
  lcd.setTextSize(3);
  lcd.setCursor(40, 30);
  lcd.println("HELLO KIDS!");
  
  // Draw all the dots
  lcd.fillCircle(60,  pacManY, dotSize, WHITE);
  lcd.fillCircle(90,  pacManY, dotSize, WHITE);
  lcd.fillCircle(120, pacManY, dotSize, WHITE);
  lcd.fillCircle(150, pacManY, dotSize, WHITE);
  lcd.fillCircle(180, pacManY, dotSize, WHITE);
}

// Draws Pac-Man at a position
void drawPacman(int x, bool open) {
  // Head
  lcd.fillCircle(x, pacManY, 25, YELLOW); 
  
  if (open) {
    // Draw open mouth (a black triangle)
    lcd.fillTriangle(x, pacManY, x + 25, pacManY - 20, x + 25, pacManY + 20, BLACK);
  } else {
    // Draw closed mouth (just a black line)
    lcd.drawLine(x, pacManY, x + 25, pacManY, BLACK);
  }
}

// Erases Pac-Man at a position (by drawing him in black)
void erasePacman(int x, bool open) {
  // Erase Head
  lcd.fillCircle(x, pacManY, 25, BLACK);
  
  if (open) {
    // Erase open mouth
    lcd.fillTriangle(x, pacManY, x + 25, pacManY - 20, x + 25, pacManY + 20, BLACK);
  } else {
    // Erase closed mouth
    lcd.drawLine(x, pacManY, x + 25, pacManY, BLACK);
  }
}