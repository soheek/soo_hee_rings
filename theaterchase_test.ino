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
  switch(i){
    case 0: theaterChase(strip1.Color(0, 0, 0, 0), 50);    // Black/off
           
    case 1: theaterChase(strip1.Color(0, 255, 0, 0), 50);  // Red (strip1)

    case 2: theaterChase(strip1.Color(0x4B, 0x0, 0x82, 0), 70);  // Blue 

    case 3: theaterChase(strip1.Color(100,255,0,0), 70); // Yellow
    
    case 4: theaterChase(strip1.Color(0, 0, 0, 0), 50);    // Black/off
            
            
    case 5: theaterChase(strip2.Color(8, 158, 148, 0), 50);    // purple
            
            
    case 6: theaterChase(strip2.Color(127, 127, 127, 0), 50); // White

    case 7: theaterChase(strip2.Color(0, 0, 0, 0), 50);    // Black/off
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
  for (int j=0; j<7; j++) {  //do 7 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip1.numPixels(); i=i+3) {
        strip1.setPixelColor(i+q, c);
        strip2.setPixelColor(i+q, c);//turn every third pixel on
      }
      strip1.show();
      strip2.show();

      delay(wait);

      for (int i=0; i < strip1.numPixels(); i=i+3)
      for (int i=0; i < strip2.numPixels(); i=i+3){
        strip1.setPixelColor(i+q, 0);
        strip2.setPixelColor(i+q, 0);//turn every third pixel off
      }
    }
  }
}

