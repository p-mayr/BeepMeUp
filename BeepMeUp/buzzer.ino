unsigned long buzzer_start_time;
boolean buzzing = false;
double buzz_freq;
int buzz_duration;
float climbing_threshold = 0.3;
float sinking_threshold = -0.5;


void Buzz(){
  if (velocity > 10){     // Avoid unnecessary high pitches
    velocity = 10.0;
  }
  
  buzz_freq = 141.0 * velocity + 386.0;
  buzz_duration = 1500 / (velocity * 0.51 + 1.62);

  if (velocity > climbing_threshold
      && !buzzing
      && buzzer_start_time+buzz_duration < time){     // Climbing start
    toneAC(buzz_freq, buzzerVolume);
    buzzing = true;
    buzzer_start_time = time;
  } else if (velocity < sinking_threshold){     // Sinking start
    toneAC(100, buzzerVolume);
    buzzing = true;
  } else if (buzzing
      && velocity < climbing_threshold){      // Sinking stop
    noToneAC();
    buzzing = false;
  } else if (buzzing
      && buzzer_start_time+buzz_duration < time){     // Climbing stop
    noToneAC();
    buzzing = false;
    buzzer_start_time = time;
  } else if (buzzing 
      && velocity > climbing_threshold){ // Adjust climbing frequenzy
    toneAC(buzz_freq, buzzerVolume);
  }
}

