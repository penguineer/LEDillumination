/* bigBULB - 42x WS2811 / WS2812(B)
 * Copyright (C) 2013 Stefan Schuermans <stefan@blinkenarea.org>
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 * a BlinkenArea project - http://www.blinkenarea.org/
 */

/* bigBULB
 * Copyright 2013 Stefan Schuermans <stefan@blinkenarea.org>
 * Copyleft: CC-BY-SA http://creativecommons.org/licenses/by-sa/3.0/
 */

#ifndef LEDS_H
#define LEDS_H

// initialize
void leds_init(void);

// output GBR values to 42 LEDs
void leds_out(unsigned char data[126]);

#endif // #ifdef LEDS_H

