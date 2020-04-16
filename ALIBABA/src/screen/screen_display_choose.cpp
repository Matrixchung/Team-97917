#include "../Globals/Globals.h"
#include "../screen/VirtualButton.h"

// button intances
VirtualButton vb_red1;  // bv:0
VirtualButton vb_red2;  // bv:1
VirtualButton vb_blue1; // bv:2
VirtualButton vb_blue2; // bv:3
VirtualButton vb_route;
/////////////////////////////////////////////////
//
void highlighting_init() {
  switch (auto_info.side + auto_info.role) {
  case 0:
    vb_red1.brighter();
    break;
  case 1:
    vb_red2.brighter();
    break;
  case 2:
    vb_blue1.brighter();
    break;
  case 3:
    vb_blue2.brighter();
    break;
  default:
    break;
  }
}
////////////////////////////////////////////////
void route_number_corrent() {
  if (auto_info.role == ROLE_ONE &&
      auto_info.route_number > ROLE_ONE_MAX_AUTO_NUMBER)
    auto_info.route_number = 1;
  if (auto_info.role == ROLE_TWO &&
      auto_info.route_number > ROLE_TWO_MAX_AUTO_NUMBER)
    auto_info.route_number = 1;
}
/////////////////////////////////////////////////
void update_auto_info_display() {
  int line_x = 250;
  int line_y = 45;
  if (auto_info.side == SIDE_RED)
    Brain.Screen.printAt(line_x, line_y, "RED  ");
  else
    Brain.Screen.printAt(line_x, line_y, "BLUE  ");

  if (auto_info.role == ROLE_ONE)
    Brain.Screen.printAt(line_x + 5 * LETTER_WIDTH, line_y, "ONE  ");
  else
    Brain.Screen.printAt(line_x + 5 * LETTER_WIDTH, line_y, "TWO  ");

  Brain.Screen.printAt(line_x + 9 * LETTER_WIDTH, line_y, "%d",
                       auto_info.route_number);
}
/////////////////////////////////////////////////////////////////////////////////////////
void darker_highlighting(int current_brighter_btn_val) {
  if (current_brighter_btn_val != -1) {
    switch (current_brighter_btn_val) {
    case 0:
      vb_red1.darker();
      break;
    case 1:
      vb_red2.darker();
      break;
    case 2:
      vb_blue1.darker();
      break;
    case 3:
      vb_blue2.darker();
      break;
    default:
      break;
    }
  }
}
/////////////////////////////////////////
void buttons_init() {

  int width = 100, height = 45;
  int red_x = 250, blue_x = red_x + width + 15;
  int y_1 = 120, y_2 = y_1 + height + 15;

  vb_red1 = VirtualButton(red_x, y_1, width, height, color::white, color::red,
                          "RED ONE"); // bv:0
  vb_red2 = VirtualButton(red_x, y_2, width, height, color::white, color::red,
                          "RED TWO"); // bv:1
  vb_blue1 =
      VirtualButton(blue_x, y_1, width, height, color::white, color::blue,
                    "BLUE ONE"); // bv:2
  vb_blue2 =
      VirtualButton(blue_x, y_2, width, height, color::white, color::blue,
                    "BLUE TWO"); // bv:3
  vb_route = VirtualButton(red_x, y_1 - height - 15, width * 2 + 15, height,
                           color::white, color::white, "ROUTE");

  highlighting_init();
  update_auto_info_display();
}

////////////////////////////////////////////////////////////////
void screen_display_choose() {

  static int bv = auto_info.side + auto_info.role;

  if (1) {
    // choose red
    if (bv != 0 && vb_red1.pressing()) {
      vb_red1.brighter();
      auto_info.role = ROLE_ONE;
      auto_info.side = SIDE_RED;
      darker_highlighting(bv);
      bv = 0; // change bv
      route_number_corrent();
      update_auto_info_display();
    }
    if (bv != 1 && vb_red2.pressing()) {
      vb_red2.brighter();
      auto_info.role = ROLE_TWO;
      auto_info.side = SIDE_RED;
      darker_highlighting(bv);
      bv = 1; // change bv
      route_number_corrent();
      update_auto_info_display();
    }
    // choose blue
    if (bv != 2 && vb_blue1.pressing()) {
      vb_blue1.brighter();
      auto_info.side = SIDE_BLUE;
      auto_info.role = ROLE_ONE;
      darker_highlighting(bv);
      bv = 2; // change bv
      route_number_corrent();
      update_auto_info_display();
    }
    if (bv != 3 && vb_blue2.pressing()) {
      vb_blue2.brighter();
      auto_info.role = ROLE_TWO;
      auto_info.side = SIDE_BLUE;
      darker_highlighting(bv);
      bv = 3; // change bv
      route_number_corrent();
      update_auto_info_display();
    }
  } // side and role

  if (vb_route.pressing()) {
    vb_route.brighter();
    auto_info.route_number++;

    route_number_corrent();

    update_auto_info_display();
    while (vb_route.pressing()) {
    };
    vb_route.darker();

  } // number
}
