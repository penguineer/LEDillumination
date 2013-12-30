/* bigBULB - 42x WS2811 / WS2812(B)
 * Copyright (C) 2013 Stefan Schuermans <stefan@blinkenarea.org>
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 * a BlinkenArea project - http://www.blinkenarea.org/
 */

#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#define PIXEL_CNT (42)

struct pixel {
  unsigned char r, g, b;
};

extern struct pixel pixels[PIXEL_CNT];

/// calculate next animation frame
void animations_next(void);

#endif // #ifndef ANIMATIONS_H

