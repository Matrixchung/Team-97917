#include "../Globals/Globals.h"
#include <string>

// screen size: 480x240
#define LCD_MAX_X 480
#define LCD_MAX_Y 240

#define LETTER_WIDTH 10
#define LETTER_HEIGHT 15

class VirtualButton {
public:
  int x, y;
  int w, h;
  color c_border, c_fill;
  std::string lable = "";

  int lable_x,lable_y;

public:
  VirtualButton(){};
  VirtualButton(int xx, int yy, int ww, int hh, color c_b, color c_f,
                std::string s);
  bool pressing();

private:
  uint32_t rgb_compose(uint8_t v_r, uint8_t v_g, uint8_t v_b) {
    uint32_t rgb = (v_r << 16) + (v_g << 8) + (v_b << 0);
    return rgb;
  }

  void rgb_resolve(uint32_t rgb_v, uint8_t &rr, uint8_t &gg, uint8_t &bb) {
    rr = (rgb_v >> 16) & 0xff;
    gg = (rgb_v >> 8) & 0xff;
    bb = (rgb_v >> 0) & 0xff;
  }

public:
  void darker(double darker_rate = 0.4);
  void brighter();
};
