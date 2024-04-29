#pragma once
#include <stdint.h>
#include <string> 
#include "WateringData.h"
#include "AbstractSensor.h"
#include "AbstractPump.h"

class WateringSet {
  public:
    WateringSet(WateringData& wateringData, AbstractPump* pump); ///< constructor without Sensor argument as watering can be done without moisture sensors, using interval or manually
    WateringSet(WateringData& wateringData, AbstractPump* pump, AbstractSensor* soilSensor); ///< standard constructor
    int32_t getNumber() const; ///< get serial number of the set
          int32_t& threshold(); ///< set threshold in WateringData
    const int32_t& threshold() const; ///< get threshold from WateringData
          int32_t& pumpTime(); ///< set pumpTime in WateringData
    const int32_t& pumpTime() const; ///< get pumpTime from WateringData
          int32_t& interval(); ///< set interval in WateringData
    const int32_t& interval() const; ///< get interval from WateringData
          int32_t& mode(); ///< set mode in WateringData
    const int32_t& mode() const; ///< get mode from WateringData
	void initWateringData(); ///< set WateringData booleans to correct values at start
    bool tryManualWatering(); ///< set btnWater to true if manual mode is selected and conditions are met, return true if watering will happen
    void setSensorsReported(); ///< set reported to true after sensor data was sent to mqtt
    bool getSensorsReported() const; ///< get reported state that is updated to false after Watering::check was run and new sensor values received
    void setPumpReported(); ///< set pumpReported to true after pump data was sent to mqtt
    bool getPumpReported() const; ///< get pumpReported state that is updated to false after pump was run
    int32_t getSensorCount() const; ///< get number of sensors used in this Watering set
    std::vector<int32_t> getSensorValues() const; ///< get sensors' values in %
    bool check(uint32_t currentTime); ///< main method to perform check of conditions and call runPump method of associated Pump, reported is set to false to send data to mqtt. Returns true if pump was run
    static constexpr const char* thresholdName = "threshold";
    static constexpr const char* pumpTimeName = "pumpTime";
    static constexpr const char* intervalName = "interval";
    static constexpr const char* modeName = "mode";
  private:
    static int32_t start_hour;
    static int32_t end_hour;
    std::string prefString;
    const char* prefName(std::string name);
    static int32_t objectCount;
    int32_t objectNumber;
    WateringData& data;
    void setData(uint32_t time);
    AbstractSensor* sensors;
    AbstractPump* _pump;
};
