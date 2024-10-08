# Watering
A simple Arduino library to facilitate watering of plants using ESP32 development boards.

## How to use
The library is created with deep sleep in mind, so the state of watering "set" is preserved in WateringData struct. The WateringSet itself takes as a mandatory argument concrete realisation of an AbstractPump class to control a pump and a non-mandatory concrete realization of an AbstractSensor class, which may be used to take measures of one or several soil moisture sensors.

> [!CAUTION]
> The library is still in development and is not fully tested. Only ADC2 is currently supported. If ADC1 is needed, `SensorData.h` can be modified, and `adc2_channel_t` replaced with `adc1_channel_t`.
