#pragma once
// Reconstructed from the supplied report; values are historical project settings.
struct ControlState { bool bulb = false; bool fan = false; };
inline ControlState nextState(ControlState state, float temperature) {
  if (temperature <= 34.5f) state.bulb = true;
  else if (temperature >= 35.0f) state.bulb = false;
  if (temperature > 38.5f) state.fan = true;
  else if (temperature <= 37.0f) state.fan = false;
  return state;
}
