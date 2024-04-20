#pragma once
#include <stdint.h>
#include <driver/adc.h>
#include <driver/rtc_io.h>

struct SensorData {
  gpio_num_t pin;
  adc2_channel_t channel;
  int32_t airValue;
  int32_t waterValue;
};
