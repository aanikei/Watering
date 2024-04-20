#pragma once
#include <stdint.h>

class Pump {
  public:
    virtual void runPump(int32_t time);
};
