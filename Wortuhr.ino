/*

Wortuhr_FastLED

based on D1 mini (LED: D3)
and DS1302 RTC (Rst: D6, IO: D7, CLK: D8)

*/

#include <FastLED.h>
#include <Time.h>
#include <DS1302.h>

#define WORDCLOCK_TEST 1

void setup() {
  // Setup Serial connection for debug
  Serial.begin(9600);
#ifdef WORDCLOCK_TEST
  Serial.println("Test mode");
#endif
  delay( 3000 ); // power-up safety delay
#ifdef WORDCLOCK_TEST
  Serial.println("LEDs setup");
#endif
  leds_setup();
#ifdef WORDCLOCK_TEST
  Serial.println("RTC setup");
#endif
  rtc_setup();
  delay(2000);
}

// Loop through changing R, G, and B colors
// Each color fades in from off (i=0) to fully on (i=255)
void loop() {
  int stunde;
  int minute;
#ifdef WORDCLOCK_TEST
  for (int stunde = 0; stunde < 24; stunde++) {
    for (int minute = 0; minute < 60; minute += 5) {
#else
  stunde = rtc_read(0);
  minute = rtc_read(1);
#endif
  Serial.print("Zeit ");
  Serial.print(stunde);
  Serial.write(':');
  Serial.print(minute);
  Serial.println();
  leds_set(stunde, minute);
#ifdef WORDCLOCK_TEST
      delay(1000);
    }
  }
#else
  delay(10000);
#endif
}
