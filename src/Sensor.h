#pragma once
#include <vector>
#include <stdint.h>

class Sensor {
  public:
    virtual std::vector<int32_t> getValues();
    virtual void measureValues();
    virtual int32_t getCount();
};
