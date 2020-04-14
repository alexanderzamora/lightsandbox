#include <Adafruit_NeoPixel.h>
#include "IRremote.h"
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN    6
#define LED_COUNT 60

int receiver = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11
int stripState;


IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// legend
uint32_t OFF = strip.Color(0  , 0,   0  ); // 0
uint32_t RED = strip.Color(255, 0,   0  ); // 1
uint32_t MAG = strip.Color(255, 0,   255); // 2
uint32_t BLU = strip.Color(0,   0,   255); // 3
uint32_t TEA = strip.Color(0,   255, 255); // 4
uint32_t GRE = strip.Color(0,   255, 0  ); // 5
uint32_t YEL = strip.Color(255, 255, 0  ); // 6

void setup() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(100); // Set BRIGHTNESS to about 1/5 (max = 255)
  stripState = 2;
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver

}

void loop() {
  if (irrecv.decode(&results)){
    translateIR(); 
    irrecv.resume(); // receive the next value
  }  
}

void translateIR() {
  switch(results.value){
    case 0xFFA25D: Serial.println("POWER"); break;
    case 0xFFE21D: Serial.println("FUNC/STOP"); break;
    case 0xFF629D: Serial.println("VOL+"); break;
    case 0xFF22DD: Serial.println("FAST BACK");    break;
    case 0xFF02FD: Serial.println("PAUSE");    break;
    case 0xFFC23D: Serial.println("FAST FORWARD");   break;
    case 0xFFE01F: Serial.println("DOWN");    break;
    case 0xFFA857: Serial.println("VOL-");    break;
    case 0xFF906F: Serial.println("UP");    break;
    case 0xFF9867: Serial.println("EQ");    break;
    case 0xFFB04F: Serial.println("ST/REPT");    break;
    case 0xFF6897: Serial.println("0"); Solid(OFF);    break;
    case 0xFF30CF: Serial.println("1"); Solid(RED);    break;
    case 0xFF18E7: Serial.println("2"); Solid(MAG);    break;
    case 0xFF7A85: Serial.println("3"); Solid(BLU);    break;
    case 0xFF10EF: Serial.println("4"); Solid(TEA);    break;
    case 0xFF38C7: Serial.println("5"); Solid(GRE);    break;
    case 0xFF5AA5: Serial.println("6"); Solid(YEL);    break;
    case 0xFF42BD: Serial.println("7");    break;
    case 0xFF4AB5: Serial.println("8");    break;
    case 0xFF52AD: Serial.println("9");    break;
    case 0xFFFFFFFF: Serial.println(" REPEAT");break;  
  
    default: 
      Serial.println(" other button : ");
      Serial.println(results.value);

  }
  delay(100);
}

void Solid(uint32_t color) {
  for(int i=0; i<LED_COUNT; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}
