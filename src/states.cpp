#include "states.hpp"

// Define the global variable `currentState`
volatile system_state currentState = INIT;
flags_t systemFlags;