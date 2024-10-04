#include "ConcretePump.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp32-hal-log.h>
#include <esp_task_wdt.h>

ConcretePump::ConcretePump(gpio_num_t pumpPin) : pin(pumpPin) { }

void ConcretePump::runPump(int32_t time) {
  log_i("Start pump, pin %d", pin);
  esp_task_wdt_config_t config = {
    .timeout_ms = (time + 1) * 1000,
    .trigger_panic = true,
  };
  esp_task_wdt_reconfigure(&config);

  gpio_set_level(pin, 1);

  vTaskDelay(time * 1000 / portTICK_PERIOD_MS);
  log_i("Stop pump, pin %d", pin);

  gpio_set_level(pin, 0);
}
