#include <toneAC.h>
#include <Buzzer.h>

Buzzer::Buzzer(uint8_t volume,
			   uint8_t climbing_threshold,
			   int8_t sinking_threshold) :
				volume_ (volume),
				climbing_threshold_ (climbing_threshold),
				sinking_threshold_ (sinking_threshold),
				buzzing_ (false),
				start_time_ (0)
{}

void Buzzer::update(int16_t velocity, unsigned long time)
{	
	// Avoid unnecessary high pitches
	if (velocity > 10000)
	{
		velocity = 10000;
	}

	buzz_freq_ = (141.0 * velocity)/1000 + 386.0;
	//buzz_duration_ = 1500 / ((float(velocity)/10) * 0.51 + 1.62);
	buzz_duration_ = 1500000 / (velocity * 0.51 + 1620);

	Serial.print("buzz_freq_: ");
	Serial.print(buzz_freq_);

	Serial.print(", buzz_duration_: ");
	Serial.print(buzz_duration_);

	Serial.print(", velocity: ");
	Serial.print(velocity);

	Serial.print("\n");

	// Climbing start
	if (velocity > climbing_threshold_
			&& !buzzing_
			&& (start_time_ + buzz_duration_) < time)
	{
		toneAC(buzz_freq_, volume_);
		buzzing_ = true;
		start_time_ = time;
	}
	// Sinking start
	else if (velocity < sinking_threshold_)
	{
		toneAC(100, volume_);
		buzzing_ = true;
	}
	// Sinking stop
	else if (buzzing_
			&& velocity < climbing_threshold_)
	{
		noToneAC();
		buzzing_ = false;
	}
	// Climbing stop
	else if (buzzing_
			&& (start_time_ + buzz_duration_) < time)
	{
		noToneAC();
		buzzing_ = false;
		start_time_ = time;
	}
	// Adjust climbing frequenzy
	else if (buzzing_ 
			&& velocity > climbing_threshold_)
	{
		toneAC(buzz_freq_, volume_);
	}
}