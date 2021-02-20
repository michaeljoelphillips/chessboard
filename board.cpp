#include "quadrant.cpp"

class Board {
	private:
		char position[64];

		Quadrant *quadrant0;
		Quadrant *quadrant1;
		Quadrant *quadrant2;
		Quadrant *quadrant3;

	public:
		Board(Quadrant *quadrant0) {
			this->quadrant0 = quadrant0;
		}

		void read() {
		}

		char *getPosition() {
			return this->position;
		}
};
