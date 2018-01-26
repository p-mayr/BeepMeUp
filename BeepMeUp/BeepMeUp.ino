#include <MS5611.h>
#include <MPU6050.h>
#include <EEPROM.h>
#include <avr/power.h>
#include <toneAC.h>

//calibration settings
//standard scale factor
float acc_scale_factor_x = 16384.0;
float acc_scale_factor_y = 16384.0;
float acc_scale_factor_z = 16384.0;
//calibration flag
bool calibration = 0;
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

//Buzzer
const int buzzerVolume = 10;

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
//------------------------------------------------------------
//set prescaler to 2 ro F_cpu is 8MHz
//for this setting you have to compile with 8MHz!!!
//------------------------------------------------------------
  clock_prescale_set(clock_div_2);
  delay(1);
//------------------------------------------------------------
  EEPROM.get(0, calibration);
  //uncomment to force calibration
  //calibration = 1;
  delay(2);
  //set Accelerometer
  setupAccelerometer();

  // set barometer
  setupBaro();
  delay(2);
  getVerticalSpeed();
  getVerticalSpeedAcc();
  calibration_factor = Acc;

  // set kalman
  kalman_init((double)altitude, (double)(Acc), 0.1, 0.3, millis());
  delay(2);
  // Set initial times
  time = millis();
  loop_time = time;

  // Start serial (UART)
  //Serial.begin(9600);
  delay(2);
}


void loop() {


  if(!calibration){
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
    eeaddress = 0;
  }else{
     calibrationAcc();
     acc_scale_factor_z = (one_g_z-final_z);
     acc_scale_factor_x = (one_g_x-final_x);
     acc_scale_factor_y = (one_g_y-final_y);
    //Serial.print("starting write process");
    toneAC(200, 8);
    delay(1000);
    toneAC(300, 8);
    delay(1000);
    toneAC(400, 8);
    delay(1000);
    toneAC(500, 8);
    delay(1000);
    noToneAC();
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
    eeaddress = 0;
  }

  // Calculate loop time
  ul_tmp = millis();
  loop_time = ul_tmp - time;
  time = ul_tmp;
  //Serial.println(1000/loop_time);
  // Calculate vertical speed and altitude
  getVerticalSpeed();
  getVerticalSpeedAcc();
  kalman_update((double)altitude, (double)(0.9*Acc + 0.1*Acc_diff), millis());
  if(abs(velocity-velocity_baro) > 1){
    velocity = velocity_baro;
  }
  //Serial.print(velocity_baro, 1);
  //Serial.print("\t");
  //Serial.println(velocity, 1);
  Buzz();
}

float lowPassFilter(float old_value, float raw_value, float alpha) {
  return old_value + alpha * (raw_value - old_value);
}
