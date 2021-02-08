#include <SoftwareSerial.h>
#include <CD74HC4067.h>

/*
 * RFID Data Frame:
 *   1 byte head (value: 2)
 *   2 byte version
 *   8 byte data
 *   2 byte checksum
 *   1 byte tail (value: 3)
 */
const int BUFFER_SIZE = 14;

SoftwareSerial rfid_serial = SoftwareSerial(3,4);
CD74HC4067 mux(7, 8, 9, 10);

/*
 * The buffer storing data from the RFID serial connection.
 */
uint8_t buffer[BUFFER_SIZE];

int CHANNEL = 0;


/*
 * The current index of RFID buffer
 */
int buffer_index = 0;

void setup() {
	Serial.begin(9600);

	rfid_serial.begin(9600);
	rfid_serial.listen();

	mux.channel(0);

	Serial.println("Initializing Serial Connections");
}

void loop() {
	if (rfid_serial.available() > 0){
		int rfid_char = rfid_serial.read();
		
		if (rfid_char == -1) {
			return;
		}

		if (rfid_char == 2) {
			buffer_index = 0;
		}

		if (buffer_index >= BUFFER_SIZE) {
			Serial.println("Somehow we overflowed the buffer!");

			return;
		}

		buffer[buffer_index] = rfid_char;
		buffer_index++;

		if (rfid_char == 3) {
			Serial.println(CHANNEL);
			Serial.println(decode_tag());

			if (CHANNEL == 0) {
				mux.channel(1);

				CHANNEL = 1;
			} else {
				mux.channel(0);

				CHANNEL = 0;
			}
		}
	}
}

unsigned long decode_tag() {
	if (verify_checksum() == false) {
		Serial.println("Checksum validation failed");

		return;
	}

	char tag[9];

	for (int i = 3; i < 11; i++) {
		tag[i - 3] = char(buffer[i]);
	}

	tag[8] = '\0';

	return strtoul(tag, NULL, 16);

}

bool verify_checksum()
{
	long checksum = 0;

	char payload_checksum_string[3] = {char(buffer[11]), char(buffer[12]), '\0'};
	long payload_checksum_value = strtol(payload_checksum_string, NULL, 16);

	for (int i = 1; i < BUFFER_SIZE - 3; i = i + 2) {
		char byte_string[3] = {char(buffer[i]), char(buffer[i + 1]), '\0'};

		checksum ^= strtol(byte_string, NULL, 16);
	}

	return checksum == payload_checksum_value;
}
