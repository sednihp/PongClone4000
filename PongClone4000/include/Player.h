#pragma once

class Player {
private:
	int score;

public:
	Player() : score(0) {}
	~Player() {}

	void hasScored() { ++score; }
	const int getScore() const { return score; }
	void reset() { score = 0;  }
};