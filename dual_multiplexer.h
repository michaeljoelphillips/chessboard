#include "multiplexer.h"

#ifndef DUAL_MULTIPLEXER_H
#define DUAL_MULTIPLEXER_H

class DualMultiplexer: public Multiplexer {
	public:
		DualMultiplexer(Multiplexer *multiplexerA, Multiplexer *multiplexerB);
		void select(int channel);

	private:
		Multiplexer *multiplexerA;
		Multiplexer *multiplexerB;
};

#endif
