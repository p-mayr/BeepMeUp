#include <MS5611.h>
#include <MPU6050.h>
#include <EEPROM.h>

//calibration settings
//standard scale factor
float acc_scale_factor_x = 16384.0;
float acc_scale_factor_y = 16384.0;
float acc_scale_factor_z = 16384.0;
//calibration flag
bool calibration = 1;
//address for eeprom
int eeaddress = 0;
//maximum calibration deviation
int deviation = 4;
//calculated final offsets
float final_x = 0;
float final_y = 0;
float final_z = 0;
//one G value for each axis -> scaling
float one_g_x = 0;
float one_g_y = 0;
float one_g_z = 0;

// Barometer variables
float temperature;
float altitude = 330;
float velocity_baro = 0;

// MPU6050 variables
float Acc = 0;
float Acc_old = 0;
float Acc_diff = 0;
float Acc_diff_new = 0;
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
  EEPROM.get(eeaddress, calibration);
  //uncomment to force calibration
  //calibration = 1;

  if(calibration == 0){
    eeaddress += sizeof(bool);
    EEPROM.get(eeaddress, acc_scale_factor_x);
    eeaddress += sizeof(float);
    EEPROM.get(eeaddress, acc_scale_factor_y);
    eeaddress += sizeof(float);
    EEPROM.get(eeaddress, acc_scale_factor_z);
    eeaddress += sizeof(float);
    EEPROM.get(eeaddress, final_x);
    eeaddress += sizeof(float);
    EEPROM.get(eeaddress, final_y);
    eeaddress += sizeof(float);
    EEPROM.get(eeaddress, final_z);
  }
  //set Accelerometer
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
  delay(20);
}


void loop() {
  if(calibration){
     calibrationAcc();
     acc_scale_factor_z = (one_g_z-final_z);
     acc_scale_factor_x = (one_g_x-final_x);
     acc_scale_factor_y = (one_g_y-final_y);
     Serial.print("starting write process");
     delay(5000);
    eeaddress += sizeof(bool);
    EEPROM.put(eeaddress, acc_scale_factor_x);
    eeaddress += sizeof(float);
    EEPROM.put(eeaddress, acc_scale_factor_y);
    eeaddress += sizeof(float);
    EEPROM.put(eeaddress, acc_scale_factor_z);
    eeaddress += sizeof(float);
    EEPROM.put(eeaddress, final_x);
    eeaddress += sizeof(float);
    EEPROM.put(eeaddress, final_y);
    eeaddress += sizeof(float);
    EEPROM.put(eeaddress, final_z);
  }

  // Calculate loop time
  ul_tmp = millis();
  loop_time = ul_tmp - time;
  time = ul_tmp;
  //Serial.println(1000/loop_time);
  // Calculate vertical speed and altitude
  getVerticalSpeed();
  getVerticalSpeedAcc();
  kalman_update((double)altitude, (double)(0.8*Acc + 0.2*Acc_diff), millis());
  Serial.println(velocity, 1);


  Buzz();
}

float lowPassFilter(float old_value, float raw_value, float alpha) {
  return old_value + alpha * (raw_value - old_value);
}
