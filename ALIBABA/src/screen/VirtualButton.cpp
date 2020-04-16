#include "../screen/VirtualButton.h"

VirtualButton::VirtualButton(int xx, int yy, int ww, int hh, color c_b,
                             color c_f, std::string s)
    : x(xx), y(yy), w(ww), h(hh), c_border(c_b), c_fill(c_f), lable(s) {

  // calc lable position 
  lable_x = x + (w - lable.length() * LETTER_WIDTH) / 2;
  lable_y = y + (h - LETTER_HEIGHT) / 2 + LETTER_HEIGHT;
  darker(0.15);
}

bool VirtualButton::pressing() {
  if (!Brain.Screen.pressing())
    return false;

  int px = Brain.Screen.xPosition();
  int py = Brain.Screen.yPosition();

  if ((x <= px) && (px <= x + w) && (y <= py) && (py <= y + h))
    return true;
  else
    return false;
}

void VirtualButton::darker(double darker_rate) {
  uint8_t r, g, b;
  rgb_resolve(c_fill.rgb(), r, g,
              b); //获取c_fill的rgb值并分解到r,g,b三个变量上

  r *= darker_rate;
  g *= darker_rate;
  b *= darker_rate;

  uint32_t new_rgb = rgb_compose(r, g, b);
  vex::color c_darker(new_rgb);
  Brain.Screen.drawRectangle(x, y, w, h, c_darker);
  Brain.Screen.printAt(lable_x, lable_y, false, "%s",
                       lable.c_str()); // write lable
}

#include "iostream"
void VirtualButton::brighter() {
  Brain.Screen.drawRectangle(x, y, w, h, c_fill);
  Brain.Screen.printAt(lable_x, lable_y, false, "%s",
                       lable.c_str()); // write lable
}