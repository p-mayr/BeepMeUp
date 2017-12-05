void calibrationAcc(){
  int axis_count = 1;
  float offset_x = 0;
  float offset_y = 0;
  float offset_z = 0;
  float mean_calx = 0;
  float mean_caly = 0;
  float mean_calz = 0;

//each axis one case for positive and one case in negative direction
  switch(axis_count){
    case 1:

    //Serial.println("Make ready for Z+ axis");
      toneAC(1000,6);
      delay(2000);
      noToneAC();
      //Serial.println("Starting Measure don't move!");
      delay(1000);
      toneAC(500,6);
      delay(1000);
      noToneAC();
      toneAC(1000,6);
      delay(1000);
      noToneAC();
    while(axis_count == 1){
        for(int i = 0; i < 1100; i++){
        delay(2);
        mpu.getAcceleration(&AcX,&AcY,&AcZ);
        if(i > 100){
          mean_calx += AcX;
          mean_caly += AcY;
          mean_calz += AcZ;
        }
        }
        mean_calx = mean_calx/1000;
        mean_caly = mean_caly/1000;
        mean_calz = mean_calz/1000;
        if(abs(mean_calx - offset_x) <= (float)deviation &&
           abs(mean_caly - offset_y) <= (float)deviation &&
           abs(mean_calz - offset_z) <= (float)deviation){
            offset_x = mean_calx;
            offset_y = mean_caly;
            final_z = mean_calz;
            axis_count ++;
           }else{
            toneAC(500,6);
            delay(100);
            noToneAC();
            //Serial.println("calculating...");
            offset_x = mean_calx;
            offset_y = mean_caly;
            offset_z = mean_calz;
           }
    }
     case 2:

      //Serial.println("Make ready for Z- axis.");
      toneAC(1000,6);
      delay(2000);
      noToneAC();
      //Serial.println("Starting Measure don't move!");
      delay(1000);
      toneAC(500,6);
      delay(1000);
      noToneAC();
      toneAC(1000,6);
      delay(1000);
      noToneAC();
        while(axis_count == 2){
                for(int i = 0; i < 1100; i++){
        delay(2);
        mpu.getAcceleration(&AcX,&AcY,&AcZ);
        if(i > 100){
          mean_calx += AcX;
          mean_caly += AcY;
          mean_calz += AcZ;
        }
        }
        mean_calx = mean_calx/1000;
        mean_caly = mean_caly/1000;
        mean_calz = mean_calz/1000;
        if(abs(mean_calx - offset_x) <= (float)deviation &&
           abs(mean_caly - offset_y) <= (float)deviation &&
           abs(mean_calz - offset_z) <= (float)deviation){
            offset_x = mean_calx;
            offset_y = mean_caly;
            final_z += mean_calz;
            final_z /= 2;
            one_g_z = mean_calz;
            axis_count ++;
           }else{
            toneAC(500,6);
            delay(100);
            noToneAC();
            //Serial.println("calculating...");
            offset_x = mean_calx;
            offset_y = mean_caly;
            offset_z = mean_calz;
           }
     }

     case 3:

    //Serial.println("Make ready for X+ axis");
      toneAC(1000,6);
      delay(2000);
      noToneAC();
      //Serial.println("Starting Measure don't move!");
      delay(1000);
      toneAC(500,6);
      delay(1000);
      noToneAC();
      toneAC(1000,6);
      delay(1000);
      noToneAC();
    while(axis_count == 3){
        for(int i = 0; i < 1100; i++){
        delay(2);
        mpu.getAcceleration(&AcX,&AcY,&AcZ);
        if(i > 100){
          mean_calx += AcX;
          mean_caly += AcY;
          mean_calz += AcZ;
        }
        }
        mean_calx = mean_calx/1000;
        mean_caly = mean_caly/1000;
        mean_calz = mean_calz/1000;
        if(abs(mean_calx - offset_x) <= (float)deviation &&
           abs(mean_caly - offset_y) <= (float)deviation &&
           abs(mean_calz - offset_z) <= (float)deviation){
            offset_z = mean_calz;
            offset_y = mean_caly;
            final_x = mean_calx;
            axis_count ++;
           }else{
            toneAC(500,6);
            delay(100);
            noToneAC();
            //Serial.println("calculating...");
            offset_x = mean_calx;
            offset_y = mean_caly;
            offset_z = mean_calz;
           }
    }
     case 4:

      //Serial.println("Make ready for X- axis.");
      toneAC(1000,6);
      delay(2000);
      noToneAC();
      //Serial.println("Starting Measure don't move!");
      delay(1000);
      toneAC(500,6);
      delay(1000);
      noToneAC();
      toneAC(1000,6);
      delay(1000);
      noToneAC();
        while(axis_count == 4){
                for(int i = 0; i < 1100; i++){
        delay(2);
        mpu.getAcceleration(&AcX,&AcY,&AcZ);
        if(i > 100){
          mean_calx += AcX;
          mean_caly += AcY;
          mean_calz += AcZ;
        }
        }
        mean_calx = mean_calx/1000;
        mean_caly = mean_caly/1000;
        mean_calz = mean_calz/1000;
        if(abs(mean_calx - offset_x) <= (float)deviation &&
           abs(mean_caly - offset_y) <= (float)deviation &&
           abs(mean_calz - offset_z) <= (float)deviation){
            offset_z = mean_calz;
            offset_y = mean_caly;
            final_x += mean_calx;
            final_x /= 2;
            one_g_x = mean_calx;
            axis_count ++;
           }else{
            toneAC(500,6);
            delay(100);
            noToneAC();
            //Serial.println("calculating...");
            offset_x = mean_calx;
            offset_y = mean_caly;
            offset_z = mean_calz;
           }
     }

     case 5:

    //Serial.println("Make ready for Y+ axis");
      toneAC(1000,6);
      delay(2000);
      noToneAC();
      //Serial.println("Starting Measure don't move!");
      delay(1000);
      toneAC(500,6);
      delay(1000);
      noToneAC();
      toneAC(1000,6);
      delay(1000);
      noToneAC();
    while(axis_count == 5){
        for(int i = 0; i < 1100; i++){
        delay(2);
        mpu.getAcceleration(&AcX,&AcY,&AcZ);
        if(i > 100){
          mean_calx += AcX;
          mean_caly += AcY;
          mean_calz += AcZ;
        }
        }
        mean_calx = mean_calx/1000;
        mean_caly = mean_caly/1000;
        mean_calz = mean_calz/1000;
        if(abs(mean_calx - offset_x) <= (float)deviation &&
           abs(mean_caly - offset_y) <= (float)deviation &&
           abs(mean_calz - offset_z) <= (float)deviation){
            offset_x = mean_calx;
            offset_z = mean_calz;
            final_y = mean_caly;
            axis_count ++;
           }else{
            toneAC(500,6);
            delay(100);
            noToneAC();
            //Serial.println("calculating...");
            offset_x = mean_calx;
            offset_y = mean_caly;
            offset_z = mean_calz;
           }
    }
     case 6:

      //Serial.println("Make ready for Y- axis.");
      toneAC(1000,6);
      delay(2000);
      noToneAC();
      //Serial.println("Starting Measure don't move!");
      delay(1000);
      toneAC(500,6);
      delay(1000);
      noToneAC();
      toneAC(1000,6);
      delay(1000);
      noToneAC();
        while(axis_count == 6){
                for(int i = 0; i < 1100; i++){
        delay(2);
        mpu.getAcceleration(&AcX,&AcY,&AcZ);
        if(i > 100){
          mean_calx += AcX;
          mean_caly += AcY;
          mean_calz += AcZ;
        }
        }
        mean_calx = mean_calx/1000;
        mean_caly = mean_caly/1000;
        mean_calz = mean_calz/1000;
        if(abs(mean_calx - offset_x) <= (float)deviation &&
           abs(mean_caly - offset_y) <= (float)deviation &&
           abs(mean_calz - offset_z) <= (float)deviation){
            offset_x = mean_calx;
            offset_z = mean_calz;
            final_y += mean_caly;
            final_y /= 2;
            one_g_y = mean_caly;
            axis_count ++;
            EEPROM.put(0, 0);
            calibration = 0;
           }else{
            toneAC(500,6);
            delay(100);
            noToneAC();
            //Serial.println("calculating...");
            offset_x = mean_calx;
            offset_z = mean_calz;
            offset_y = mean_caly;
           }
     }
  }
    
}
