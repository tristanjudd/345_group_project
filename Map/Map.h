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


class Territory {
private:
    int *id;
    int *continentId; //a part of which continent
    int *armyCount;
    string *territoryName; //name of territory
    vector<int> *borders;  // ids of adjacent territories
    //Player *owner; //owner of the territory
public:
    //constructors
    Territory(); //default constructor
    Territory(int inId, int inContinentId, string inTerritoryName); //constructor
    Territory(const Territory &copy); //copy constructor
    Territory& operator=(const Territory& t); //assignment operator
    friend ostream& operator<<(ostream& os, const Territory& t);
    ~Territory(); //destructor

    //getters and setters
    void setId(int inId);
    int *getId();
    void setContinentId(int inContinentId);
    int *getContinentId();
    void setArmyCount(int inArmyCount);
    int *getArmyCount();
    void setTerritoryName(string inTerritoryName);
    string *getTerritoryName();
    void setBorders(vector<int> inBorders);
    vector<int> *getBorders();
};

class Continent {
private:
    int *id;
    string *continentName;
    int *value;
public:
    //constructors
    Continent(); //default constructor
    Continent(int inId, string inContinentName, int inValue); //constructor
    Continent(const Continent &copy); //copy constructor
    Continent& operator=(const Continent& c); //assignment operator
    friend ostream& operator<<(ostream& os, const Continent& c);
    ~Continent(); //destructor

    //getters and setters
    void setId(int inId);
    int *getId();
    void setContinentName(string inContinentName);
    string *getContinentName();
    void setValue(int inValue);
    int *getValue();
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
    void setId(int inId);
    int *getId();
    void setName(string inName);
    string *getName();
    void setContinents(vector<Continent *> inContinents);
    vector<Continent *> *getContinents();
    void setTerritories(vector<Territory *> inTerritories);
    vector<Territory *> *getTerritories();

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
    std::string* path;

    // static methods
    static PARSE_MODE getMode(const string& inputString);
    static vector<string> getTokens(const string& inputString);

public:
    // Constructors
    MapLoader();

    // Getters & Setters
    std::string getPath();
    void setPath(std::string* inputPath);

    // Methods
    Map load(int mapNumber);
};

#endif //MAP_H