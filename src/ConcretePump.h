#pragma once
#include "Watering.h"
#include <stdint.h>
#include <driver/rtc_io.h>

class ConcretePump : public AbstractPump {
  public:
    ConcretePump(gpio_num_t pumpPin);
    void runPump(int32_t time) override;
  private:
    gpio_num_t pin;
};
