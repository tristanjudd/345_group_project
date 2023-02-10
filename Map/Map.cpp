#include "Map.h"

// Territory class
// default constructor
Territory::Territory() {
    id = new int(0);
    continentId = new int(-1);
    armyCount = new int(0);
    territoryName = new string("");
    borders = new vector<int>();
    //owner = new Player();
    cout << "Territory default constructor called" << endl;
}

// constructor for loader
Territory::Territory(int inId, int inContinentId, string inTerritoryName) {
    id = new int(inId);
    continentId = new int(inContinentId);
    armyCount = new int(0);
    territoryName = new string(inTerritoryName);
    borders = new vector<int>();
    // owner = new Player(*inOwner);
    cout << "Territory constructor called" << endl;
}

// copy constructor
Territory::Territory(const Territory &copy) {
    id = new int(*copy.id);
    continentId = new int(*copy.continentId);
    armyCount = new int(*copy.armyCount);
    territoryName = new string(*copy.territoryName);
    borders = new vector<int>(*copy.borders);
    cout << "Territory copy constructor called" << endl;
}

// assignment operator
Territory &Territory::operator=(const Territory &t) {
    if (this != &t) {
        id = new int(*t.id);
        continentId = new int(*t.continentId);
        armyCount = new int(*t.armyCount);
        territoryName = new string(*t.territoryName);
        borders = new vector<int>(*t.borders);
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
Territory::~Territory() {
    delete id;
    delete continentId;
    delete armyCount;
    delete territoryName;
    delete borders;
    // delete owner;
    cout << "Territory destructor called" << endl;
}

// getters and setters
void Territory::setId(int inId) {
    id = &inId;
}

int *Territory::getId() {
    return id;
}

void Territory::setContinentId(int inContinentId) {
    continentId = &inContinentId;
}

int *Territory::getContinentId() {
    return continentId;
}

void Territory::setArmyCount(int inArmyCount) {
    armyCount = &inArmyCount;
}

int *Territory::getArmyCount() {
    return armyCount;
}

void Territory::setTerritoryName(string inTerritoryName) {
    territoryName = &inTerritoryName;
}

string *Territory::getTerritoryName() {
    return territoryName;
}

void Territory::setBorders(vector<int> inBorders) {
    borders = new vector<int>(inBorders);
}

vector<int> *Territory::getBorders() {
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
        id = new int(*c.id);
        continentName = new string(*c.continentName);
        value = new int(*c.value);
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
Continent::~Continent() {
    delete id;
    delete continentName;
    delete value;
    cout << "Continent destructor called" << endl;
}

// getters and setters
void Continent::setId(int inId) {
    id = &inId;
}

int *Continent::getId() {
    return id;
}

void Continent::setContinentName(string inContinentName) {
    continentName = &inContinentName;
}

string *Continent::getContinentName() {
    return continentName;
}

void Continent::setValue(int inValue) {
    value = &inValue;
}

int *Continent::getValue() {
    return value;
}

// Map class
// default constructor
Map::Map() {
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
    cout << "Map default constructor called" << endl;
}

// constructor for loader
Map::Map(int inId, string inName, vector<Continent *> inContinents, vector<Territory *> inTerritories) {
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
    cout << "Map constructor called" << endl;
}

// copy constructor
Map::Map(const Map &copy) {
    id = new int(*copy.id);
    name = new string(*copy.name);
    territories = new vector<Territory *>(*copy.territories);
    continents = new vector<Continent *>(*copy.continents);
    territoryMatrix = new bool *[territories->size()];
    continentMatrix = new bool *[continents->size()];
    territoryMatrix = copy.territoryMatrix;
    continentMatrix = copy.continentMatrix;
    cout << "Map copy constructor called" << endl;
}

// assignment operator
Map &Map::operator=(const Map &m) {
    if (this != &m) {
        id = new int(*m.id);
        name = new string(*m.name);
        territories = new vector<Territory *>(*m.territories);
        continents = new vector<Continent *>(*m.continents);
        territoryMatrix = new bool *[territories->size()];
        continentMatrix = new bool *[continents->size()];
        territoryMatrix = m.territoryMatrix;
        continentMatrix = m.continentMatrix;
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
    for (int i = 0; i < territories->size(); i++) {
        delete[] territoryMatrix[i];
    }
    delete[] territoryMatrix;
    for (int i = 0; i < continents->size(); i++) {
        delete[] continentMatrix[i];
    }
    delete[] continentMatrix;
    delete id;
    delete name;
    delete territories;
    delete continents;
    cout << "Map destructor called" << endl;
}

// getters and setters
void Map::setId(int inId) {
    id = &inId;
}

int *Map::getId() {
    return id;
}

void Map::setName(string inName) {
    name = &inName;
}

string *Map::getName() {
    return name;
}

void Map::setContinents(vector<Continent *> inContinents) {
    continents = &inContinents;
}

vector<Continent *> *Map::getContinents() {
    return continents;
}

void Map::setTerritories(vector<Territory *> inTerritories) {
    territories = &inTerritories;
}

vector<Territory *> *Map::getTerritories() {
    return territories;
}

// link 2 territories
void Map::addTerritoryEdge(Territory *t1, Territory *t2) {
    if ((*t1->getId() - 1) != (*t2->getId() - 1)) {
        territoryMatrix[*t1->getId() - 1][*t2->getId() - 1] = true;
    }
}

// check if 2 territories are connected
bool Map::isTerritoryConnected(Territory *t1, Territory *t2) {
    return territoryMatrix[*t1->getId() - 1][*t2->getId() - 1];
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
    if ((*c1->getId() - 1) != (*c2->getId() - 1)) {
        continentMatrix[*c1->getId() - 1][*c2->getId() - 1] = true;
    }
}

// check if 2 continents are connected
bool Map::isContinentConnected(Continent *c1, Continent *c2) {
    return continentMatrix[*c1->getId() - 1][*c2->getId() - 1];
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
            if (territoryMatrix[*territories->at(i)->getId() - 1][j]) {
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
            if (continentMatrix[*continents->at(i)->getId() - 1][j]) {
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
MapLoader::MapLoader() : path(nullptr) {}

//getters/setters
string MapLoader::getPath() {
    return *path;
}
void MapLoader::setPath(string *inputPath) {
    path = inputPath;
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

                territories->at(stoi(tokens[0])-1)->setBorders(*borders);
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
