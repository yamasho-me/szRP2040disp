#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>

// GPIO0: SDA
// GPIO1: SCL
// GPIO2: LED(WS2812)

#define PIN_SDA  0
#define PIN_SCL  1

/* for other boards:
             LED    BTN
   cui2      8(x4)  6(SW3)/7(SW4)
   tanaka    -
   ishii     -
   yamasho   2
   ogawa     2(x8)
   kojima    2
   kobayashi        4(U4)/2(U5)

 */

#define NO_LED

#define PIN_LED  2 // adjust to actual design
#define PIN_BTN0 2 // adjust to actual design
#define PIN_BTN1 4 // adjust to actual design

/*
// RP2040connect
// https://docs.platformio.org/en/stable/boards/raspberrypi/nanorp2040connect.html
// using NeoPixel on rp2040connect
// https://github.com/MrYsLab/NeoPixelConnect
// using I2C on RP2040
// https://qiita.com/totuto/items/81944426dc81ab4b7e57
*/

#ifndef NO_LED
#define NUM_PIXELS 8 // number of pixels
Adafruit_NeoPixel led = Adafruit_NeoPixel(NUM_PIXELS, PIN_LED, NEO_RGBW + NEO_KHZ800); // XL-5050RGBWC-WS2812B
uint8_t led_r, led_g, led_b;
#include "LED.inc"
#endif

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3c
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#include "OLEDdraw.inc"

void setup()
{
  Serial.begin(9600);

  pinMode(PIN_BTN0, INPUT_PULLUP);

  // I2C SDA:GP0, SCL:GP1
  Wire.setSDA(PIN_SDA); Wire.setSCL(PIN_SCL);
  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

#ifndef NO_LED
  // init leds
  led.begin();
  led.clear();
  led.show();
#endif

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Draw a single pixel in white
  // display.drawPixel(10, 10, SSD1306_WHITE);

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

uint16_t baseHue = 0;

void loop()
{
/*
	led.setPixelColor(0, led.Color(5, 0, 0));
	led.setPixelColor(1, led.Color(0, 0, 0));
  led.show();
  delay(500);
	led.setPixelColor(0, led.Color(0, 0, 0));
	led.setPixelColor(1, led.Color(0, 5, 0));
  led.show();
  delay(500);
	led.fill(led.Color(0, 0, 5));
	led.show();
  delay(500);
*/

#ifndef NO_LED
#define LED_BRIGHTNESS 10
  for (unsigned int i = 0; i < NUM_PIXELS; i++)
  {
	  setColorHSV(map(i, 0, NUM_PIXELS, 0, 65535) + (unsigned int)baseHue, 250, LED_BRIGHTNESS);
	  if (digitalRead(PIN_BTN0) == 1){ // if button NOT pressed
    	led.setPixelColor(i, led.Color(led_r, led_g, led_b));
		}
  }
	led.show();
  delay(10);
	baseHue += 0x100;
#endif
	if (digitalRead(PIN_BTN0) == 0){ // if BTN0 pressed
		display.invertDisplay(true);
	}
	else{
		display.invertDisplay(false);
	}
	delay(100);
}
