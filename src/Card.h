#ifndef CARD_H
#define CARD_H
#include <string>

struct Front {
	std::string text = "";
	void change(std::string newFront);
};

struct Back {
	std::string text = "";
	void change(std::string newBack);
};

struct Card {
	std::string name = "";
	Front front;
	Back back;
	void remove();
};

#endif
