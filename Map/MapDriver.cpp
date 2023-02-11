#include "MapDriver.h"

int mapDriver() {
    printf("Beginning map setup...\n");
    map<int, Map *> maps;

    printf("Initializing MapLoader...\n");
    MapLoader* myMapLoader = new MapLoader();

    // Select files to read prompt
    int mapCounter = 0;
    while (true) {
        printf("Please enter the (absolute) path to a map file (e to exit): ");

        string filePath;
        cin >> filePath;

        // Check if user wants to exit
        if (equal(filePath.begin(), filePath.end(), "e")) {
            printf("Exiting map selector...\n");
            break;
        }

        // Check if file exists
        ifstream file(filePath);
        if (file.fail()) {
            printf("File \"%s\" does not exist.\n", filePath.c_str());
            continue;
        }

        printf("Reading %s...\n", filePath.c_str());
        myMapLoader->setPath(&filePath);

        Map loadedMap = myMapLoader->load(mapCounter);

        printf("Validating loaded map...\n");
        if (loadedMap.validate()) {
            maps[mapCounter] = new Map(loadedMap);
            printf("Saved \"%s\" with id %d.\n", loadedMap.getName()->c_str(), mapCounter++);
        } else {
            printf("Could xnot validate map. Discarding...\n");
        }
    }

    Territory* tesTerritory = new Territory(*maps[0]->getTerritories()->at(0));
    cout << tesTerritory << endl;
    cout << *maps[0]->getTerritories()->at(0) << endl;

    cout << "Making change to tesTerritory..." << endl;

    tesTerritory->setBorders(new vector<int>());

    cout << tesTerritory << endl;
    cout << *maps[0]->getTerritories()->at(0) << endl;

    printf("Deleting MapLoader...\n");
    delete myMapLoader;

    printf("Map selection complete.\n");  // When merging with the rest, will return map
    return 0;
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

