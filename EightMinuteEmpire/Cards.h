#pragma once
#include <string>
#include <vector>

using namespace std;

class SingleAction {
public:
	std::string action;
	int amount;
	std::string entity;
	std::string terrain; //WATER means land + water

	SingleAction();
	SingleAction(string, int, string, string);
	//~Action();
};


class DoubleAction {
public:
	SingleAction firstAction;
	SingleAction secondAction;

	DoubleAction();
	DoubleAction(SingleAction, SingleAction);
};

class Cards
{

public:

	SingleAction singleAction;
	DoubleAction doubleAction;
	std::string* good;
	bool isTaken;

	Cards();
	Cards(SingleAction, string);
	Cards(DoubleAction, string);
	//~Cards();

	int* draw();
	int* initializeDeck(); // initializes 42 cards

};

class Hand //is hand what a player has in their hand or is it the row from which they pick?
	// row has 6 cards
{

public:

	int* cards[];
	int* exchange();

};

static Cards fullDeck [42];
static Cards cardsToExchange[6];