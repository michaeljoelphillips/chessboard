#include <Arduino.h>

#ifndef RFID_READER_H
#define RFID_READER_H

class RFIDReader {
	public:
		virtual unsigned long read() = 0;
};

#endif
