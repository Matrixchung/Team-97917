#include "vex.h"

void wait(int milsec)
{
   vex::this_thread::sleep_for(milsec);
}


int sgn(double x) {
  if (x > 0)
    return 1;
  else if (x < 0)
    return -1;
  else
    return 0;
}

void max_limit(int &x, unsigned int bnd) {
  if (abs(x) > bnd)
    x = sgn(x) * bnd;
}

void zero_blind(int &x, unsigned int threshold) {
  if (abs(x) < threshold)
    x = 0;
}
