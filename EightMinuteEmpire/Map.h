#ifndef MAP_H
#define MAP_H

#include <list>
#include <string>
#include <map>

enum Colors { Red, Blue, Yellow, Green, White };

//graph


//node
class Region // or country
{

public:

	int* continent;
	int* val; // id of the region NOT UNIQUE
	std::list <Region>* next; // adjacency - edges ( can point to more than one other region? )
	int* numberOfArmy;
	std::map<Colors, int> numberOfArmiesPerPlayer;
	std::map<Colors, int> numberOfCityPerPlayer;
	int* cityNumber;
	bool* startingRegion;
	Region(int v, int c);
	Region(const Region& region);
	~Region();
	bool compareRegions(Region* reg);
	bool operator==(const Region& argument) const;

	std::string playerPath();
	Region* validateMove(Region* currentR, int* numberOfMoves, std::string s);
	void display();
	void simple_display();
	void setStartingRegion(bool b);
	//int readPlayerArmy(); //isn't a pointer: if pointer, function needs to return pointer??

};

class Map
{
/*
	Region* getAdjListNode(int dest, Region* head)
	{

		Region* newNode = new Region;
		newNode -> val = &dest; //val needs to reference the address of dest?

		newNode -> next = head;

		return newNode;
	}
*/

public:

	std::list <Region>* eightMinEmpMap;
	Region* startingRegion;

	Map continentSubMap(int continent);
	bool isConnected();

	void traverse(Region u, std::list<Region>& visited);
	void display();
	void setStartingRegion(Region* startingR);
	Region getStartingRegion();
	void addRegion(Region r);

	int findNbRegions();

	Region* findRegion(int val);

	Map();

};

/*

initializing a region would set its continent its id and its adjacency + a null number of army and cities and of goods?

*/

//extern: looks for definition in another translation unit (Game.cpp)
//static int *nbRegions;

#endif