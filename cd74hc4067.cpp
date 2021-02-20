#include <Pin.h>
#include "multiplexer.h"
#include "cd74hc4067.h"

CD74HC4067::CD74HC4067(Pin *s0, Pin *s1, Pin *s2, Pin *s3) {
	this->s0 = s0;
	this->s1 = s1;
	this->s2 = s2;
	this->s3 = s3;

	this->s0->setOutputLow();
	this->s1->setOutputLow();
	this->s2->setOutputLow();
	this->s3->setOutputLow();
}

void CD74HC4067::select(int channel) {
	s0->setState(CHANNEL_TRUTH_TABLE[channel][0]);
	s1->setState(CHANNEL_TRUTH_TABLE[channel][1]);
	s2->setState(CHANNEL_TRUTH_TABLE[channel][2]);
	s3->setState(CHANNEL_TRUTH_TABLE[channel][3]);
}
