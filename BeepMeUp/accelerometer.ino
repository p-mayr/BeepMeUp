const int MPU_addr=0x68;  // I2C address of the MPU-6050
const float acc_scale_factor = 9.81/16384.0;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

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
//  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
//  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
//  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
//  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
//  Serial.print("AcX = "); Serial.print(AcX/acc_scale_factor);
//  Serial.print(" | AcY = "); Serial.print(AcY/acc_scale_factor);
//  Serial.print(" | AcZ = "); Serial.print(AcZ/acc_scale_factor);
//  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
//  Serial.print(" | GyX = "); Serial.print(GyX);
//  Serial.print(" | GyY = "); Serial.print(GyY);
//  Serial.print(" | GyZ = "); Serial.println(GyZ);

  // calculate acceleration vector
  new_acc = sqrt(sq((float)AcX)+sq((float)AcY)+sq((float)AcZ))*acc_scale_factor;
  // filter current acceleration
  new_acc = lowPassFilter(Acc, new_acc, 0.1);
  // calculate vertical speed from the difference of the new and the old acceleration
  acc_diff = lowPassFilter(acc_diff, (new_acc-Acc)*loop_time, 0.1);
  Acc = new_acc;
  calibrateAccelerometer();
  Acc -= calibration_factor;
}

void calibrateAccelerometer(){
  if (vertical_speed < 0.1 && vertical_speed > -0.1){
//    Acc_sum += Acc;
//    calibration_count++;
    calibration_factor = lowPassFilter(calibration_factor, Acc, 0.05);
  }
}

