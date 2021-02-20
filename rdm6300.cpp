#include "rdm6300.h"
#include <Stream.h>
#include <arduino-timer.h>

RDM6300::RDM6300(Stream *stream, Timer<> *timer) : RFIDReader(timer) {
	this->stream = stream;
}

unsigned long RDM6300::read() {
	startTimer();

	while (hasTimedOut() == false) {
		tick();

		if (stream->available() < 10) {
			continue;
		}

		int rfid_char = stream->read();

		if (rfid_char == -1) {
			continue;
		}

		if (rfid_char == 2) {
			buffer_index = 0;
		}

		if (buffer_index >= BUFFER_SIZE) {
			continue;
		}

		buffer[buffer_index] = rfid_char;
		buffer_index++;

		if (rfid_char == 3) {
			resetTimer();

			return decode_tag();
		}
	}

	resetTimer();

	return 0;
}

unsigned long RDM6300::decode_tag() {
	if (verify_checksum() == false) {
		return 0;
	}

	char tag[9];

	for (int i = 3; i < 11; i++) {
		tag[i - 3] = char(buffer[i]);
	}

	tag[8] = '\0';

	return strtoul(tag, NULL, 16);

}

bool RDM6300::verify_checksum() {
	long checksum = 0;

	char payload_checksum_string[3] = {char(buffer[11]), char(buffer[12]), '\0'};
	long payload_checksum_value = strtol(payload_checksum_string, NULL, 16);

	for (int i = 1; i < BUFFER_SIZE - 3; i = i + 2) {
		char byte_string[3] = {char(buffer[i]), char(buffer[i + 1]), '\0'};

		checksum ^= strtol(byte_string, NULL, 16);
	}

	return checksum == payload_checksum_value;
}
