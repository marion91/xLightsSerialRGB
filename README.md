# xLightsSerialRGB

Enables xLights control of addressable RGB LEDs via xLights Generic Serial protocol and FastLED library for Arduino.

FastLED is implemented in a multi-strip configuration allowing for 1-8 outputs, though you can add more just by defining them in the header and in setup(). 

Channels are parsed 3 at a time (RGB) and sent out sequentially across all LEDS and ports, so models can be split between two ports as long as they are sequential eg.(5,6).
All channels are parsed out to LEDS in the same order as they are received by xLights.



All user-defined variables are shown below:

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

const char start_char = '<'; // Set serial delimiter here and in xLights
//const char end_char = '>'; // Not used, as some colour bytes can trigger this. Use dynamic BUFF_SIZE instead to force exact number of channels
