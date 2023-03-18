#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <iostream>
#include <list>
#include <ostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <map>
#include "../GameEngine/GameEngine.h"

//#include "../Player/Player.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::list;
using std::ostream;
using std::istream;
using std::stoi;
using std::ifstream;
using std::stringstream;
using std::map;

class Player; //forward declaration
class GameEngine; //forward declaration

class Territory {
private:
    int *id;
    int *continentId; //a part of which continent
    int *armyCount;
    string *territoryName; //name of territory
    vector<int> *borders;  // ids of adjacent territories
    Player *owner; //owner of the territory
    vector<Territory *> *borderedTerritories; //adjacent territories
public:
    //constructors
    Territory(); //default constructor
    Territory(int inId, int inContinentId, string inTerritoryName); //constructor
    Territory(const Territory &copy); //copy constructor
    Territory& operator=(const Territory& t); //assignment operator
    friend ostream& operator<<(ostream& os, const Territory& t);
    ~Territory(); //destructor

    //getters and setters
    void setId(int *inId);
    int *getId() const;
    void setContinentId(int *inContinentId);
    int *getContinentId() const;
    void setArmyCount(int *inArmyCount);
    int *getArmyCount() const;
    void setTerritoryName(string *inTerritoryName);
    string *getTerritoryName() const;
    void setBorders(vector<int> *inBorders);
    vector<int> *getBorders() const;
    void setOwner(Player *inPlayer);
    Player *getOwner() const;
    static void setBorderedTerritories(Territory *inTerritory, vector<Territory *> *Territories);
    vector<Territory *> *getBorderedTerritories() const;

    void testSetBorders(vector<Territory *>* b); // Tristan: for dev purposes, delete later
};

class Continent {
private:
    int *id;
    string *continentName;
    int *value;
    vector<Territory *> *territoriesInContinent; //territories that are a part of this continent
public:
    //constructors
    Continent(); //default constructor
    Continent(int inId, string inContinentName, int inValue); //constructor
    Continent(const Continent &copy); //copy constructor
    Continent& operator=(const Continent& c); //assignment operator
    friend ostream& operator<<(ostream& os, const Continent& c);
    ~Continent(); //destructor

    //getters and setters
    void setId(int *inId);
    int *getId() const;
    void setContinentName(string *inContinentName);
    string *getContinentName() const;
    void setValue(int *inValue);
    int *getValue() const;
    static void setTerritoriesInContinent(Continent *inContinent, vector<Territory *> *inTerritoriesInContinent);
    vector<Territory *> *getTerritoriesInContinent() const;
    void testSetTerritories(vector<Territory *>* t); // Tristan: for dev purposes, remove later
};

class Map {
private:
    int *id;
    string *name;
    vector<Continent *> *continents;
    vector<Territory *> *territories;

    bool **continentMatrix;
    bool **territoryMatrix;

public:
    //constructors
    Map(); //default constructor
    Map(int inId, string inName, vector<Continent *> inContinents, vector<Territory *> inTerritories); //constructor
    Map(const Map &copy); //copy constructor
    Map& operator=(const Map& m); //assignment operator
    friend ostream& operator<<(ostream& os, const Map& m);
    ~Map(); //destructor

    //getters and setters
    void setId(int *inId);
    int *getId() const;
    void setName(string *inName);
    string *getName() const;
    void setContinents(vector<Continent *> *inContinents);
    vector<Continent *> *getContinents() const;
    void setTerritories(vector<Territory *> *inTerritories);
    vector<Territory *> *getTerritories() const;

    //validation methods
    bool validate();
    bool isConnectedGraph();
    bool isConnectedSubgraph();
    bool oneContinentPerTerritory();

    //methods
    void addTerritoryEdge(Territory *t1, Territory *t2);
    bool isTerritoryConnected(Territory *t1, Territory *t2);
    void printTerritoryMap();

    void addContinentEdge(Continent *c1, Continent *c2);
    bool isContinentConnected(Continent *c1, Continent *c2);
    void printContinentMap();

};

enum PARSE_MODE {
    UNSPECIFIED,
    FILES,
    CONTINENTS,
    TERRITORIES,
    BORDERS
};

class MapLoader {
private:
    // attributes
    string* path;

    // static methods
    static PARSE_MODE getMode(const string& inputString);

public:
    // Constructors
    MapLoader(); //default constructor
    MapLoader(const MapLoader &copy); //copy constructor
    MapLoader& operator=(const MapLoader& ml); //assignment operator
    friend ostream& operator<<(ostream& os, const MapLoader& ml); //stream insertion operator
    ~MapLoader(); //destructor

    // Getters & Setters
    void setPath(string *inputPath);
    string *getPath() const;

    // Methods
    Map load(int mapNumber);
    static vector<string> getTokens(const string& inputString);
};
int mapTest();
#endif //MAP_H