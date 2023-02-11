#include "Map.h"

// Territory class
// default constructor
Territory::Territory() {
    id = new int(0);
    continentId = new int(0); //todo discuss with jay
    armyCount = new int(0);
    territoryName = new string("");
    borders = new vector<int>();
    //owner = new Player(); //todo
    cout << "Territory default constructor called" << endl;
}

// constructor for loader
Territory::Territory(int inId, int inContinentId, string inTerritoryName) {
    id = new int(inId);
    continentId = new int(inContinentId);
    armyCount = new int(0);
    territoryName = new string(inTerritoryName);
    borders = new vector<int>(); //todo test
    // owner = new Player(*inOwner); //todo
    cout << "Territory constructor called" << endl;
}

// copy constructor
Territory::Territory(const Territory &copy) {
    id = new int(*copy.id);
    continentId = new int(*copy.continentId);
    armyCount = new int(*copy.armyCount);
    territoryName = new string(*copy.territoryName);
    borders = new vector<int>(*copy.borders); //todo test
    cout << "Territory copy constructor called" << endl;
}

// assignment operator
Territory &Territory::operator=(const Territory &t) {
    if (this != &t) {
        id = t.id;
        continentId = t.continentId;
        armyCount = t.armyCount;
        territoryName = t.territoryName;
        borders = t.borders;
    }
    return *this;
}

// stream insertion operator
ostream &operator<<(ostream &out, const Territory &c) {
    out << "Territory ID: " << *c.id << endl;
    out << "Continent ID: " << *c.continentId << endl;
    out << "Army Count: " << *c.armyCount << endl;
    out << "Territory Name: " << *c.territoryName << endl;
    out << "Borders: ";
    for (int i = 0; i < c.borders->size(); i++) {
        out << c.borders->at(i) << " ";
    }
    out << endl;
    return out;
}

// destructor
Territory::~Territory() { //todo check if this is correct
    delete id;
    delete continentId;
    delete armyCount;
    delete territoryName;
    // delete owner;
    id = nullptr;
    continentId = nullptr;
    armyCount = nullptr;
    territoryName = nullptr;
    // owner = nullptr;
    cout << "Territory destructor called" << endl;
}

// getters and setters
void Territory::setId(int *inId) {
    id = inId;
}

int *Territory::getId() const {
    return id;
}

void Territory::setContinentId(int *inContinentId) {
    continentId = inContinentId;
}

int *Territory::getContinentId() const{
    return continentId;
}

void Territory::setArmyCount(int *inArmyCount) {
    armyCount = inArmyCount;
}

int *Territory::getArmyCount() const {
    return armyCount;
}

void Territory::setTerritoryName(string *inTerritoryName) {
    territoryName = inTerritoryName;
}

string *Territory::getTerritoryName() const {
    return territoryName;
}

void Territory::setBorders(vector<int> *inBorders) {
    borders = new vector<int>(*inBorders);
}

vector<int> *Territory::getBorders() const {
    return borders;
}

// Continent class
// default constructor
Continent::Continent() {
    id = new int(0);
    continentName = new string("");
    value = new int(0);
    cout << "Continent default constructor called" << endl;
}

// constructor for loader
Continent::Continent(int inId, string inContinentName, int inValue) {
    id = new int(inId);
    continentName = new string(inContinentName);
    value = new int(inValue);
    cout << "Continent constructor called" << endl;
}

// copy constructor
Continent::Continent(const Continent &copy) {
    id = new int(*copy.id);
    continentName = new string(*copy.continentName);
    value = new int(*copy.value);
    cout << "Continent copy constructor called" << endl;
}

// assignment operator
Continent &Continent::operator=(const Continent &c) {
    if (this != &c) {
        id = c.id;
        continentName = c.continentName;
        value = c.value;
    }
    return *this;
}

// stream insertion operator
ostream &operator<<(ostream &out, const Continent &c) {
    out << "Continent ID: " << *c.id << endl;
    out << "Continent Name: " << *c.continentName << endl;
    out << "Continent Value: " << *c.value << endl;
    return out;
}

// destructors
Continent::~Continent() { //todo check if this is correct
    delete id;
    delete continentName;
    delete value;
    id = nullptr;
    continentName = nullptr;
    value = nullptr;
    cout << "Continent destructor called" << endl;
}

// getters and setters
void Continent::setId(int *inId) {
    id = inId;
}

int *Continent::getId() const{
    return id;
}

void Continent::setContinentName(string *inContinentName) {
    continentName = inContinentName;
}

string *Continent::getContinentName() const {
    return continentName;
}

void Continent::setValue(int *inValue) {
    value = inValue;
}

int *Continent::getValue() const {
    return value;
}

// Map class
// default constructor
Map::Map() {
    cout << "Map default constructor called" << endl;
    id = new int(0);
    name = new string("");
    territories = new vector<Territory *>();
    continents = new vector<Continent *>();
    territoryMatrix = new bool *[territories->size()];
    continentMatrix = new bool *[continents->size()];
    for (int i = 0; i < territories->size(); i++) {
        territoryMatrix[i] = new bool[territories->size()];
        for (int j = 0; j < territories->size(); j++) {
            territoryMatrix[i][j] = false;
        }
    }
    for (int i = 0; i < continents->size(); i++) {
        continentMatrix[i] = new bool[continents->size()];
        for (int j = 0; j < continents->size(); j++) {
            continentMatrix[i][j] = false;
        }
    }
}

// constructor for loader
Map::Map(int inId, string inName, vector<Continent *> inContinents, vector<Territory *> inTerritories) {
    cout << "Map constructor called" << endl;
    id = new int(inId);
    name = new string(inName);
    continents = new vector<Continent *>(inContinents);
    territories = new vector<Territory *>(inTerritories);
    territoryMatrix = new bool *[territories->size()];
    continentMatrix = new bool *[continents->size()];
    for (int i = 0; i < territories->size(); i++) {
        territoryMatrix[i] = new bool[territories->size()];
        for (int j = 0; j < territories->size(); j++) {
            territoryMatrix[i][j] = false;
        }
    }
    for (int i = 0; i < continents->size(); i++) {
        continentMatrix[i] = new bool[continents->size()];
        for (int j = 0; j < continents->size(); j++) {
            continentMatrix[i][j] = false;
        }
    }
}

// copy constructor
Map::Map(const Map &copy) {
    cout << "Map copy constructor called" << endl;
    id = new int(*copy.id);
    name = new string(*copy.name);
    territories = new vector<Territory *>(*copy.territories);
    continents = new vector<Continent *>(*copy.continents);
    territoryMatrix = new bool *[copy.territories->size()];
    continentMatrix = new bool *[copy.continents->size()];
    for (int i = 0; i < copy.territories->size(); i++) {
        territoryMatrix[i] = new bool[copy.territories->size()];
        for (int j = 0; j < copy.territories->size(); j++) {
            territoryMatrix[i][j] = copy.territoryMatrix[i][j];
        }
    }
    for (int i = 0; i < copy.continents->size(); i++) {
        continentMatrix[i] = new bool[copy.continents->size()];
        for (int j = 0; j < copy.continents->size(); j++) {
            continentMatrix[i][j] = copy.territoryMatrix[i][j];
        }
    }
}

// assignment operator
Map &Map::operator=(const Map &m) {
    if (this != &m) {
        id = m.id;
        name = m.name;
        territories = m.territories;
        continents = m.continents;
        for (int i = 0; i < m.territories->size(); i++) {
            for (int j = 0; j < m.territories->size(); j++) {
                territoryMatrix[i][j] = m.territoryMatrix[i][j];
            }
        }
        for (int i = 0; i < m.continents->size(); i++) {
            for (int j = 0; j < m.continents->size(); j++) {
                continentMatrix[i][j] = m.territoryMatrix[i][j];
            }
        }
    }
    return *this;
}

// stream insertion operator
ostream &operator<<(ostream &out, const Map &m) {
    out << "Map ID: " << *m.id << endl;
    out << "Map Name: " << *m.name << endl;
    out << "Map Territories: " << endl;
    for (int i = 0; i < m.territories->size(); i++) {
        out << *m.territories->at(i)->getId() << " ";
        out << *m.territories->at(i)->getTerritoryName() << " ";
        out << *m.territories->at(i)->getContinentId() << endl;
    }
    out << "Map Continents: " << endl;
    for (int i = 0; i < m.continents->size(); i++) {
        out << *m.continents->at(i)->getId() << " ";
        out << *m.continents->at(i)->getContinentName() << " ";
        out << *m.continents->at(i)->getValue() << endl;
    }
    return out;
}

// destructor
Map::~Map() {
    cout << "Map destructor called" << endl;
    delete id;
    delete name;
    delete territories;
    delete continents;
    id = nullptr;
    name = nullptr;
    territories = nullptr;
    continents = nullptr;
}

// getters and setters
void Map::setId(int *inId) {
    id = inId;
}
int *Map::getId() const {
    return id;
}
void Map::setName(string *inName) {
    name = inName;
}
string *Map::getName() const {
    return name;
}
void Map::setContinents(vector<Continent *> *inContinents) {
    continents = inContinents;
}
vector<Continent *> *Map::getContinents() const {
    return continents;
}

void Map::setTerritories(vector<Territory *> *inTerritories) {
    territories = inTerritories;
}

vector<Territory *> *Map::getTerritories() const {
    return territories;
}

// link 2 territories
void Map::addTerritoryEdge(Territory *t1, Territory *t2) {
    if ((*t1->getId()) != (*t2->getId())) {
        territoryMatrix[*t1->getId()][*t2->getId()] = true;
    }
}

// check if 2 territories are connected
bool Map::isTerritoryConnected(Territory *t1, Territory *t2) {
    return territoryMatrix[*t1->getId()][*t2->getId()];
}

// print the territory map
void Map::printTerritoryMap() {
    for (int i = 0; i < territories->size(); i++) {
        cout << "Territory " << i << " is connected to: ";
        for (int j = 0; j < territories->size(); j++) {
            if (territoryMatrix[i][j]) {
                cout << j << " ";
            }
        }
        cout << endl;
    }
}

// link 2 continents
void Map::addContinentEdge(Continent *c1, Continent *c2) {
    if ((*c1->getId()) != (*c2->getId())) {
        continentMatrix[*c1->getId()][*c2->getId()] = true;
    }
}

// check if 2 continents are connected
bool Map::isContinentConnected(Continent *c1, Continent *c2) {
    return continentMatrix[*c1->getId()][*c2->getId()];
}

// print the continent map
void Map::printContinentMap() {
    for (int i = 0; i < continents->size(); i++) {
        cout << "Continent " << i << " is connected to: ";
        for (int j = 0; j < continents->size(); j++) {
            if (continentMatrix[i][j]) {
                cout << j << " ";
            }
        }
        cout << endl;
    }
}

// check if all territories are connected
bool Map::isConnectedGraph() {
    int *terrCount = new int(0);
    for (int i = 0; i < territories->size(); i++) {
        for (int j = 0; j < territories->size(); j++) {
            if (territoryMatrix[*territories->at(i)->getId()][j]) {
                *terrCount = ++*terrCount; //increment terrCount if the territory has a connection
                break;
            }
        }
    }
    if (*terrCount == territories->size()) { //if all territories have a connection
        return true;
    }
    return false;
}

// check if all continents are connected
bool Map::isConnectedSubgraph() {
    int *contCount = new int(0);
    for (int i = 0; i < continents->size(); i++) {
        for (int j = 0; j < continents->size(); j++) {
            if (continentMatrix[*continents->at(i)->getId()][j]) {
                *contCount = ++*contCount; //increment contCount the continent has a connection
                break;
            }
        }
    }
    if (*contCount == continents->size()) { //if all continents have a connection
        return true;
    }
    return false;
}

// checks that all territories are in a continent and that no continent is empty
// checks that all continents consist of at least 1 territory
bool Map::oneContinentPerTerritory() {
    int *terrCount = new int(0);
    int *contCount = new int(0);
    int *temp = new int(-1);
    for (int i = 0; i < continents->size(); i++) { //iterate through continents
        for (int j = 0; j < territories->size(); j++) { //iterate through territories
            if (*territories->at(j)->getContinentId() != -1 &&
                *territories->at(j)->getContinentId() == *continents->at(i)->getId()) {
                *terrCount = ++*terrCount; //increment terrCount if they are in a continent
                if (*temp != i) { //true if continent isn't already validated
                    *temp = i; //set to i so that contCount doesn't increment again until new continent is reached
                    *contCount = ++*contCount;
                }
            }
        }
    }
    //return true if territory size = terrCount meaning that all territories are in a continent
    //return true if continent size = contCount meaning that all continents have at least 1 territory
    if (*terrCount == territories->size() && *contCount == continents->size()) {
        return true;
    }
    return false;
}

bool Map::validate() {
    //true if all these functions return true
    if (isConnectedGraph() && isConnectedSubgraph() && oneContinentPerTerritory()) {
        return true;
    }
    return false;
}

// Map Loader
// default constructor
MapLoader::MapLoader() {
    path = nullptr;
}

// copy constructor
MapLoader::MapLoader(const MapLoader &mapLoader) {
    path = new string(*mapLoader.path);
}

// assignment operator
MapLoader &MapLoader::operator=(const MapLoader &mapLoader) {
    path = mapLoader.path;
    return *this;
}

// stream insertion operator
ostream &operator<<(ostream &out, const MapLoader &mapLoader) {
    out << "MapLoader: " << mapLoader.path;
    return out;
}

// destructor
MapLoader::~MapLoader() {
    cout << "MapLoader destructor called" << endl;
    delete path;
}

//getters/setters
void MapLoader::setPath(string *inputPath) {
    path = inputPath;
}
string *MapLoader::getPath() const {
    return path;
}

// Loads the input file and returns a full map object
Map MapLoader::load(int mapNumber) {
    printf("Loading %s...\n", path->c_str());

    ifstream file(path->c_str());
    PARSE_MODE mode = UNSPECIFIED;

    vector<Territory *> *territories = new vector<Territory*>();  // countries
    vector<Continent *> *continents = new vector<Continent*>();
    int continentCounter = 1;

    // Iterate over each line, and create object based on parsing mode
    string line;
    vector<string> tokens;
    while (getline (file, line)) {
        if (line.starts_with('[')) {
            mode = getMode(line);
            continue;
        }

        tokens = getTokens(line);
        if (tokens.empty()) {
            continue;  // Skip empty line
        }

        switch (mode) {
            case UNSPECIFIED: {
                printf("No mode specified, skipping...\n");
                break;
            }
            case FILES: {
                printf("Skipping files for Phase 1...\n");
                break;
            }
            case TERRITORIES: {
                printf("Parsing territory %s...\n", tokens[1].c_str());
                territories->push_back(new Territory(stoi(tokens[0]),
                                                     stoi(tokens[2]),
                                                     tokens[1]));
                break;
            }
            case CONTINENTS: {
                printf("Parsing continent %s...\n", tokens[0].c_str());
                continents->push_back(new Continent(continentCounter++,
                                                    tokens[0],
                                                    stoi(tokens[1])));
                break;
            }
            case BORDERS: {
                printf("Parsing %s borders...\n", territories->at(stoi(tokens[0]) - 1)->getTerritoryName()->c_str());
                vector<int>* borders = new vector<int>();

                for (int i = 1; i < tokens.size(); i++) {
                    borders->push_back(stoi(tokens[i]));
                }

                territories->at(stoi(tokens[0])-1)->setBorders(borders);
                break;
            }
        }
    }

    Map* map = new Map(mapNumber,
                       "Unnamed Map...",
                       *continents,
                       *territories);

    // Create territory and continent matrix
    for (Territory* territory : *map->getTerritories()) {
        for (int border : *territory->getBorders()) {
            // add a territory edge between each border territory
            Territory* borderTerritory = map->getTerritories()->at(border - 1);
            map->addTerritoryEdge(territory, borderTerritory);

            // if the border territory is in a different continent than this territory, add a continent edge
            int territoryContinentId = *territory->getContinentId();
            int borderContinentId = *borderTerritory->getContinentId();
            Continent* territoryContinent = map->getContinents()->at(territoryContinentId - 1);
            Continent* borderContinent = map->getContinents()->at(borderContinentId - 1);
            if (borderContinentId != territoryContinentId) {
                map->addContinentEdge(territoryContinent, borderContinent);
            }
        }
    }

    printf("Closing %s...\n", path->c_str());
    file.close();

    return *map;
}

// Switch the parsing mode based on the [flag]
PARSE_MODE MapLoader::getMode(const string& inputString) {
    if (inputString.find("files") != string::npos) {
        printf("Switching to 'files' input mode.\n");
        return FILES;
    } else if (inputString.find("continents") != string::npos) {
        printf("Switching to 'continents' input mode.\n");
        return CONTINENTS;
    } else if (inputString.find("countries") != string::npos) {
        printf("Switching to 'territories' input mode.\n");
        return TERRITORIES;
    } else if (inputString.find("borders") != string::npos) {
        printf("Switching to 'borders' input mode.\n");
        return BORDERS;
    }
}

// Split the line into each relevant token of information
vector<string> MapLoader::getTokens(const string& inputString) {
    vector<string> tokens;
    char delimiter = ' ';

    char start = inputString.find_first_not_of(delimiter);
    char end;

    while (start != string::npos) {
        end = inputString.find(delimiter, start);
        tokens.push_back(inputString.substr(start, end - start));
        start = inputString.find_first_not_of(delimiter, end);
    }

    return tokens;
}

int mapTest() {
    vector<int> cow;
    cow.push_back(2);
    cow.push_back(3);
    cow.push_back(4);
    Territory *cow2 = new Territory(0, 1, "Alaska");
    Territory *cow3 = new Territory(1, 2, "Ontario");
    Territory *cow4 = new Territory(2, 1, "Eastern United States");
    Territory *cow5 = new Territory(3, 0, "Western United States");
  //  Territory *cow5 = new Territory(*cow4);
    //cow4->setId(5);
  //  cout << *cow5->getId() << endl;

    Continent *continent1 = new Continent(0, "North America", 5);
    Continent *continent2 = new Continent(1, "South America", 2);
    Continent *continent3 = new Continent(2, "Europe", 5);
    // Map *map = new Map(5, 5);
    vector<Continent *> cont;
    cont.push_back(continent1);
    cont.push_back(continent2);
    cont.push_back(continent3);


    vector<Territory *> terr;
    terr.push_back(cow2);
    terr.push_back(cow3);
    terr.push_back(cow4);
    terr.push_back(cow5);


    Map *map = new Map(1, "World", cont, terr);
    // cout << *map->getContinents()->at(1)->getContinentName() << endl;

    map->addTerritoryEdge(cow2, cow3);
    map->addTerritoryEdge(cow3, cow4);
    map->addTerritoryEdge(cow4, cow5);
    // map->addTerritoryEdge(cow4, cow5);
    map->addContinentEdge(continent2, continent3);
    map->addContinentEdge(continent1, continent3);
    map->isContinentConnected(continent2, continent3) ? cout << "Yarg" << endl : cout << "Not1" << endl;
   // map->isConnectedGraph() ? cout << "Yargt" << endl : cout << "Not" << endl;
    map->isConnectedSubgraph() ? cout << "Yargsz" << endl : cout << "Norr" << endl;
    map->oneContinentPerTerritory() ? cout << "good" << endl : cout << "bad" << endl;
   // map->validate() ? cout << "Yarg" << endl : cout << "Not" << endl;

    cout << endl;

    cout << "cowwwwwwww" << endl;
  //  cout << *map->getId() << endl;
    int id = 5;
    map->setId(&id);
    Territory *cow6 = new Territory(4, 1, "Alaska");
    terr.pop_back();
    terr.push_back(cow6);
    map->setTerritories(&terr);
   //cout << *map->getTerritories()->at(0) << endl;
    string name = "cow76";
    map->setName(&name);
    cout << *map->getId() << endl;
    cout << *map->getName() << endl;
    cout << *map << endl;
    Map *map2 = new Map(*map);
    int newid = 6;
    map->setId(&newid);
    terr.pop_back();
    map->setTerritories(&terr);
   //Map *map3 = new Map(*map2);
    //map2 = new Map(*map);

    cout << *map << endl;
    cout << *map2 << endl;

    cout << "cowwwwwwww" << endl;
    //copy constructor test
//    Map *test = new Map(*map);
//    test->printTerritoryMap();
//    cout << *test->getId() << endl;

//    Territory *test = new Territory(*cow2);
//    cout << test->getBorders()->at(1) << endl;

//Continent *test = new Continent(*continent1);
//    cout << *test->getId() << endl;
//    cout << *test->getContinentName() << endl;
//    cout << *test->getValue() << endl;

    // map->addTerritoryEdge(cow2, cow3);

//   map->addTerritoryEdge(cow2, cow4);
//   map->addTerritoryEdge(cow3, cow4);
    // map->addContinentEdge(continent1, continent2);


    // Map *copy = new Map(*map);
    //   cout << copy->getTerritoryMatrix()->size() << endl;
    //list<Territory *> test4 = *map->getTerritoryMatrix();;
    // cout << test4.size() << endl;
//[*u->getId()].push_back(v);

    // map->addEdge(1, 2);
  //  map->printTerritoryMap();
    //map->isTerritoryConnected(cow3, cow4) ? cout << "Yes" : cout << "No";

//   map->addContinentEdge(continent1, continent2);
    //  map->addContinentEdge(continent1, continent3);
    // map->isContinentConnected(new Continent(1, "North America", 5), new Continent(2, "South America", 2)) ? cout << "Yes" : cout << "No";
  //  map->printContinentMap();

    //ostream print tests
//    cout << *cow2 << endl;
//    cout << *continent1 << endl;
//    cout << *map << endl;
}

