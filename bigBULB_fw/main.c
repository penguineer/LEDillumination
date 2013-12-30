/* bigBULB - 42x WS2811 / WS2812(B)
 * Copyright (C) 2013 Stefan Schuermans <stefan@blinkenarea.org>
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 * a BlinkenArea project - http://www.blinkenarea.org/
 */

/* bigBULB
 * Copyright 2013 Stefan Schuermans <stefan@blinkenarea.org>
 * Copyleft: CC-BY-SA http://creativecommons.org/licenses/by-sa/3.0/
 */

#include <avr/wdt.h>

#include "animations.h"
#include "leds.h"
#include "timing.h"

/// main code entry point
int main(void)
{
  unsigned char i, gbr[129], *src, *dest;

  // enable watchdog
  wdt_reset();
  //wdt_disable();
  wdt_enable(WDTO_60MS);
  wdt_reset();

  // initialize
  leds_init();
  timing_init();

  // main loop
  while (1) {

    // wait for interval to elapse
    while (!timing_interval_elapsed())
      wdt_reset();

    // play animation
    animations_next();

    // rearrage frame data to output buffer
    src = (unsigned char *)pixels;
    dest = gbr;
    for (i = 0; i < 42; ++i) {
      // RGB -> GBR
      dest[0] = src[1];
      dest[1] = src[0];
      dest[2] = src[2];
      // next pixel
      src += 3;
      dest += 3;
      // move pixel 33 to end (position 41)
      if (i == 32)
        dest += 3;
      if (i == 40)
        dest -= 27;
    }

    // output to LEDs
    leds_out(gbr);

  } // while 1

  return 0;
}

