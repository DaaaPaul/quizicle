#include "Card.h"
#include <iostream>
#include <string>
#include <vector>
using std::getline;
using std::string;
using std::cout;
using std::cin;
using std::vector;

vector<Card> cards;
vector<Card> correct;
vector<Card> incorrect;

int main() {
	cout << "(N \"name\") = New\n"
			"(R \"name\") = Remove\n"
		    "(P \"name\") = Print\n"
			"(CF \"name\") = Change front\n"
			"(CB \"name\") = Change back\n"
			"(QUIZ) = Begin round\n\n"
			"(q) = quit\n"
			"---------------------------------------------------------\n";

	string input = "";
	string inName = "";
	while(getline(cin, input) && input != "q") {
		if(input[1] == ' ' && input.size() > 2) {
			inName = input.substr(2, input.size());

			if(input[0] == 'N') {
				Card card;	
				card.name = inName;
				cards.push_back(card);
				cout << "New card created:" << card.name << '\n';
			} else if(input[0] == 'R') {
				bool found = false;

				for(auto i = cards.begin(); i < cards.end(); ++i) {
					if(i->name == inName) {
						cout << "Card removed:" << i->name << '\n';
						cards.erase(i);
						found = true;
					}
				}

				if(!found) {
					cout << "No card matching that name." << '\n';
				}
			} else if(input[0] == 'P') {
				bool found = false;

				for(auto i = cards.begin(); i < cards.end(); ++i) {
					if(i->name == inName) {
						cout << "Front:" << i->front.text << '\n' 
							 << "Back:" << i->back.text << '\n';
						found = true;
					}
				}

				if(!found) {
					cout << "No card matching that name." << '\n';
				}
			}
		} else if(input[2] == ' ' && input.size() > 3) {
			inName = input.substr(3, input.size());

			if(input[0] == 'C' && input[1] == 'F') {
				bool found = false;

				for(auto i = cards.begin(); i < cards.end(); ++i) {
					if(i->name == inName) {
						found = true;
						cout << "What would you like to change " << i->name << "'s front to?\n";
						string newF = "";
						getline(cin, newF);
						i->front.text = newF;
						cout << "Changed " << i->name << "'s front to:" << newF << '\n';
					}
				}			
				if(!found) {
					cout << "No card matching that name." << '\n';
				}
			}
			if(input[0] == 'C' && input[1] == 'B') {
				bool found = false;

				for(auto i = cards.begin(); i < cards.end(); ++i) {
					if(i->name == inName) {
						found = true;
						cout << "What would you like to change " << i->name << "'s back to?\n";
						string newB = "";
						getline(cin, newB);
						i->back.text = newB;
						cout << "Changed " << i->name << "'s back to:" << newB << '\n';
					}
				}

				if(!found) {
					cout << "No card matching that name." << '\n';
				}
			}
		}
	}
	return 0;
}
