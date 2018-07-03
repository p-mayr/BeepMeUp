#ifndef BUZZER_H
#define BUZZER_H

#define VOLUME 10
#define CLIMBING_THRESHOLD 0.3
#define SINKING_THRESHOLD (-0.5)

class Buzzer {

	private:
		// Settings
		uint8_t volume_;
		uint8_t climbing_threshold_;
		int8_t sinking_threshold_;

		// Frequenzy 428-1796 Hz
		uint16_t buzz_freq_;
		// Duration 223-846 ms
		uint16_t buzz_duration_;
		bool buzzing_;
		unsigned long start_time_;

	public:
		Buzzer(uint8_t volume = VOLUME,
			   uint8_t climbing_threshold = CLIMBING_THRESHOLD,
			   int8_t sinking_threshold = SINKING_THRESHOLD);
		void update(int16_t velocity, unsigned long time);

};

#endif