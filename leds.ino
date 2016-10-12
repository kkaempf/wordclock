// actual RGB values for FastLed
CRGB leds[NUM_LEDS];

// current on/off state
boolean current_leds[NUM_LEDS];
// next on/off state
boolean next_leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

void leds_set_next_word(byte *word_p) {
  int start = *word_p++;
  int len = *word_p;
  for(int i = start; i < start+len; i++) {
    next_leds[i] = true;
  }
}

void leds_fade(uint8_t start, uint8_t count) {
  Serial.print("fade start ");
  Serial.print(start);
  Serial.print(" ");
  Serial.print(count);
  Serial.println(" leds");
  fadeToBlackBy(leds+start, count, 10);
  FastLED.show();
}


//
// copy next_leds to current_leds to leds by fading
void leds_make_next_current() {
  Serial.println("make_next_current");
  for (uint8_t scale = 0; scale < 5; scale++) {
    uint8_t count = 0;
    uint8_t start = 0;
    for (uint8_t i = 0; i < NUM_LEDS; i++) {
      if (current_leds[i] == next_leds[i]) {
        if (count > 0) {
          leds_fade(start, count);
          count = 0;
        }
        start = i;
      }
      else {
        count++;
      }
    }
    if (count > 0) {
      leds_fade(start, count);
    }    
  }
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    current_leds[i] = next_leds[i];
    next_leds[i] = false;
    if (current_leds[i]) {
      leds[i] = CRGB::White;
    }
    else {
      leds[i] = CRGB::Black;
    }
  }
  FastLED.show();
}

void leds_setup() {
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(  BRIGHTNESS );
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    current_leds[i] = false;
    next_leds[i] = false;
  }
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
  leds_set_next_word(w_es);
  leds_set_next_word(w_ist);
  m = minute / 5;
  leds_set_next_word(a_minuten[m]); /* fuenf, zehn, viertel, ... */
  if (minute < 5) {
    // skip
  }
  else if (minute < 25) {
    leds_set_next_word(w_nach);
  }
  else if (minute < 30) {
    leds_set_next_word(w_vor);
    leds_set_next_word(w_halb);
    s++;
  }
  else if ((minute >= 35) && (minute < 40)) {
    leds_set_next_word(w_nach);
    leds_set_next_word(w_halb);
    s++;
  }
  else if (minute >= 40) {
    leds_set_next_word(w_vor);
    s++;
  }
  if (s > 11) {
    s = 0;
  }
  leds_set_next_word(a_stunden[s]);
  if ((s == 1) && (minute < 5)) {
    /* eins -> ein */
    next_leds[99] = false;
  }
  leds_make_next_current();
}
