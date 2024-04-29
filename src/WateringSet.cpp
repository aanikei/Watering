#include "Watering.h"

using namespace std;

int32_t WateringSet::objectCount = 0;

WateringSet::WateringSet(WateringData& wateringData, AbstractPump* pump) : 
														WateringSet(wateringData, pump, nullptr) { }

WateringSet::WateringSet(WateringData& wateringData, AbstractPump* pump, AbstractSensor* soilSensor) : 
														data(wateringData), _pump(pump), sensors(soilSensor) {
  objectNumber = ++objectCount;
}

int32_t WateringSet::getNumber() const {
  return objectNumber;
}

//Threshold
int32_t& WateringSet::threshold() {
  return data.threshold;
}

const int32_t& WateringSet::threshold() const {
  return data.threshold;
}

//PumpTime
int32_t& WateringSet::pumpTime() {
  return data.pumpTime;
}

const int32_t& WateringSet::pumpTime() const {
  return data.pumpTime;
}

//Interval
int32_t& WateringSet::interval() {
  return data.interval;
}

const int32_t& WateringSet::interval() const {
  return data.interval;
}

//Mode
int32_t& WateringSet::mode() {
  return data.mode;
}

const int32_t& WateringSet::mode() const {
  return data.mode;
}

void WateringSet::initWateringData() {
  data.btnWater = false;
  data.allowWater = true;
  data.reported = false;
  data.pumpReported = true;
}

//BtnWater
bool WateringSet::tryManualWatering() {
  if (data.allowWater && data.mode != 0) {
    data.btnWater = true;
	return true;
  }
  
  return false;
}

bool WateringSet::getSensorsReported() const {
  return data.reported;
}

void WateringSet::setSensorsReported() {
  data.reported = true;
}

bool WateringSet::getPumpReported() const {
  return data.pumpReported;
}

void WateringSet::setPumpReported() {
  data.pumpReported = true;
}

int32_t WateringSet::getSensorCount() const {
  if (sensors != nullptr) {
    return sensors->getCount();
  } else {
    return 0;
  }
}

std::vector<int32_t> WateringSet::getSensorValues() const {
  if (sensors != nullptr) {
    return sensors->getValues();
  } else {
    return {};
  }
}

bool WateringSet::check(uint32_t currentTime) {
  bool pumpRun = false;
  data.reported = false;
  data.pumpReported = true;
  bool belowThreshold = true;
  if (sensors != nullptr) {
    sensors->measureValues();
    std::vector<int32_t> res = sensors->getValues();

    if (res.size() > 1) {
      for (int32_t elem : res) {
        if (elem > data.threshold) {
          belowThreshold = false;
          break;
        }
      }
    } else {
      int32_t single_element = res.at(0); // this way UART logging won't stop working (not sure why it stops)
      belowThreshold = single_element < data.threshold;
    }
  }

  int32_t hour = (currentTime / 3600) % 24;
  if (data.mode == 0) { // automatic
    if (!data.allowWater && currentTime > data.wateringTime + 86200 * data.interval) {
      data.allowWater = true;
    }

    if (data.allowWater && belowThreshold && hour > start_hour && hour < end_hour) {
      _pump->runPump(data.pumpTime);
	  pumpRun = true;
      setData(currentTime);
    }
  } else {
    if (!data.allowWater && currentTime > data.wateringTime + 86200) {
      data.allowWater = true;
    }

    if (data.allowWater && data.btnWater) {
      _pump->runPump(data.pumpTime);
	  pumpRun = true;
      setData(currentTime);
      data.btnWater = false;
    }
  }
  
  return pumpRun;
}

void WateringSet::setData(uint32_t time) {
  data.allowWater = false;
  data.wateringTime = time;
  data.pumpReported = false;
}

const char* WateringSet::prefName(std::string name) {
  prefString = name + to_string(objectNumber);
  return prefString.c_str();
}
