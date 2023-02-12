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
            printf("Could not validate map. Discarding...\n");
        }
    }

    printf("Deleting MapLoader...\n");
    delete myMapLoader;

    printf("Map selection complete.\n");  // When merging with the rest, will return map
    return 0;
}
