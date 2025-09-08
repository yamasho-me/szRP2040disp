#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <NeoPixelConnect.h>

// GPIO0: SDA
// GPIO1: SCL
// GPIO2: LED(WS2812)

#define PIN_LED 2
#define PIN_BTN0 5 // adjust to actual design

// RP2040connect
// https://docs.platformio.org/en/stable/boards/raspberrypi/nanorp2040connect.html

// using NeoPixel on rp2040connect
// https://github.com/MrYsLab/NeoPixelConnect

// using I2C on RP2040
// https://qiita.com/totuto/items/81944426dc81ab4b7e57
MbedI2C i2cOLED(p0, p1); // I2C SDA:GP0, SCL:GP1 
NeoPixelConnect p(2, 2); // GPIO2, 2 pixels

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3c
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &i2cOLED, OLED_RESET);
#include "OLEDdraw.inc"

void setup() {
  Serial.begin(9600);

	pinMode(PIN_BTN0, INPUT_PULLUP);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed")); for(;;);
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

	// Draw a single pixel in white
  //display.drawPixel(10, 10, SSD1306_WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  // display.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // display.display(). These examples demonstrate both approaches...
/*
  testdrawline();      // Draw many lines
  testdrawrect();      // Draw rectangles (outlines)
  testfillrect();      // Draw rectangles (filled)
  testdrawcircle();    // Draw circles (outlines)
  testfillcircle();    // Draw circles (filled)
  testdrawroundrect(); // Draw rounded rectangles (outlines)
  testfillroundrect(); // Draw rounded rectangles (filled)
  testdrawtriangle();  // Draw triangles (outlines)
  testfilltriangle();  // Draw triangles (filled)
  testdrawchar();      // Draw characters of the default font
  testdrawstyles();    // Draw 'stylized' characters
  testscrolltext();    // Draw scrolling text
  testdrawbitmap();    // Draw a small bitmap image
  // Invert and restore display, pausing in-between
  display.invertDisplay(true);
  delay(1000);
  display.invertDisplay(false);
//  delay(1000);
//  testanimate(logo_bmp, LOGO_WIDTH, LOGO_HEIGHT); // Animate bitmaps
*/
}

void loop() {
//	p.neoPixelFill(5, 0, 0, true); // 0=Red, 1=Green?
//	p.neoPixelSetValue(0, 5, 0, 0, true); // 0=Red
	p.neoPixelSetValue(0, 0, 0, 5, true); // 0=Blue
//	p.neoPixelSetValue(1, 5, 0, 0, true); // 1=Green
	delay(500);
	p.neoPixelClear();
	delay(500);

/*
	// test for BTN
	if (digitalRead(PIN_BTN0) == 0) p.neoPixelFill(0, 5, 0, true);
	else p.neoPixelClear();
	delay(100);
*/
}
