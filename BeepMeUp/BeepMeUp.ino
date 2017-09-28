#include <MS5611.h>

// Barometer variables
MS5611 baro;
float sea_pressure;
float pressure;
float temperature;
float altitude;
float vertical_speed;

// Timing
unsigned long time;
unsigned long loop_time;

// Temporary variables
unsigned long ul_tmp;
float f_tmp;

void setup() {
  // Start barometer
  baro = MS5611();
  baro.begin();
  sea_pressure = 1024.00;

  // Set initial times
  time = millis();
  loop_time = time;
  
  // Start serial (UART)
  Serial.begin(9600);
  delay(2);
}

void loop() {
  // Calculate loop time
  ul_tmp = millis();
  loop_time = ul_tmp - time;
  time = ul_tmp;

  // Calculate vertical speed and altitude
  getVerticalSpeed();

  // Print results
  //Serial.println(altitude);
  Serial.println(vertical_speed);
}

float lowPassFilter(float old_value, float raw_value, float alpha){
  return old_value + alpha * (raw_value-old_value);
}
