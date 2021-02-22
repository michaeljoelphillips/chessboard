#include "dual_multiplexer.h"
#include "multiplexer.h"

DualMultiplexer::DualMultiplexer(Multiplexer *multiplexerA, Multiplexer *multiplexerB) {
	this->multiplexerA = multiplexerA;
	this->multiplexerB = multiplexerB;
}

void DualMultiplexer::select(int channel) {
	multiplexerA->select(channel);
	multiplexerB->select(channel);
}
