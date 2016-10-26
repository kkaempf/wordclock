#include <Arduino.h>
#include <FastLED.h>

#include "hardware.h"
#include "leds.h"
#include "led_matrix.h"

// actual RGB values for FastLed
CRGB leds[NUM_LEDS];


// +1/-1 change for leds
int8_t change_leds[NUM_LEDS];

#define FADE_IN 1
#define FADE_OUT -1

void no_change()
{
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    change_leds[i] = 0;
  }  
}

void leds_set_word(byte *word_p) {
  int start = *word_p++;
  int len = *word_p;
  for(int i = start; i < start+len; i++) {
    change_leds[i] = FADE_IN;
  }
}

//
// apply change_leds to current_leds to leds by fading
//
void leds_apply() {
  Serial.println("apply");

  // fully setup change_leds
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
     if (leds[i]) {
       // leds is 'on'
       if (change_leds[i] == 0) {
         // must be dimmed down
         change_leds[i] = FADE_OUT;
       }
       else if (change_leds[i] == FADE_IN) {
         // stays on
         change_leds[i] = 0;
       }
     }
  }
#define FADE_STEPS 20
  // apply change_leds to leds
  int rate = BRIGHTNESS / FADE_STEPS + 1;
  CRGB r = CRGB(rate,rate,rate);
  for (uint8_t s = 0; s < FADE_STEPS; s++) {
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      if (change_leds[i] == FADE_IN) {
        leds[i] += r;
      }
      else if (change_leds[i] == FADE_OUT) {
        leds[i] -= r;
      }
    }
    FastLED.show();
    delay(30);
  }
  no_change();
}

void leds_setup() {
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(  BRIGHTNESS );
  no_change();
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  delay(500);  
}

void leds_set(int stunde, int minute) {
  int s;
  int m;
#ifdef WORDCLOCK_TEST
  Serial.println("Setting LEDs");
#endif
  s = stunde;
  if (s > 12) {
    s = s - 12;
  }
  leds_set_word(w_es);
  leds_set_word(w_ist);
  m = minute / 5;
  leds_set_word(a_minuten[m]); /* fuenf, zehn, viertel, ... */
  if (minute < 5) {
    // skip
  }
  else if (minute < 25) {
    leds_set_word(w_nach);
  }
  else if (minute < 30) {
    leds_set_word(w_vor);
    leds_set_word(w_halb);
    s++;
  }
  else if (minute < 35) {
    leds_set_word(w_halb);
    s++;    
  }
  else if ((minute >= 35) && (minute < 40)) {
    leds_set_word(w_nach);
    leds_set_word(w_halb);
    s++;
  }
  else if (minute >= 40) {
    leds_set_word(w_vor);
    s++;
  }
  if (s > 11) {
    s = 0;
  }
  leds_set_word(a_stunden[s]);
  if ((s == 1) && (minute < 5)) {
    /* eins -> ein */
    change_leds[99] = FADE_OUT;
  }
  leds_apply();
}
