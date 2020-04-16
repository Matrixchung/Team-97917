#include "../Display/screen.h"
using namespace vex;
void display()
{
  while(1)
  {
    screen_display_choose();
    //sensor_display();
    task::sleep(50);
  }
}