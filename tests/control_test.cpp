#include <cassert>
#include "../firmware/SmartIncubation/control.h"
int main() {
  ControlState s;
  s = nextState(s, 34.5f); assert(s.bulb && !s.fan);
  s = nextState(s, 34.8f); assert(s.bulb);
  s = nextState(s, 35.0f); assert(!s.bulb);
  s = nextState(s, 38.5f); assert(!s.fan);
  s = nextState(s, 38.6f); assert(s.fan && !s.bulb);
  s = nextState(s, 37.5f); assert(s.fan);
  s = nextState(s, 37.0f); assert(!s.fan);
  s = nextState(s, 33.0f); assert(s.bulb && !s.fan);
  s = nextState(s, 40.0f); assert(!s.bulb && s.fan);
}
