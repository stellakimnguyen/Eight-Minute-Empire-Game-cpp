#pragma once
#include <string>
#include <vector>

using namespace std;


// test push to BB

class SingleAction {
public:
	std::string action;
	int amount;

	SingleAction();
	SingleAction(string, int);
	void display();

	//~Action();
};


class DoubleAction {
public:
	SingleAction firstAction;
	SingleAction secondAction;

	DoubleAction();
	DoubleAction(SingleAction firstSingle, SingleAction secondSingle);
	SingleAction getFirstAction();
	void display();
};

class Cards
{

public:

	SingleAction singleAction;
	DoubleAction doubleAction;
	std::string good;
	bool isTaken;

	Cards();
	Cards(SingleAction aSingleAction, string aGood);
	Cards(DoubleAction aDoubleAction, string aGood);
	//~Cards();

	DoubleAction getDoubleAction();

	void draw(int index);
	int* initializeDeck(); // initializes 42 cards
	int* shuffleCards();
	Cards exchange(int);
	void shift(int);
	void displayFullHand();
	void displayHand(int);

	void displayCardAction();

	//TO-DO: display (print) cards from exchangeCards

};

class Hand //is hand what a player has in their hand or is it the row from which they pick?
	// row has 6 cards
{

public:


};

static Cards fullDeck[42];
static Cards hand[6];
static Cards test[5];
static Cards testTest[5];
static int firstAvailableCard = 0;
static int cardsCost[] = { 0, 1, 1, 2, 2, 3 };