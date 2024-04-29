#pragma once
#include <stdint.h>

class AbstractPump {
  public:
    virtual void runPump(int32_t time);
};
