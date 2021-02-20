#include "rfid_reader.h"
#include "multiplexer.h"

class Quadrant {
	private:
		Multiplexer *mux;
		RFIDReader *reader;

	public:
		long squares[16];

		Quadrant(Multiplexer *mux, RFIDReader *reader) {
			this->mux = mux;
			this->reader = reader;
		}

		void read() {
			for (int i = 0; i < 16; i++) {
				mux->select(i);

				squares[i] = reader->read();
			}
		}

		long *getSquares() {
			return squares;
		}
};
