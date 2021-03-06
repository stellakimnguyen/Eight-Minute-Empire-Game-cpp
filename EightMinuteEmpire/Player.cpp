#include "Player.h"
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

/*
int main() {


	int numberOfPlayers = 0;
	std::list <Player>* players = new std::list <Player>();

	cout << "How many players are joining the game? ";
	cin >> numberOfPlayers;

	for (int i = 0; i < numberOfPlayers; i++)
	{
		Player* temp = new Player(&numberOfPlayers, (i + 1));

		(*players).push_back(*temp);

	}

	cout << "Demonstrating that each player has regions: \n";

	for (int i = 0; i < 10; i++)
	{

		Region* region = new Region(i, (i + 1) % 2);

		// Create iterator pointing to first element
		std::list<Player>::iterator it = (*players).begin();
		// Advance the iterator by 2 positions,
		std::advance(it, i % numberOfPlayers);

		it->addRegion(region);
	}

	for (int i = 0; i < numberOfPlayers; i++)
	{
		// Create iterator pointing to first element
		std::list<Player>::iterator itP = (*players).begin();
		// Advance the iterator by 2 positions,
		std::advance(itP, i);

		cout << "Player" << (i + 1) << ":\n";

		for (std::list<Region>::iterator it = (*(itP->regionOwned)).begin(); it != (*(itP->regionOwned)).end(); ++it) {
			cout << *(it->val) << "\n";
		}

	}
	Region* region1 = new Region(10, 3);
	Region* region2 = new Region(11, 3);

	cout << "\n\n";

	(*(players->begin())).payCoin(new int(2));
	(*(players->begin())).placeNewArmies(region1, new int(2));
	(*(players->begin())).moveArmies(region1, region2, new int(2));
	(*(players->begin())).moveOverLand(region1, region2, new int(2));
	(*(players->begin())).buildCity(region1);
	(*(players->begin())).destroyArmy(region1, new int(1));

	return 0;
}
	*/


Player::Player(int* numberOfPlayer, int pn) {
	playerNumber = new int(pn);
	int tempAge = 0;
	cout << "Player " << *playerNumber << ", your age: ";
	cin >> tempAge;
	playerAge = new int(tempAge);
	biddingFacility = new BiddingFacility();
	cubes = new int(14);
	discs = new int(3);
	playerScore = new int(0);
	nbControllingRegions = new int(0);
	totalNbArmies = new int(0);

	if (*numberOfPlayer == 5) {
		tokenCoins = new int(8);
	}
	else if (*numberOfPlayer == 4) {
		tokenCoins = new int(9);
	}
	else if (*numberOfPlayer == 3) {
		tokenCoins = new int(11);
	}
	else if (*numberOfPlayer == 2) {
		tokenCoins = new int(14);
	}

	regionOwned = new std::list <Region>();
	cards = new std::list <Cards>();
	moveDesc = new std::list <MoveDesc>();

}

Player::Player(int pn, int tc, int age, Colors c) {

	playerNumber = new int(pn);
	playerAge = new int(age);
	biddingFacility = new BiddingFacility();
	cubes = new int(14);
	discs = new int(3);
	playerScore = new int(0);
	nbControllingRegions = new int(0);
	totalNbArmies = new int(0);

	tokenCoins = new int(tc);
	//chosenColor = c;
	regionOwned = new std::list <Region>();
	cards = new std::list <Cards>();
	moveDesc = new std::list <MoveDesc>();
	chosenColor = c;
	//playerStrategy = new ModerateBot(pn);
	playerStrategy = new InteractiveHuman(pn);

}
Player::Player(int pn, int tc, int age, Colors c, PlayerStrategies* pStrategy) {

	playerNumber = new int(pn);
	playerAge = new int(age);
	biddingFacility = new BiddingFacility();
	cubes = new int(14);
	discs = new int(3);
	playerScore = new int(0);
	nbControllingRegions = new int(0);
	totalNbArmies = new int(0);

	tokenCoins = new int(tc);
	//chosenColor = c;
	regionOwned = new std::list <Region>();
	cards = new std::list <Cards>();
	moveDesc = new std::list <MoveDesc>();
	chosenColor = c;
	playerStrategy = pStrategy;

}

Player::~Player()
{
	/*delete playerNumber;
	delete playerAge;
	delete biddingFacility;
	delete cubes;
	delete discs;
	delete playerScore;
	delete nbControllingRegions;
	delete totalNbArmies;
	delete tokenCoins;
	delete regionOwned;
	delete cards;
	delete moveDesc;
	delete playerStrategy;

	playerNumber = nullptr;
	playerAge = nullptr;
	biddingFacility = nullptr;
	cubes = nullptr;
	discs = nullptr;
	playerScore = nullptr;
	nbControllingRegions = nullptr;
	totalNbArmies = nullptr;
	tokenCoins = nullptr;
	regionOwned = nullptr;
	cards = nullptr;
	moveDesc = nullptr;
	playerStrategy = nullptr;*/
}

void Player::addRegion(Region* regionToAdd)
{
	//for the player, adds the region when they have more than 1 army

	regionOwned->push_back(*regionToAdd);

}

void Player::payCoin(int* value)
{
	//cout << "This removes the paid coins from the player's coins." << endl;

	cout << "Number of coins before paying: " << *tokenCoins << endl;

	*tokenCoins = *tokenCoins - *value;

	cout << "Player::payCoin ********************* : " << this << "  " << *(this->tokenCoins) << endl;
	cout << "Number of coins left: " << *tokenCoins << endl;

}
//TODO break out of the if in the for loop
void Player::placeNewArmies(Region* region, int* value)
{
	cout << "This allows a player to place new armies in a certain region." << endl;
	//region->display();

	//should we verify that the total number of armies is not surpassing the limit?
	//cout << "cubes " << *cubes << " value " << *value << endl;
	if (*cubes - *value >= 0) {

		bool rOwned = false;
		for (std::list<Region>::iterator it = (*regionOwned).begin(); it != (*regionOwned).end(); ++it) {
			if (it->compareRegions(region)) {
				rOwned = true;
				break;
			}
		}
		if (!rOwned) {
			regionOwned->push_back(*region);
		}

		//std::stoi(regCont.find(std::to_string(*(itNeigh->val)))->second;
		//std::cout << chosenColor << ": " << region->numberOfArmiesPerPlayer[chosenColor] << ", ";
		//std::cout << chosenColor << ": " << region->numberOfArmiesPerPlayer.find(chosenColor)->second << ", ";
		
		MoveDesc md;
		md.regionFrom = region;
		md.regionTo = nullptr;

		moveDesc->push_back(md);
		
		region->numberOfArmiesPerPlayer[chosenColor] = region->numberOfArmiesPerPlayer.find(chosenColor)->second + *value;
		*(region->numberOfArmy) = *(region->numberOfArmy) + *value; // add army to the region
		*cubes = *cubes - *value;
		//std::cout << chosenColor << ": " << region->numberOfArmiesPerPlayer[chosenColor] << ", ";
		//std::cout << chosenColor << ": " << region->numberOfArmiesPerPlayer.find(chosenColor)->second << ", ";
		//std::cout << endl;

	}
	//region->display();
	//cout << "end  ---- -This allows a player to place new armies in a certain region." << endl;

}

void Player::displayArmies()
{
	cout << "Regions and armies for player " << endl;

	for (std::list<Region>::iterator it = (*regionOwned).begin(); it != (*regionOwned).end(); ++it) {
		std::cout << *(it->val) << " ----- " << it->numberOfArmiesPerPlayer.find(chosenColor)->second << endl;
	}

}

void Player::moveArmies(Region* regionFrom, Region* regionTo, int* value)
{
	//have to remove the armies from the region where they were and put them in the new region
	cout << "This allows a player to move a number of armies from one region to another." << endl;


	if (*(regionFrom->continent) != *(regionTo->continent)) {
		cout << "Can't move armies to another continent!";
	}
	else {
		MoveDesc md;
		md.regionFrom = regionFrom;
		md.regionTo = regionTo;

		moveDesc->push_back(md);

		for (std::list<Region>::iterator it = (*regionOwned).begin(); it != (*regionOwned).end(); ++it) {
			if (it->compareRegions(regionFrom)) {
				regionFrom->numberOfArmiesPerPlayer[chosenColor] = regionFrom->numberOfArmiesPerPlayer[chosenColor] - *value;
				*(regionFrom->numberOfArmy) = *(regionFrom->numberOfArmy) - *value;

				if (regionFrom->numberOfArmiesPerPlayer[chosenColor] == 0) {
					(*regionOwned).remove(*regionFrom);

				}

				break;

			}
		}

		if (!	isRegionOwned(regionTo)) {
			regionOwned->push_back(*regionTo);
		}
		regionTo->numberOfArmiesPerPlayer[chosenColor] = regionTo->numberOfArmiesPerPlayer[chosenColor] + *value;
		*(regionTo->numberOfArmy) = *(regionTo->numberOfArmy) + *value;
		//no need to change the value of cubes since we're moving armies that were already on the board
		//*cubes = *cubes + *value;

	}

}

void Player::moveOverLand(Region* regionFrom, Region* regionTo, int* value)
{
	cout << "This allows a player to move a number of armies from one region to another and he can go over continents." << endl;


	for (std::list<Region>::iterator it = (*regionOwned).begin(); it != (*regionOwned).end(); ++it) {
		if (it->compareRegions(regionFrom)) {
			regionFrom->numberOfArmiesPerPlayer[chosenColor] = regionFrom->numberOfArmiesPerPlayer[chosenColor] - *value;

			if (regionFrom->numberOfArmiesPerPlayer[chosenColor] == 0) {
				(*regionOwned).remove(*regionFrom);
			}
			break;
		}
	}

	regionOwned->push_back(*regionTo);
	regionTo->numberOfArmiesPerPlayer[chosenColor] = regionTo->numberOfArmiesPerPlayer[chosenColor] + *value;


}

void Player::buildCity(Region* region)
{
	//add a city to the region picked -> region already to the player
	cout << "This adds a city to the region picked by the player, the player must have the region and he can add more than one city." << endl;

	if (discs != 0) {
		bool isRegionOwned = false;

		for (std::list<Region>::iterator it = (*regionOwned).begin(); it != (*regionOwned).end(); ++it) {
			if (it->compareRegions(region)) {
				MoveDesc md;
				md.regionFrom = region;
				md.regionTo = nullptr;

				moveDesc->push_back(md);

				isRegionOwned = true;
				region->numberOfCityPerPlayer[chosenColor] = region->numberOfCityPerPlayer[chosenColor] + 1;
				*(region->cityNumber) = *(region->cityNumber) + 1;
				*discs = *discs - 1;
				break;
			}
		}
		if (!isRegionOwned) {
			MoveDesc md;
			md.regionFrom = nullptr;
			md.regionTo = nullptr;

			//moveDesc->push_back(md);
			std::cout << "You can not build a city in this region because you do not have any armies!" << std::endl;
		}
	}
	else {
		std::cout << "You have 0 discs!" << std::endl;
	}



}

bool Player::isRegionOwned(Region* region)
{
	for (std::list<Region>::iterator it = regionOwned->begin(); it != regionOwned->end(); ++it) {
		if (it->compareRegions(region)) {
			return true;
		}
	}
	return false;
}

void Player::destroyArmy(Region* region, int* value)
{
	//destroy an army from a specific region
	cout << "This removes a number of armies from a specific region for the player." << endl;


	if (*cubes != 14) {


		for (std::list<Region>::iterator it = (*regionOwned).begin(); it != (*regionOwned).end(); ++it) {
			if (it->compareRegions(region)) {
				region->numberOfArmiesPerPlayer[chosenColor] = region->numberOfArmiesPerPlayer[chosenColor] - *value; // remove
				*(region->numberOfArmy) = *(region->numberOfArmy) - 1;
				MoveDesc md;
				md.regionFrom = region;
				md.regionTo = nullptr;

				moveDesc->push_back(md);
				break;
			}
		}

		*cubes = *cubes + *value;
	}


}

void Player::setChosenColor(Colors c)
{
	chosenColor = c;

}

void Player::ignore() {
	cout << "This action is ignored.";
}

int Player::choose_Card()
{
	return playerStrategy->chooseCard();
}

int Player::choose_target_region(string action, Map m, int numberOfArmiesToMove)
{
	return playerStrategy->chooseTargetRegion(action, m, numberOfArmiesToMove);
}

int Player::choose_to_ignore_action(string action)
{
	return playerStrategy->chooseToIgnoreAction(action);
}

int Player::choose_destination_Region(string action, Map m, int fromRegion)
{
	return playerStrategy->chooseDestinationRegion(action, m, fromRegion);
}

int Player::choose_number_army_move(int numberOfArmiesLeftToMove)
{
	return playerStrategy->chooseNumberOfArmyToMove(numberOfArmiesLeftToMove);
}

int Player::choose_playerID(int numberOfPlayers)
{
	return playerStrategy->choosePlayerToDestroyArmy(numberOfPlayers);
}

Player::Player()
{
}

void Player::takeCard(Cards chosenCard)
{
	(*cards).push_back(chosenCard);
	displayCardsInHand();
	//chosenCard.singleAction.display();
}

void Player::displayCardsInHand() {
	cout << "\n\nYour hand: \n";
	cout << "------------" << endl;
	for (std::list <Cards>::const_iterator i = (*cards).begin(); i != (*cards).end(); ++i) {
		
		cout << "Action: " << (*i).singleAction.action << "\tAmount: " << (*i).singleAction.amount;
		cout << "\n------------" << endl;
	}

}

void Player::categorizeGoods(string good) {
	if (good == "FOREST") {
		goodsNumber[0] += 1;
	}
	else if (good == "CARROT") {
		goodsNumber[1] += 1;
	}
	else if (good == "ANVIL") {
		goodsNumber[2] += 1;
	}
	else if (good == "ORE") {
		goodsNumber[3] += 1;
	}
	else if (good == "CRYSTAL") {
		goodsNumber[4] += 1;
	}
}

void Player::findNbArmiesPerRegion(int totalNbRegions)
{
	nbArmiesAndCitiesPerRegion.resize(totalNbRegions, 0); //initializing all elements to 0

	for (std::list<Region>::iterator it = (*regionOwned).begin(); it != (*regionOwned).end(); ++it) {
		nbArmiesAndCitiesPerRegion.at((*(it->val))-1) = it->numberOfArmiesPerPlayer.find(chosenColor)->second;
		nbArmiesAndCitiesPerRegion.at((*(it->val)) - 1) += it->numberOfCityPerPlayer.find(chosenColor)->second;

		*totalNbArmies += it->numberOfArmiesPerPlayer.find(chosenColor)->second;
	}
}

/*
int Player::computeScore(vector<int> finalRegionControllers, int playerNumber) //regions, continents, goods
{
	*nbControllingRegions = 0;

	//regions: more armies in region than any other player on region
	for (int i = 0; i < finalRegionControllers.size(); i++) {
		if (finalRegionControllers.at(i) == playerNumber) {
			score++; //adds one point per regions they control
			*nbControllingRegions++;
		}
	}

	//GOODS: points differ according to good (can choose where the wild card goes)
	cout << "Your current cards: \n" << endl;

	for (std::list <Cards>::const_iterator i = (*cards).begin(); i != (*cards).end(); ++i) {
		cout << "\n" << (*i).good << endl;
		//(*i).singleAction.display();
		SingleAction currentCard = (i->singleAction);
		currentCard.display();
	}

	for (std::list <Cards>::const_iterator i = (*cards).begin(); i != (*cards).end(); ++i) {
		if ((*i).good == "WILD") {
			string wildValue;
			cout << "You have a wild card. To what good would you like to associate with?\n"
				<< "FOREST | CARROT | ANVIL | ORE | CRYSTAL" << endl;
			cin >> wildValue;

			categorizeGoods(wildValue);
		}
		else {
			categorizeGoods((*i).good);
		}
	}

	switch (goodsNumber[0]) { //forest points
	case 2:
	case 3: score += 1;
		break;
	case 4:
	case 5: score += 2;
		break;
	case 6: score += 3;
		break;
	case 7: 
	case 8: score += 5;
		break;
	default: score =+ 0;
	}

	switch (goodsNumber[1]) { //carrot points
	case 3:
	case 4: score += 1;
		break;
	case 5:
	case 6: score += 2;
		break;
	case 7: score += 3;
		break;
	case 8:
	case 9:
	case 10: score += 5;
		break;
	default: score += 0;
	}

	switch (goodsNumber[2]) { //anvil points
	case 2:
	case 3: score += 1;
		break;
	case 4:
	case 5: score += 2;
		break;
	case 6: score += 3;
		break;
	case 7:
	case 8:
	case 9: score += 5;
		break;
	default: score += 0;
	}

	switch (goodsNumber[3]) { //ore points
	case 2: score += 1;
		break;
	case 3: score += 2;
		break;
	case 4: score += 3;
		break;
	case 5:
	case 6:
	case 7: score += 5;
		break;
	default: score += 0;
	}

	switch (goodsNumber[4]) { //crystal points
	case 1: score += 1;
		break;
	case 2: score += 2;
		break;
	case 3: score += 3;
		break;
	case 4:
	case 5: score += 4;
		break;
	default: score += 0;
	}
	
	return score;
}
*/

void Player::computeScore(Map map, bool isTournament) //regions, continents, goods
{
	*nbControllingRegions = 0;

	//regions: more armies in region than any other player on region
	for (std::list <Region>::const_iterator it = regionOwned->begin(); it != regionOwned->end(); ++it) {
		if ((Colors)*(it->regionOwner) == chosenColor) {
			(*playerScore)++;
			(*nbControllingRegions)++;
		}
	}

	//GOODS: points differ according to good (can choose where the wild card goes)
	cout << "Your current cards: \n" << endl;

	for (std::list <Cards>::const_iterator i = (*cards).begin(); i != (*cards).end(); ++i) {
		cout << "\n" << (*i).good << endl;
		//(*i).singleAction.display();
		SingleAction currentCard = (i->singleAction);
		currentCard.display();
	}

	for (std::list <Cards>::const_iterator i = (*cards).begin(); i != (*cards).end(); ++i) {
		if ((*i).good == "WILD") {
			string wildValue;
			cout << "You have a wild card. To what good would you like to associate with?\n"
				<< "FOREST | CARROT | ANVIL | ORE | CRYSTAL" << endl;
			if (isTournament) {
				int a = rand() % 5;
				switch (a)
				{
				case 0:
					wildValue = "FOREST";
					break;
				case 1:
					wildValue = "CARROT";
					break;
				case 2:
					wildValue = "ANVIL";
					break;
				case 3:
					wildValue = "ORE";
					break;
				case 4:
					wildValue = "CRYSTAL";
					break;

				default:
					break;
				}
				
			}
			else {
				cin >> wildValue;
			}


			categorizeGoods(wildValue);
		}
		else {
			categorizeGoods((*i).good);
		}
	}

	switch (goodsNumber[0]) { //forest points
	case 2:
	case 3: (*playerScore) += 1;
		break;
	case 4:
	case 5: (*playerScore) += 2;
		break;
	case 6: (*playerScore) += 3;
		break;
	case 7:
	case 8: (*playerScore) += 5;
		break;
	default: (*playerScore) = +0;
	}

	switch (goodsNumber[1]) { //carrot points
	case 3:
	case 4: (*playerScore) += 1;
		break;
	case 5:
	case 6: (*playerScore) += 2;
		break;
	case 7: (*playerScore) += 3;
		break;
	case 8:
	case 9:
	case 10: (*playerScore) += 5;
		break;
	default: (*playerScore) += 0;
	}

	switch (goodsNumber[2]) { //anvil points
	case 2:
	case 3: (*playerScore) += 1;
		break;
	case 4:
	case 5: (*playerScore) += 2;
		break;
	case 6: (*playerScore) += 3;
		break;
	case 7:
	case 8:
	case 9: (*playerScore) += 5;
		break;
	default: (*playerScore) += 0;
	}

	switch (goodsNumber[3]) { //ore points
	case 2: (*playerScore) += 1;
		break;
	case 3: (*playerScore) += 2;
		break;
	case 4: (*playerScore) += 3;
		break;
	case 5:
	case 6:
	case 7: (*playerScore) += 5;
		break;
	default: (*playerScore) += 0;
	}

	switch (goodsNumber[4]) { //crystal points
	case 1: (*playerScore) += 1;
		break;
	case 2: (*playerScore) += 2;
		break;
	case 3: (*playerScore) += 3;
		break;
	case 4:
	case 5: (*playerScore) += 4;
		break;
	default: (*playerScore) += 0;
	}

	//return score;
}
