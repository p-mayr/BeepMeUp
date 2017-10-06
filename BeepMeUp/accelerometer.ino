const int MPU_addr=0x68;  // I2C address of the MPU-6050
const float acc_scale_factor = 9.81/16384.0;
int16_t AcX,AcY,AcZ;
float new_acc;

unsigned int calibration_count = 0;
float Acc_sum = 0.0;

void setupAccelerometer(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void getVerticalSpeedAcc(){
  Acc += calibration_factor;
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

  // calculate acceleration vector in m/s including gravity
  new_acc = sqrt(sq((float)AcX)+sq((float)AcY)+sq((float)AcZ))*acc_scale_factor;
  // filter current acceleration
  Acc = lowPassFilter(Acc, new_acc, 0.1);
  calibrateAccelerometer();
  Acc -= calibration_factor;
}

// Tries to compensate the gravity by applying a "very slow" LP filter to the acceleration
void calibrateAccelerometer(){
  if (velocity_baro < 0.1 && velocity_baro > -0.1){
    calibration_factor = lowPassFilter(calibration_factor, Acc, 0.05);
  }
}

