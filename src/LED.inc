unsigned char sinTable[46] = {0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};

void setColorHSV(unsigned int hue, unsigned char sat, unsigned char val) {
  hue = (hue * 1530L + 32768) / 65536;
  if (hue < 510) { // Red to Green-1
    led_b = 0;
    if (hue < 255) { //   Red to Yellow-1
      led_r = 255;
      led_g = hue;       //     g = 0 to 254
    } else {         //   Yellow to Green-1
      led_r = 510 - hue; //     r = 255 to 1
      led_g = 255;
    }
  } else if (hue < 1020) { // Green to Blue-1
    led_r = 0;
    if (hue < 765) { //   Green to Cyan-1
      led_g = 255;
      led_b = hue - 510;  //     b = 0 to 254
    } else {          //   Cyan to Blue-1
      led_g = 1020 - hue; //     g = 255 to 1
      led_b = 255;
    }
  } else if (hue < 1530) { // Blue to Red-1
    led_g = 0;
    if (hue < 1275) { //   Blue to Magenta-1
      led_r = hue - 1020; //     r = 0 to 254
      led_b = 255;
    } else { //   Magenta to Red-1
      led_r = 255;
      led_b = 1530 - hue; //     b = 255 to 1
    }
  } else { // Last 0.5 Red (quicker than % operator)
    led_r = 255;
    led_g = led_b = 0;
  }

  // Apply saturation and value to R,G,B, pack into 32-bit result:
  unsigned long v1 = 1 + val;  // 1 to 256; allows >>8 instead of /255
  unsigned int s1 = 1 + sat;  // 1 to 256; same reason
  unsigned char s2 = 255 - sat; // 255 to 0

  led_r = (((((led_r * s1) >> 8) + s2) * v1) >> 8);
  led_g = (((((led_g * s1) >> 8) + s2) * v1) >> 8);
  led_b = (((((led_b * s1) >> 8) + s2) * v1) >> 8);
}

/*
// hue = 0-179(360/2)
void setRGB(unsigned int hue, unsigned char sat, unsigned char val) {
  for (unsigned char i = 0; i < NUM_LEDS; i++) {
    setColorHSV(hue, sat, val);
    setPixel(i, led_r, led_g, led_b); //Choose the color order depending on the LED you use
    hue += 655;
  }
  showPixels();
}
*/

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
