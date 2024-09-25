#pragma once
#include <stdint.h>

struct WateringData {
  int32_t threshold; ///< threshold in % for all soil sensors, below which watering is allowed in an automatic mode
  int32_t pumpTime; ///< time length of watering, in seconds
  int32_t interval; ///< interval between waterings in days in an automatic mode
  int32_t mode; ///< currently 2 modes, automatic (if current time > wateringTime + 86200 * interval AND all soil sensors show moisture level below threshold) and manual (if current time > wateringTime + 86200)
  bool btnWater; ///< is true if buttonWater was pressed AND if activated == false AND mode is manual, is set to false right after watering
  bool allowWater; ///< if true, allows watering after at least 86000 seconds (~ 1 day) after pump was last time activated, so that overwatering is not possible
  bool reported; ///< set to false to report sensors values every time check() of WateringSet is called, needed because wifi connect may fail
  bool pumpReported; ///< set to false to report that pump was activated, needed because wifi connect may fail and is different from reported
  uint32_t wateringTime; ///< last time the pump was activated
};
