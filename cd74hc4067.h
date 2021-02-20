#include <Pin.h>
#include "multiplexer.h"

class CD74HC4067: public Multiplexer {
	public:
		CD74HC4067(Pin *s0, Pin *s1, Pin *s2, Pin *s3);
		void select(int channel);

	private:
		const int CHANNEL_TRUTH_TABLE[16][4] = {
			{0,  0,  0,  0},
			{1,  0,  0,  0},
			{0,  1,  0,  0},
			{1,  1,  0,  0},
			{0,  0,  1,  0},
			{1,  0,  1,  0},
			{0,  1,  1,  0},
			{1,  1,  1,  0},
			{0,  0,  0,  1},
			{1,  0,  0,  1},
			{0,  1,  0,  1},
			{1,  1,  0,  1},
			{0,  0,  1,  1},
			{1,  0,  1,  1},
			{0,  1,  1,  1},
			{1,  1,  1,  1},
		};

		Pin *s0;
		Pin *s1;
		Pin *s2;
		Pin *s3;
};

