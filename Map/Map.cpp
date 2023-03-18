#include "Map.h"
#include "../Player/Player.h"

// Territory class
// default constructor
Territory::Territory() {
    id = new int(0);
    continentId = new int(-1);
    armyCount = new int(0);
    territoryName = new string("");
    borders = new vector<int>();
    owner = nullptr;
    cout << "Territory default constructor called" << endl;
}

// constructor for loader
Territory::Territory(int inId, int inContinentId, string inTerritoryName) {
    id = new int(inId);
    continentId = new int(inContinentId);
    armyCount = new int(0);
    territoryName = new string(inTerritoryName);
    borders = new vector<int>();
    owner = nullptr;
    cout << "Territory constructor called" << endl;
}

// copy constructor
Territory::Territory(const Territory &copy) {
    id = new int(*copy.id);
    continentId = new int(*copy.continentId);
    armyCount = new int(*copy.armyCount);
    territoryName = new string(*copy.territoryName);
    borders = new vector<int>(*copy.borders);
    owner = copy.owner;
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
        owner = t.owner;
    }
    return *this;
}

// stream insertion operator
ostream &operator<<(ostream &out, const Territory &c) {
    out << "Territory ID: " << *c.id << endl;
    out << "Continent ID: " << *c.continentId << endl;
    out << "Army Count: " << *c.armyCount << endl;
    out << "Territory Name: " << *c.territoryName << endl;
    if (c.owner == nullptr) {
        out << "Territory Owner: None" << endl;
    } else {
        out << "Territory Owner: " << *c.owner << endl;
    }
    out << "Borders: ";
    for (int i = 0; i < c.borders->size(); i++) {
        out << c.borders->at(i) << " ";
    }
    out << endl;
    return out;
}

// destructor
Territory::~Territory() {
    id = nullptr;
    continentId = nullptr;
    armyCount = nullptr;
    territoryName = nullptr;
    // owner = nullptr;
    delete id;
    delete continentId;
    delete armyCount;
    delete territoryName;
    delete owner;
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

int *Territory::getContinentId() const {
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

void Territory::setOwner(Player *inOwner) {
    owner = inOwner;
}

Player *Territory::getOwner() const {
    return owner;
}

void Territory::setBorderedTerritories(Territory *inTerritory, vector<Territory *> *territories) {
    vector<Territory *> *tempTerritory = new vector<Territory *>();
    for (int i = 0; i < inTerritory->getBorders()->size(); i++) {
        tempTerritory->push_back(territories->at(inTerritory->getBorders()->at(i)));
    }
    inTerritory->borderedTerritories = tempTerritory;
    tempTerritory->clear();
    delete tempTerritory;
}

vector<Territory *> *Territory::getBorderedTerritories() const {
    return borderedTerritories;
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
Continent::~Continent() {
    cout << "Continent destructor called" << endl;
    id = nullptr;
    continentName = nullptr;
    value = nullptr;
    delete id;
    delete continentName;
    delete value;
}

// getters and setters
void Continent::setId(int *inId) {
    id = inId;
}

int *Continent::getId() const {
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

void Continent::setTerritoriesInContinent(Continent *inContinent, vector<Territory *> *inTerritoriesInContinent) {
    vector<Territory *> *tempTerritory = new vector<Territory *>();
    for (int i = 0; i < inTerritoriesInContinent->size(); i++) {
        if (*inContinent->getId() == *inTerritoriesInContinent->at(i)->getContinentId()) {
            tempTerritory->push_back(inTerritoriesInContinent->at(i));
        }
    }
    inContinent->territoriesInContinent = tempTerritory;
    tempTerritory->clear();
    delete tempTerritory;
}

vector<Territory *> *Continent::getTerritoriesInContinent() const {
    return territoriesInContinent;
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
    id = nullptr;
    name = nullptr;
    territories = nullptr;
    continents = nullptr;
    delete id;
    delete name;
    delete territories;
    delete continents;
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
    if (*terrCount == territories->size() && *terrCount != 0) { //if all territories have a connection
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
    if (*contCount == continents->size() && *contCount != 0) { //if all continents have a connection
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
    if (*terrCount == territories->size() && *contCount == continents->size() && *terrCount != 0 && *contCount != 0) {
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
    if (this != &mapLoader) {
        path = mapLoader.path;
    }
    return *this;
}

// stream insertion operator
ostream &operator<<(ostream &out, const MapLoader &mapLoader) {
    out << "MapLoader: " << *mapLoader.path;
    return out;
}

// destructor
MapLoader::~MapLoader() {
    cout << "MapLoader destructor called" << endl;
    path = nullptr;
    delete path;
}

//getters/setters
void MapLoader::setPath(string *inputPath) {
    path = inputPath;
}

string *MapLoader::getPath() const {
    return path;
}

// Reads the input file and returns a full map object
Map *MapLoader::readMap(string *filePath) {
    //  printf("Loading %s...\n", filePath->c_str());

    ifstream file(filePath->c_str());
    PARSE_MODE mode = UNSPECIFIED;

    vector<Territory *> *territories = new vector<Territory *>();
    vector<Continent *> *continents = new vector<Continent *>();
    int continentCounter = 0;

    // Iterate over each line, and create object based on parsing mode
    string line;
    vector<string> tokens;
    while (getline(file, line)) {
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
                if (stoi(tokens[0]) < territories->size()) {
                    throw std::exception();  // if the first token is bad, exit and cannot parse
                }
                printf("Parsing territory %s...\n", tokens[1].c_str());
                territories->push_back(new Territory(stoi(tokens[0]) - 1,
                                                     stoi(tokens[2]) - 1,
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
                vector<int> *borders = new vector<int>();

                for (int i = 1; i < tokens.size(); i++) {
                    borders->push_back(stoi(tokens[i]) - 1);
                }

                territories->at(stoi(tokens[0]) - 1)->setBorders(borders);
                break;
            }
        }
    }

    string *mapName = new string();
    *mapName = filePath->substr(filePath->find_last_of('/') + 1,
                                filePath->find_last_of('.') - filePath->find_last_of('/') - 1);
    Map *map = new Map(0,
                       *mapName,
                       *continents,
                       *territories);

    // Create territory and continent matrix
    for (Territory *territory: *map->getTerritories()) {
        for (int border: *territory->getBorders()) {
            // add a territory edge between each border territory
            Territory *borderTerritory = map->getTerritories()->at(border);
            map->addTerritoryEdge(territory, borderTerritory);

            // if the border territory is in a different continent than this territory, add a continent edge
            int territoryContinentId = *territory->getContinentId();
            int borderContinentId = *borderTerritory->getContinentId();
            Continent *territoryContinent = map->getContinents()->at(territoryContinentId);
            Continent *borderContinent = map->getContinents()->at(borderContinentId);
            if (borderContinentId != territoryContinentId) {
                map->addContinentEdge(territoryContinent, borderContinent);
            }
        }
    }

    for (int i = 0; i < map->getTerritories()->size(); i++) {
        Territory::setBorderedTerritories(map->getTerritories()->at(i), map->getTerritories());
    }

    for (int i = 0; i < map->getContinents()->size(); i++) {
        Continent::setTerritoriesInContinent(map->getContinents()->at(i), map->getTerritories());
    }

    printf("Closing %s...\n", filePath->c_str());
    file.close();

    return map;
}

// Switch the parsing mode based on the [flag]
PARSE_MODE MapLoader::getMode(const string &inputString) {
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
vector<string> MapLoader::getTokens(const string &inputString) {
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

bool MapLoader::loadMap(GameEngine *g, string *inputPath) {
    // printf("Beginning map setup...\n");
    // printf("Initializing MapLoader...\n");
    MapLoader *myMapLoader = new MapLoader();
    string filePath = *inputPath;

    // Check if file exists
    ifstream file(filePath);
    if (file.fail()) {
        printf("File \"%s\" does not exist.\n", filePath.c_str());
        return false;
    }

    printf("Reading %s...\n", filePath.c_str());
    myMapLoader->setPath(&filePath);

    Map *loadedMap = new Map();
    try {
        loadedMap = myMapLoader->readMap(&filePath);
        g->setMap(loadedMap);
    } catch (...) {
        printf("Could not parse map file. Discarding...\n");
    }

    printf("Deleting MapLoader...\n");
    delete myMapLoader;

    printf("Map selection complete.\n");  // When merging with the rest, will return map
    return true;
}

int mapTest() {
    vector<int> bord;
    bord.push_back(2);
    bord.push_back(3);
    bord.push_back(4);
    Territory *ter1 = new Territory(0, 1, "Alaska");
    Territory *ter2 = new Territory(1, 2, "Ontario");
    Territory *ter3 = new Territory(2, 1, "Eastern United States");
    Territory *ter4 = new Territory(3, 0, "Western United States");
    vector<Territory *> terr;
    terr.push_back(ter1);
    terr.push_back(ter2);
    terr.push_back(ter3);
    terr.push_back(ter4);

    Continent *continent1 = new Continent(0, "North America", 5);
    Continent *continent2 = new Continent(1, "South America", 2);
    Continent *continent3 = new Continent(2, "Europe", 5);
    vector<Continent *> cont;
    cont.push_back(continent1);
    cont.push_back(continent2);
    cont.push_back(continent3);

    Map *map = new Map(0, "World", cont, terr);
    map->addTerritoryEdge(ter1, ter2);
    map->addTerritoryEdge(ter2, ter1);
    map->addTerritoryEdge(ter2, ter3);
    map->addTerritoryEdge(ter3, ter2);
    map->addTerritoryEdge(ter3, ter4);
    map->addTerritoryEdge(ter4, ter3);
    map->addContinentEdge(continent2, continent3);
    map->addContinentEdge(continent3, continent2);
    map->addContinentEdge(continent1, continent3);
    map->addContinentEdge(continent3, continent1);

    map->isContinentConnected(continent2, continent3) ? cout << "Yay" << endl : cout << "Bad" << endl;
    map->isConnectedGraph() ? cout << "Yay1" << endl : cout << "Bad1" << endl;
    map->isConnectedSubgraph() ? cout << "Yay2" << endl : cout << "Bad2" << endl;
    map->oneContinentPerTerritory() ? cout << "Yay3" << endl : cout << "Bad3" << endl;
    map->validate() ? cout << "Yay4" << endl : cout << "Bad4" << endl;
    cout << endl;

    cout << "TEST" << endl;
    int id = 5;
    map->setId(&id);
    Territory *cow6 = new Territory(4, 1, "Alaska");
    terr.pop_back();
    terr.push_back(cow6);
    map->setTerritories(&terr);

    cout << *map;
    cout << "TEST" << endl << endl;
    delete map;
    delete ter1;
    delete ter2;
    delete ter3;
    delete ter4;
    delete cow6;
    delete continent1;
    delete continent2;
    delete continent3;
    return 0;
}

// Tristan: for dev purposes, delete later
void Territory::testSetBorders(vector<Territory *> *b) {
    borderedTerritories = b;
}

// Tristan: for dev purposes, delete later
void Continent::testSetTerritories(vector<Territory *> *t) {
    territoriesInContinent = t;
}