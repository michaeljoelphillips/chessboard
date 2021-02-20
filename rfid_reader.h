#include <Arduino.h>
#include <arduino-timer.h>

#ifndef RFID_READER_H
#define RFID_READER_H

class RFIDReader {
	private:
		Timer<>::Task task;
		Timer<> *timer;
		bool timedOut = false;

		void setTimedOut() {
			timedOut = true;
		}

	protected:
		RFIDReader(Timer<> *timer) {
			this->timer = timer;
		}

		void startTimer() {
			timedOut = false;

			task = timer->in(
					600,
					[](RFIDReader* reader) -> bool {
						reader->resetTimer();
						reader->setTimedOut();

						return true;
					},
					this
			);
		}

		void resetTimer() {
			timer->cancel(task);
		}

		bool hasTimedOut() {
			return timedOut;
		}

		void tick() {
			timer->tick();
		}

	public:
		virtual unsigned long read() = 0;
};

#endif
