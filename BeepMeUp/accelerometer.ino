int16_t AcX,AcY,AcZ;
int16_t AcX_cor,AcY_cor,AcZ_cor;
float new_acc;
MPU6050 mpu;
unsigned int calibration_count = 0;
float Acc_sum = 0.0;

void setupAccelerometer(){
  Wire.begin();
  mpu.initialize();
//Set digital low-pass filter configuration.
  mpu.setDLPFMode(0);
//Set the high-pass filter configuration.
  mpu.setDHPFMode(0);
//set speed to highest possible setting
  mpu.setMasterClockSpeed(9);
  mpu.setFullScaleAccelRange(0);
}

void getVerticalSpeedAcc(){
  mpu.getAcceleration(&AcX,&AcY,&AcZ);

AcX_cor = (float)AcX-final_x;
AcY_cor = (float)AcY-final_y;
AcZ_cor = (float)AcZ-final_z;

  new_acc = (sqrt(sq((float)AcX_cor/acc_scale_factor_x)+sq((float)AcY_cor/acc_scale_factor_y)+sq((float)AcZ_cor/acc_scale_factor_z))-1)*9.81;

  //calculate diffence for further 
  Acc_diff_new = (Acc_old-new_acc)*-1;  
  // filter current acceleration
  Acc_diff= lowPassFilter(Acc_diff, Acc_diff_new, 0.08);
  Acc_old = Acc;  
  // filter current acceleration
  Acc = lowPassFilter(Acc, new_acc, 0.08);
  

}



