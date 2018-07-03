#include <Buzzer.h>

Buzzer buzzer;
unsigned long ts;
unsigned long time;
int16_t velo;

void setup()
{
  ts = millis();
  velo = 0;
}

void loop()
{
  time = millis();
  if (ts + 1000 < time) 
  {
    if (velo > 10000)
    {
      velo = -600;
    }
    else if (velo < 0)
    {
      velo = 300;
    }
    else
    {
      velo += 300;
    }
    ts = time;
  }

  buzzer.update(velo, time);

  delay(10);
}
