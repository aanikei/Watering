#pragma once
#include <vector>
#include <stdint.h>
#include "SensorData.h"

class Sensor {
  public:
    Sensor(std::vector<SensorData> sensorSet);
    std::vector<int32_t> getValues();
    void measureValues();
    int32_t getCount();
    static adc_atten_t atten;
    static adc_bits_width_t width;
  private:
    std::vector<SensorData> sensors;
    std::vector<int32_t> sensorValues;
};
