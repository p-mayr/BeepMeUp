#include <MS5611.h>

// Barometer variables
float temperature;
float altitude = 330;
float velocity_baro = 0;

// MPU6050 variables
float Acc = 0;
float calibration_factor = 0.0;

// Kalman
float velocity;

// Timing
unsigned long time;
unsigned long loop_time = 1000;

// Temporary variables
unsigned long ul_tmp;
float f_tmp;

void setup() {
  // set Accelerometer
  setupAccelerometer();
  
  // set barometer
  setupBaro();

  getVerticalSpeed();
  getVerticalSpeedAcc();
  calibration_factor = Acc;
  
  // set kalman
  kalman_init((double)altitude, (double)(Acc), 0.1, 0.3, millis());
  
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
  getVerticalSpeedAcc();
  kalman_update((double)altitude, (double)(Acc), millis());

  Serial.print((int)(velocity_baro*100));
  Serial.print("\t");
  Serial.print((int)((Acc)*100));
  Serial.print("\t");
  Serial.println((int)(velocity*100));

  Buzz();
}

float lowPassFilter(float old_value, float raw_value, float alpha){
  return old_value + alpha * (raw_value-old_value);
}
