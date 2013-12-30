/* bigBULB - 42x WS2811 / WS2812(B)
 * Copyright (C) 2013 Stefan Schuermans <stefan@blinkenarea.org>
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 * a BlinkenArea project - http://www.blinkenarea.org/
 */

/* bigBULB
 * Copyright 2013 Stefan Schuermans <stefan@blinkenarea.org>
 * Copyleft: CC-BY-SA http://creativecommons.org/licenses/by-sa/3.0/
 */

#include <avr/io.h>

#include "timing.h"

// initialize
void timing_init(void)
{
  // configure timer 0 to 8ms interval
  TCCR0 = 1<<CS02; // 1/256 of sysclock (8MHz) -> increment every 32us
}

// check if interval elapsed
unsigned char timing_interval_elapsed(void)
{
  if (TIFR & 1<<TOV0) {
    TIFR = 1<<TOV0; // clear flag
    return 1; // interval elapsed
  }
  return 0; // interval not yet elpsed
}

