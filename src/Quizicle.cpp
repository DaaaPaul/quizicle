#define MINIAUDIO_IMPLEMENTATION
#include "../lib/miniaudio.h"
#include "card.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>

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

	ma_engine engine;
	ma_engine_init(nullptr, &engine);

	while(getline(cin, input) && input != "q") {
		if(input[1] == ' ' && input.size() > 2) {
			inName = input.substr(2, input.size());

			if(input[0] == 'N') {
				Card card;	
				card.name = inName;
				cards.push_back(card);
				cout << "New card created:" << card.name << '\n';
				ma_engine_play_sound(&engine, "/Users/paulpeng/quizicle/sfx/New Card and Print Card.mp3", nullptr);
			} else if(input[0] == 'R') {
				bool found = false;

				for(auto i = cards.begin(); i < cards.end(); ++i) {
					if(i->name == inName) {
						cout << "Card removed:" << i->name << '\n';
						cards.erase(i);
						--i;
						ma_engine_play_sound(&engine, "/Users/paulpeng/quizicle/sfx/Remove Card.mp3", nullptr);
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
						ma_engine_play_sound(&engine, "/Users/paulpeng/quizicle/sfx/New Card and Print Card.mp3", nullptr);
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
						ma_engine_play_sound(&engine, "/Users/paulpeng/quizicle/sfx/Change Front and Change Back.mp3", nullptr);
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
			} else if(input[0] == 'C' && input[1] == 'B') {
				bool found = false;

				for(auto i = cards.begin(); i < cards.end(); ++i) {
					if(i->name == inName) {
						ma_engine_play_sound(&engine, "/Users/paulpeng/quizicle/sfx/Change Front and Change Back.mp3", nullptr);
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
		} else if(input == "QUIZ") {
			if(cards.size() > 2) {
				ma_engine_play_sound(&engine, "/Users/paulpeng/quizicle/sfx/Quiz.mp3", nullptr);
				cout << "Beginning round...\n";
				std::this_thread::sleep_for(std::chrono::seconds(1));
				cout <<	"(P) = Previous (F) = Flip (N) = Next (q) = quit round\n"
						"--------------------------------------------------------\n\n";
				std::this_thread::sleep_for(std::chrono::seconds(1));

				auto rng = std::default_random_engine{};		
				std::shuffle(cards.begin(), cards.end(), rng);

				auto i = cards.begin();
				string quizInput = "";

				cout <<  "--------------------------------------------------------\n" 
					 << i->front.text << '\n'
					 << "--------------------------------------------------------\n";

				while(getline(cin, quizInput)) {
					if(quizInput == "q") {
						cout << "Quitting round...\n";
						ma_engine_play_sound(&engine, "/Users/paulpeng/quizicle/sfx/Quit.mp3", nullptr);
						std::this_thread::sleep_for(std::chrono::seconds(1));
					 	cout << "--------------------------------------------------------\n";
						break;
					}
					ptrdiff_t ipos = i - cards.begin();

					if(quizInput == "P") {
						if(ipos > 0) {
							--i;
							cout <<  "--------------------------------------------------------\n" 
								 << i->front.text << '\n'
								 << "--------------------------------------------------------\n";
							ma_engine_play_sound(&engine, "/Users/paulpeng/quizicle/sfx/Next and Previous.mp3", nullptr);
							continue;
						} else {
							cout << "Already at beginning.\n";
						}
					} else if(quizInput == "F") {
						cout <<  "--------------------------------------------------------\n" 
							 << i->back.text << '\n'
							 << "--------------------------------------------------------\n";
						ma_engine_play_sound(&engine, "/Users/paulpeng/quizicle/sfx/Flip.mp3", nullptr);
					} else if(quizInput == "N") {
						if(ipos < cards.size() - 1) {
							++i;
							cout <<  "--------------------------------------------------------\n" 
								 << i->front.text << '\n'
								 << "--------------------------------------------------------\n";
							ma_engine_play_sound(&engine, "/Users/paulpeng/quizicle/sfx/Next and Previous.mp3", nullptr);
							continue;
						} else {
							cout <<	"(R) = Redo (SR) = Smart Redo\n"
									"--------------------------------------------------------\n";
							ma_engine_play_sound(&engine, "/Users/paulpeng/quizicle/sfx/Finish.mp3", nullptr);
						}
					} else {
						cout << "Invalid command.\n";
					}
				}
			} else {
				cout << "Not enough cards to begin quiz.\n";
			}
		}
	}
	return 0;
}
