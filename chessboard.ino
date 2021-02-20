#include "rdm6300.h"
#include "rfid_reader.h"
#include "multiplexer.h"
#include "cd74hc4067.h"
#include "quadrant.cpp"
#include <SoftwareSerial.h>
#include <Pin.h>
#include <arduino-timer.h>

Timer<> *timer = new Timer<TIMER_MAX_TASKS>;
SoftwareSerial* serial_a = new SoftwareSerial(3, 4);
RFIDReader* rfid = new RDM6300(serial_a, timer);

Multiplexer* mux = new CD74HC4067(
	new Pin(7),
	new Pin(8),
	new Pin(9),
	new Pin(10)
);

Quadrant *quadrant0 = new Quadrant(mux, rfid);

void setup() {
	Serial.begin(9600);

	serial_a->begin(9600);
	serial_a->listen();

	Serial.println("Initialized...");
}

void loop() {
	for (int i = 0; i < 3; i++) {
		mux->select(i);

		long tag = rfid->read();

		char serialOutput[50];
		sprintf(serialOutput, "Channel %d: %ld", i, tag);

		Serial.println(serialOutput);
	}
}
