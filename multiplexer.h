#include <Arduino.h>

#ifndef MULTIPLEXER_H
#define MULTIPLEXER_H

class Multiplexer {
	public:
		virtual void select(int channel) = 0;
};

#endif
