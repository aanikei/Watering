#include "Sensor.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp32-hal-log.h>
#include <driver/adc.h>
#include <driver/rtc_io.h>

namespace {
  void initAnalogPin(gpio_num_t pin) {
    gpio_reset_pin(pin);
    rtc_gpio_init(pin);
    rtc_gpio_set_direction(pin, RTC_GPIO_MODE_INPUT_ONLY);
  }

  int32_t measureAnalog(adc2_channel_t channel, adc_atten_t atten, adc_bits_width_t width) {
    int32_t iterations = 100;

    adc2_config_channel_atten(channel, atten);

    vTaskDelay(800 / portTICK_PERIOD_MS);
    
    int64_t sum = 0;
    for (int32_t j = 0; j < iterations; j++) {
      int32_t raw;
      adc2_get_raw(channel, width, &raw);
      sum += raw;
      //log_i("Raw reading: %d", raw);
      vTaskDelay(2 / portTICK_PERIOD_MS);
    }

    int32_t result = (int32_t)(sum / iterations);
    log_i("adc result: %d", result);
    return result;
  }

  //https://www.arduino.cc/reference/en/language/functions/math/map/
  int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }
}

Sensor::Sensor(std::vector<SensorData> sensorSet) : sensors(sensorSet) {
  sensorValues.reserve(sensorSet.size());
}

void Sensor::measureValues() {
  for (const SensorData& s : sensors) {
    initAnalogPin(s.pin);
    int32_t value = measureAnalog(s.channel, atten, width);
    sensorValues.push_back(map(value, s.airValue, s.waterValue, 0, 100));
  }
}

std::vector<int32_t> Sensor::getValues() {
  return sensorValues;
}

int32_t Sensor::getCount() {
  return sensors.size();
}
