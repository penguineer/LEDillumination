/* bigBULB - 42x WS2811 / WS2812(B)
 * Copyright (C) 2013 Stefan Schuermans <stefan@blinkenarea.org>
 * Copyleft: GNU public license - http://www.gnu.org/copyleft/gpl.html
 * a BlinkenArea project - http://www.blinkenarea.org/
 */

#include "animations.h"

struct pixel pixels[PIXEL_CNT] = {}; // all black at begin

/// current animation number
unsigned int ani_no = 0;

/// number of times the current animation has been repeated
unsigned int ani_rep = 0;

/// current step in animation
unsigned int ani_step = 0;

/// second step counter, to be abused by current animation
unsigned int ani_step_2 = 0;

/// delay of current frame in 10ms
unsigned int ani_delay = 0;

/// go to next animation
void ani_go_to_next_ani(void);

/// get rainbow color
#define ANI_HELPER_RAINBOW_CNT (0x600)
struct pixel ani_helper_rainbow(unsigned int step)
{
  unsigned char phase = step >> 8;
  unsigned char substep = step & 0xFF;
  struct pixel color = {0, 0, 0};
  switch (phase) {
    case 0:
      color.r = 255;
      color.g = substep;
      color.b = 0;
      break;
    case 1:
      color.r = 255 - substep;
      color.g = 255;
      color.b = 0;
      break;
    case 2:
      color.r = 0;
      color.g = 255;
      color.b = substep;
      break;
    case 3:
      color.r = 0;
      color.g = 255 - substep;
      color.b = 255;
      break;
    case 4:
      color.r = substep;
      color.g = 0;
      color.b = 255;
      break;
    case 5:
      color.r = 255;
      color.g = 0;
      color.b = 255 - substep;
      break;
  }
  return color;
}

/// set all pixels to same color
void ani_helper_color(unsigned char r, unsigned char g, unsigned char b)
{
  unsigned int i;
  for (i = 0; i < PIXEL_CNT; ++i) {
    pixels[i].r = r;
    pixels[i].g = g;
    pixels[i].b = b;
  }
}

/// set all pixels to same gray level
void ani_helper_gray(unsigned char val)
{
  ani_helper_color(val, val, val);
}

/// turn all pixels off
void ani_helper_off(void)
{
  ani_helper_gray(0);
}

/// fade out all pixels
void ani_helper_fade_pixel(unsigned char pix)
{
  if (pixels[pix].r > 0)
    pixels[pix].r -= 1 + (pixels[pix].r >> 3);
  if (pixels[pix].g > 0)
    pixels[pix].g -= 1 + (pixels[pix].g >> 3);
  if (pixels[pix].b > 0)
    pixels[pix].b -= 1 + (pixels[pix].b >> 3);
}

/// fade out all pixels
void ani_helper_fade_all(void)
{
  unsigned char i;
  for (i = 0; i < PIXEL_CNT; ++i)
    ani_helper_fade_pixel(i);
}

/// running light animation
void ani_run(void)
{
  // all pixels off by default
  ani_helper_off();

  // turn on one pixel
  pixels[ani_step].r = 234;
  pixels[ani_step].g = 123;
  pixels[ani_step].b = 0;

  // duration 100ms
  ani_delay = 10;

  // next step / next animation
  ++ani_step;
  if (ani_step >= PIXEL_CNT)
    ani_go_to_next_ani();
}

/// backwards running light animation
void ani_run_back(void)
{
  // all pixels off by default
  ani_helper_off();

  // turn on one pixel
  pixels[PIXEL_CNT - 1 - ani_step].r = 234;
  pixels[PIXEL_CNT - 1 - ani_step].g = 123;
  pixels[PIXEL_CNT - 1 - ani_step].b = 0;

  // duration 100ms
  ani_delay = 10;

  // next step / next animation
  ++ani_step;
  if (ani_step >= PIXEL_CNT)
    ani_go_to_next_ani();
}

/// blink red animation
void ani_blink_red(void)
{
  // all pixels off (1st frame) or on (2nd frame) by default
  ani_helper_color(ani_step ? 255 : 0, 0, 0);

  // duration 500ms
  ani_delay = 50;

  // next step / next animation
  ++ani_step;
  if (ani_step >= 2)
    ani_go_to_next_ani();
}

/// blink green animation
void ani_blink_green(void)
{
  // all pixels off (1st frame) or on (2nd frame) by default
  ani_helper_color(0, ani_step ? 255 : 0, 0);

  // duration 500ms
  ani_delay = 50;

  // next step / next animation
  ++ani_step;
  if (ani_step >= 2)
    ani_go_to_next_ani();
}

/// blink blue animation
void ani_blink_blue(void)
{
  // all pixels off (1st frame) or on (2nd frame) by default
  ani_helper_color(0, 0, ani_step ? 255 : 0);

  // duration 500ms
  ani_delay = 50;

  // next step / next animation
  ++ani_step;
  if (ani_step >= 2)
    ani_go_to_next_ani();
}

/// blink white animation
void ani_blink_white(void)
{
  // all pixels off (1st frame) or on (2nd frame) by default
  ani_helper_gray(ani_step ? 255 : 0);

  // duration 500ms
  ani_delay = 50;

  // next step / next animation
  ++ani_step;
  if (ani_step >= 2)
    ani_go_to_next_ani();
}

/// rainbow animation
void ani_rainbow(void)
{
  // fade out
  ani_helper_fade_all();

  // turn on next pixel in rainbow color
  pixels[ani_step] = ani_helper_rainbow(ani_step * (ANI_HELPER_RAINBOW_CNT /
                                                    PIXEL_CNT));

  // duration 100ms
  ani_delay = 10;

  // next step / next animation
  ++ani_step;
  if (ani_step >= PIXEL_CNT)
    ani_step = 0;
}

/// animation list
struct ani_list_entry {
  void (*func)(void); ///< animation function
  unsigned int rep; ///< repetition count
} ani_list[] = {
  //{ ani_run, 3 },
  //{ ani_blink_red, 1 },
  //{ ani_blink_green, 1 },
  //{ ani_blink_blue, 1 },
  //{ ani_run_back, 2 },
  //{ ani_blink_white, 3 },
  { ani_rainbow, 1 },
};

/// go to next animation
void ani_go_to_next_ani()
{
  // new animation starts with first step
  ani_step = 0;
  ani_step_2 = 0;

  // next repetition
  ++ani_rep;
  if (ani_rep < ani_list[ani_no].rep)
    return;

  // new animation has not been repeated yet
  ani_rep = 0;

  // next animation
  ++ani_no;
  // first animation after last
  if (ani_no >= sizeof(ani_list) / sizeof(ani_list[0]))
    ani_no = 0;

}

/// calculate next animation frame
void animations_next()
{
  // delay for current frame
  if (ani_delay > 0) {
    --ani_delay;
    return;
  }

  // call animation function
  ani_list[ani_no].func();
}

