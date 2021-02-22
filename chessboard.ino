#include "rdm6300.h"
#include "rfid_reader.h"
#include "multiplexer.h"
#include "cd74hc4067.h"
#include "quadrant.cpp"
#include <SoftwareSerial.h>
#include <Pin.h>
#include <arduino-timer.h>
#include "dual_multiplexer.h"

Timer<> *timer = new Timer<TIMER_MAX_TASKS>;
SoftwareSerial *serial = new SoftwareSerial(2, 3);
RFIDReader *rfid = new RDM6300(serial, timer);

Multiplexer *mux = new DualMultiplexer(
	new CD74HC4067(
		new Pin(4),
		new Pin(5),
		new Pin(6),
		new Pin(7)
	),
	new CD74HC4067(
		new Pin(8),
		new Pin(9),
		new Pin(10),
		new Pin(11)
	)
);

Quadrant *quadrant0 = new Quadrant(mux, rfid);

const long pieceMap[4][2] = {
	{1710404, 1},
	{2176689, 2},
	{3705097, 3},
	{3485743, 4}
};

void setup() {
	Serial.begin(9600);

	serial->begin(9600);
	serial->listen();

	Serial.println("Initialized...");
}

void loop() {
	quadrant0->read();

	transmitPosition(quadrant0->getSquares());
}

void transmitPosition(long *squares) {
	for (int i = 10; i < 16; i++) {
		long tag = *(squares + i);
		long pieceValue = getPieceValueForTag(tag);

		char serialOutput[50];
		sprintf(serialOutput, "%d: %ld %ld", i, pieceValue, tag);

		Serial.println(serialOutput);
	}

	delay(750);
}

long getPieceValueForTag(long tag) {
	for (int j = 0; j < 4; j++) {
		if (pieceMap[j][0] == tag) {
			return pieceMap[j][1];
		}
	}

	return 0;
}
