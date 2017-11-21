// This is a demonstration on how to use an input device to trigger changes on your neo pixels.
// You should wire a momentary push button to connect from ground to a digital IO pin.  When you
// press the button it will change to a new pixel animation.  Note that you need to press the
// button once to start the first animation!

#include <Adafruit_NeoPixel.h>

#define BUTTON_PIN   2    // Digital IO pin connected to the button.  This will be
                          // driven with a pull-up resistor so the switch should
                          // pull the pin to ground momentarily.  On a high -> low
                          // transition the button press logic will execute.

#define PIXEL_PIN1   6    // Digital IO pin connected to the NeoPixels.
#define PIXEL_PIN2   7

#define PIXEL_COUNT 24

// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN1, NEO_RGBW + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN2, NEO_RGBW + NEO_KHZ800);

bool oldState = HIGH;
int showType = 0;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  strip1.begin();
  strip1.show();
  strip2.begin();
  strip2.show();// Initialize all pixels to 'off'
}

void loop() {
  // Get current button state.
  bool newState = digitalRead(BUTTON_PIN);

  // Check if state changed from high to low (button press).
  if (newState == LOW && oldState == HIGH) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState = digitalRead(BUTTON_PIN);
    if (newState == LOW) {
      showType++;
      if (showType > 9)
        showType=0;
      startShow(showType);
    }
  }

  // Set the last button state to the old state.
  oldState = newState;
}

void startShow(int i) {
  // while this is running, the button is ignored
  switch(i){
    case 0: 
      theaterChase(strip1.Color(0, 0, 0, 0), 50);    // Black/off
      break;
           
    case 1: 
      theaterChase(strip1.Color(0, 255, 0, 0), 50);  // Red (strip1)
      break;

    case 2: 
      theaterChase(strip1.Color(0x4B, 0x0, 0x82, 0), 70);  // Blue 
      break;

    case 3: 
      theaterChase(strip1.Color(100,255,0,0), 70); // Yellow
      break;
    
    case 4: 
      theaterChase(strip1.Color(0, 0, 0, 0), 50);    // Black/off
      break;
            
    case 5: 
      theaterChase(strip2.Color(8, 158, 148, 0), 50);    // purple
      break;
            
    case 6: 
      theaterChase(strip2.Color(127, 127, 127, 0), 50); // White
      break;

    case 7: 
      theaterChase(strip2.Color(0, 0, 0, 0), 50);    // Black/off
      break;
 
  
  
  }
}

// Fill the dots one after the other with a color
//void colorWipe(uint32_t c, uint8_t wait) {
  //for(uint16_t i=0; i<strip.numPixels(); i++) {
    //strip.setPixelColor(i, c);
    //strip.show();
    //delay(wait);
  //}
//}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  // a frame is 1 move: a "shift"
  for (int frame=0; frame<7; frame++) {
    // the animation is in sets of 3:
    // (1,0,0)...
    // (0,1,0)...
    // (0,0,1)...
    // repeat
    // So, "on" is +0, +1, +2
    // And off is +1/+2, +2/+0, +0,+1
    // Which is modulus arithmetic on 3
    // I.e. wrap around
    int on = frame % 3;    // +0,+1,+2
    off1 = (frame + 1) % 3 // +1,+2,+0
    off2 = (frame + 2) % 3 // +2,+0,+1

    // across all the pixels, one set of 3 at a time
    for (int p=0; p < strip1.numPixels(); p += 3) {
      // one set of 3
      strip1.setPixelColor(on, c);
      strip1.setPixelColor(off1, black);
      strip1.setPixelColor(off2, black);
      strip2.setPixelColor(on, c);
      strip2.setPixelColor(off1, black);
      strip2.setPixelColor(off2, black);
    }
    strip1.show();
    strip2.show();
    delay(wait); // between frames
  }
}

