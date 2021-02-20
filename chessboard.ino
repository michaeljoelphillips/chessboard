#include "rdm6300.h"
#include "rfid_reader.h"
#include <SoftwareSerial.h>
#include <CD74HC4067.h>

SoftwareSerial* serial_a = new SoftwareSerial(3, 4);
RFIDReader* rfid = new RDM6300(serial_a);
CD74HC4067 mux(7, 8, 9, 10);

void setup() {
	Serial.begin(9600);

	serial_a->begin(9600);
	serial_a->listen();

	mux.channel(0);

	Serial.println("Initialized...");
}

void loop() {
	for (int i = 0; i < 4; i++) {
		long tag = rfid->read();

		char serialOutput[50];
		sprintf(serialOutput, "Channel %d: %ld", i, tag);

		Serial.println(serialOutput);

		mux.channel(i);
	}
}
