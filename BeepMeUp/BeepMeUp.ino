#include <MS5611.h>

MS5611 baro;
float sea_pressure;
float pressure;
float temperature;
float altitude;

void setup() {
  // Start barometer
  baro = MS5611();
  baro.begin();
  // Start serial (UART)
  Serial.begin(9600);
  delay(2);

  sea_pressure = 1024.00;
}

void loop() {
  altitude = lowPassFilter(altitude, getAltitude(),0.1);
  Serial.println(altitude);
  delay(1000);
}

float getAltitude() {
  pressure = (float)baro.getPressure()/100;
  temperature = (float)baro.getTemperature()/100;
  return ((pow((sea_pressure / pressure), 1/5.257) - 1.0) * (temperature + 273.15)) / 0.0065;
}

float lowPassFilter(float old_value, float raw_value, float alpha){
  return old_value + alpha * (raw_value-old_value);
}
