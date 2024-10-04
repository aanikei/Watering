#pragma once
#include "Watering.h"
#include <vector>
#include <stdint.h>

class ConcreteSensor : public AbstractSensor {
  public:
    ConcreteSensor(std::vector<SensorData> sensorSet);
    std::vector<int32_t> getValues() override;
    void measureValues() override;
    int32_t getCount() override;
    static adc_atten_t atten;
    static adc_bits_width_t width;
  private:
    std::vector<SensorData> sensors;
    std::vector<int32_t> sensorValues;
};
