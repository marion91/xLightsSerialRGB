#include <FastLED.h>

#define BAUDRATE 1000000 // Set baud rate here and in xLights, faster speeds are needed for more lights
#define TOTAL_BUFF_SIZE 1024 // Set max channels that can be received. Can set to a lower number if memory is needed elsewhere. 

//Define the pins you plan to use
#define DATA_PIN_1 5
#define DATA_PIN_2 6
#define DATA_PIN_3 7
#define DATA_PIN_4 8
#define DATA_PIN_5 9
#define DATA_PIN_6 10
#define DATA_PIN_7 11
#define DATA_PIN_8 12

// Set number of LEDS on each port. Models can be split between sequential ports. 
// Errors in light colours will occur if total amount does not match the number of channels (divided by 3 for RGB) sent by xLights.
const int NUM_LEDS[] = {50, 0};
const int NUM_STRIPS = sizeof(NUM_LEDS);
CRGB leds[NUM_STRIPS][0];

const char start_char = '<'; // Set serial delimiter here and in xLights
//const char end_char = '>'; // Not used, as some colour bytes can trigger this. Use dynamic BUFF_SIZE instead to force exact number of channels

char buf[TOTAL_BUFF_SIZE];
int BUFF_SIZE = 0;

void showLEDS(char buf[TOTAL_BUFF_SIZE]) {
  int buf_index = 0;
  for(int strip_num = 0; strip_num < NUM_STRIPS; strip_num++){
    for (int index = 0; index < NUM_LEDS[strip_num]; index ++) {
      if (buf_index > BUFF_SIZE) continue;
      leds[strip_num][index] = CRGB(buf[buf_index], buf[buf_index + 1], buf[buf_index + 2]);
      buf_index += 3;
    }
  }
  FastLED.show();  // Display the frame after processing all channels
}

void setup() {
  Serial.begin(BAUDRATE);
  for (int i = 0; i < sizeof(NUM_LEDS); i++) 
    BUFF_SIZE += NUM_LEDS[i];
  BUFF_SIZE *= 3;

    if (sizeof(NUM_LEDS) >= 1)
      //FastLED.addLeds<WS2812, DATA_PIN_1, GRB>(leds[0], NUM_LEDS[0]); //Fairy Lights
      FastLED.addLeds<WS2812, DATA_PIN_1, RGB>(leds[0], NUM_LEDS[0]); //String Lights
    if (sizeof(NUM_LEDS) >= 2)
      //FastLED.addLeds<WS2812, DATA_PIN_2, GRB>(leds[1], NUM_LEDS[1]); //Fairy Lights  
      FastLED.addLeds<WS2812, DATA_PIN_2, RGB>(leds[1], NUM_LEDS[1]); //String Lights
    if (sizeof(NUM_LEDS) >= 3)
      //FastLED.addLeds<WS2812, DATA_PIN_3, GRB>(leds[2], NUM_LEDS[2]); //Fairy Lights
      FastLED.addLeds<WS2812, DATA_PIN_3, RGB>(leds[2], NUM_LEDS[2]); //String Lights
    if (sizeof(NUM_LEDS) >= 4)
      FastLED.addLeds<WS2812, DATA_PIN_4, GRB>(leds[3], NUM_LEDS[3]); //Fairy Lights
      //FastLED.addLeds<WS2812, DATA_PIN_4, RGB>(leds[3], NUM_LEDS[3]); //String Lights
    if (sizeof(NUM_LEDS) >= 5)
      //FastLED.addLeds<WS2812, DATA_PIN_5, GRB>(leds[4], NUM_LEDS[4]); //Fairy Lights
      FastLED.addLeds<WS2812, DATA_PIN_5, RGB>(leds[4], NUM_LEDS[4]); //String Lights
    if (sizeof(NUM_LEDS) >= 6)
      //FastLED.addLeds<WS2812, DATA_PIN_5, GRB>(leds[5], NUM_LEDS[5]); //Fairy Lights
      FastLED.addLeds<WS2812, DATA_PIN_6, RGB>(leds[5], NUM_LEDS[5]); //String Lights
    if (sizeof(NUM_LEDS) >= 7)
      //FastLED.addLeds<WS2812, DATA_PIN_5, GRB>(leds[6], NUM_LEDS[6]); //Fairy Lights
      FastLED.addLeds<WS2812, DATA_PIN_7, RGB>(leds[6], NUM_LEDS[6]); //String Lights
    if (sizeof(NUM_LEDS) >= 8)
      //FastLED.addLeds<WS2812, DATA_PIN_5, GRB>(leds[7], NUM_LEDS[7]); //Fairy Lights
      FastLED.addLeds<WS2812, DATA_PIN_8, RGB>(leds[7], NUM_LEDS[7]); //String Lights
}

void loop() {
  if (Serial.available()) {
    while (Serial.read() != start_char); // Wait for start_char and discard it
    Serial.readBytes(buf, BUFF_SIZE); // Save remaining bytes into channel buffer
    showLEDS(buf);
  }
}