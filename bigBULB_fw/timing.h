/* bigBULB - 42x WS2811 / WS2812(B)
 * Copyright (C) 2013 Stefan Schuermans <stefan@blinkenarea.org>
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 * a BlinkenArea project - http://www.blinkenarea.org/
 */

/* bigBULB
 * Copyright 2013 Stefan Schuermans <stefan@blinkenarea.org>
 * Copyleft: CC-BY-SA http://creativecommons.org/licenses/by-sa/3.0/
 */

#ifndef TIMING_H
#define TIMING_H

// initialize
void timing_init(void);

// check if interval elapsed
unsigned char timing_interval_elapsed(void);

#endif // #ifndef TIMING_H

