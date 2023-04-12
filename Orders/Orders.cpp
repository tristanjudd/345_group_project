#include "Orders.h"
#include "../Player/Player.h"
#include "../GameEngine/GameEngine.h"


//Order class
Order::Order(LogObserver *observer) : Subject(observer) {
    m_playerPtr = NULL; //player issuing the order
    m_descriptionPtr = new string("This is an Order."); //Description of the Order
    m_effectPtr = new string(""); //Effect of the Order after being executed
}

Order::Order(Player *_issuer, LogObserver *observer) : Subject(observer) {
    m_playerPtr = _issuer;
    m_descriptionPtr = new string("This is an Order.");
    m_effectPtr = new string("");
}

//copy constructor
Order::Order(const Order &o) {
    m_playerPtr = o.getPlayer();
    m_descriptionPtr = new string(o.getDesc());
    m_effectPtr = new string(o.getEffect());
}

Order::~Order() {
    delete m_descriptionPtr;
    delete m_effectPtr;
}

//GETTER AND SETTER ORDER
string Order::getDesc() const {
    if (m_descriptionPtr != NULL) {
        return *m_descriptionPtr;
    }
    return "null";
}

void Order::setDesc(string _desc) {
    *m_descriptionPtr = _desc;
}

string Order::getEffect() const {
    if (m_effectPtr != NULL) {
        return *m_effectPtr;
    }
    return "null";
}

void Order::setEffect(string _execMessage) {
    *m_effectPtr = _execMessage;
}

Player *Order::getPlayer() const {
    return m_playerPtr;
}

void Order::setPlayer(Player _player) {
    *m_playerPtr = _player;
}

//stream insertion operator
std::ostream &operator<<(std::ostream &OUT, const Order &theOrder) {
    OUT << theOrder.getDesc() << endl;

    //outputs effect if the order was executed
    if (!(theOrder.getEffect() == "") && !(theOrder.getEffect() == "invalid")) {
        OUT << "Effect: " << theOrder.getEffect();
    }

    return OUT;
}

//assignment operator
void Order::operator=(Order const &obj) {
    m_playerPtr = obj.m_playerPtr;
    m_descriptionPtr = obj.m_descriptionPtr;
    m_effectPtr = obj.m_effectPtr;
}

void Order::stringToLog() {

    //creating file string
    string filename = "../Log/gamelog.txt";
    ofstream outputFile;

    //checking if file exists
    ifstream exists(filename);

    if (exists.bad()) {
        outputFile.open(filename);
    }

    // Append data to the file
    outputFile.open(filename, std::ios_base::app);
    outputFile << "Executing Order effect " << this->getEffect() << endl;
    outputFile.close();

}

//deploy class
Deploy::Deploy(LogObserver *observer) : Order(observer) {
    setDesc("This is a Deploy order");
}

Deploy::Deploy(Player *_issuer, int _nbArmies, Territory *_target, LogObserver *observer) : Order(_issuer, observer) {

    string desc = "Deploy order: Player " + to_string(*(_issuer->getId())) + "  deploys " + to_string(_nbArmies) +
                  " armies to " + (*(_target->getTerritoryName()));
    setDesc(desc);

    nbArmies = new int(_nbArmies);
    target = _target;
}

Deploy::Deploy(const Deploy &_o) : Order(_o) {
    //copy nbArmies and target
    nbArmies = new int(_o.getNbArmies());
    target = _o.getTarget();

}

//GETTER AND SETTER DEPLOY
int Deploy::getNbArmies() const {
    return *nbArmies;
}

void Deploy::setNbArmies(int _nbArmies) {
    *nbArmies = _nbArmies;
}

Territory *Deploy::getTarget() const {
    return target;
}

void Deploy::setTarget(Territory _target) {
    *target = _target;
}

Deploy::~Deploy() {
    delete nbArmies;
    nbArmies = nullptr;
}

//check if territory belongs to player
bool Deploy::validate() {

    //check if playerID and target ownerID are the same
    if ((*(target->getOwner())->getId()) != (*(getPlayer()->getId()))) {
        cout << "DEBUG: Deploy not valid, target doesn't belong to player" << endl;
        return false;
    }

    return true;
}

//prints Order type + add exec message 
//have to change when Orders are defined
bool Deploy::execute() {
    bool valid = validate();

    if (valid) {
        cout << "DEBUG: Deploy order executed" << endl;

        //calc new nb of armies and assign it to target
        int *armies = new int(*(target->getArmyCount()) + *nbArmies);
        delete target->getArmyCount(); //delete old value
        target->setArmyCount(armies);

        //create exec effect
        string execEffect = *(target->getTerritoryName()) + " now has " + to_string(*armies) + " armies";
        setEffect(execEffect);
        return true;
    } else {
        cout << "DEBUG: Deploy order not executed" << endl;
        return false;
    }

    Notify(this);
}

//assign op
void Deploy::operator=(Deploy const &obj) {
    Order::operator=(obj);
    nbArmies = obj.nbArmies;
    target = obj.target;
}

//Advance class
Advance::Advance(LogObserver *observer) : Order(observer) {
    setDesc("This is an Advance order");
}

Advance::Advance(Player *_issuer, int _nbArmies, Territory *_source, Territory *_target, LogObserver *observer) : Order(
        _issuer, observer) {
    string desc = "Advance order: Player" + to_string(*(_issuer->getId())) + " Advances " + to_string(_nbArmies) +
                  " armies from " + (*(_source->getTerritoryName())) + " to " + (*(_target->getTerritoryName()));
    setDesc(desc);

    nbArmies = new int(_nbArmies);
    source = _source;
    target = _target;
}

Advance::Advance(const Advance &_o) : Order(_o) {
    nbArmies = new int(_o.getNbArmies());
    source = _o.getSource();
    target = _o.getTarget();
}

Advance::~Advance() {
    delete nbArmies;
    nbArmies = nullptr;
}

//GETTER AND SETTER ADVANCE
int Advance::getNbArmies() const {
    return *nbArmies;
}

void Advance::setNbArmies(int _nbArmies) {
    *nbArmies = _nbArmies;
}

Territory *Advance::getSource() const {
    return source;
}

void Advance::setSource(Territory _source) {
    *source = _source;
}

Territory *Advance::getTarget() const {
    return target;
}

void Advance::setTarget(Territory _target) {
    *target = _target;
}


//check if source belongs to player
//check if source and target are adjacent
//check if territory has enough armies
bool Advance::validate() {

    //check if territory has enough troops
    if (*(source->getArmyCount()) < *nbArmies) {
        cout << "DEBUG: Advance not valid, source doesn't have enough troops" << endl;
        return false;
    }

    //check owner of source
    if ((*(source->getOwner())->getId()) != (*(getPlayer()->getId()))) {
        cout << "DEBUG: Advance not valid, player doesn't own the source" << endl;
        return false;
    }

    //check if players at peace
    string peaceDuo1 = to_string(*(getPlayer()->getId())) + "/" + to_string(*(target->getOwner()->getId()));
    string peaceDuo2 = to_string(*(target->getOwner()->getId())) + "/" + to_string(*(getPlayer()->getId()));

    if (GameEngine::peaceStatus->count(peaceDuo1) > 0 || GameEngine::peaceStatus->count(peaceDuo2) > 0) {
        cout << "DEBUG: Advance not valid, players at peace" << endl;
        return false;
    }

    //check if source and target are adjacent
    vector<int> *vec = source->getBorders();

    if (find(vec->begin(), vec->end(), (*(target->getId()))) != vec->end()) {
        return true;
    }

    cout << "DEBUG: Advance not valid, source and target are not adjacent" << endl;
    return false;
}

//move army to ally territtory or battle for a target territory
bool Advance::execute() {
    bool valid = validate();

    if (valid) {
        cout << "DEBUG: Advance order executed" << endl;

        //create exec effect string
        string execEffect = "";

        //if target and source are owned by same player
        if (*(source->getOwner()->getId()) == *(target->getOwner()->getId())) {
            //calc new nb of armies
            int *leave = new int(*(source->getArmyCount()) - *nbArmies);
            int *arrive = new int(*(target->getArmyCount()) + *nbArmies);

            //assign new nb of armies
            delete source->getArmyCount();
            delete target->getArmyCount();

            source->setArmyCount(leave);
            target->setArmyCount(arrive);
            execEffect = *(target->getTerritoryName()) + " now has " + to_string(*arrive) + " armies";
        }


            // battle between 2 armies
        else {

            //check if target is a neutral strategy
            Neutral *neutralCheck = dynamic_cast<Neutral *>(target->getOwner()->getStrategy());

            if (neutralCheck != nullptr) {
                //change target player strategy to aggressive
                delete target->getOwner()->getStrategy();
                PlayerStrategy *aggressive = new Aggressive(target->getOwner());
                target->getOwner()->setStrategy(aggressive);
                cout << "DEBUG: Neutral player strategy changed to aggressive" << endl;
            }

            int attackingArmies = *nbArmies;
            int defendingArmies = *(target->getArmyCount());

            while (attackingArmies != 0 && defendingArmies != 0) {
                //attack kills and defending unit
                if (rand() % 100 < 60) {
                    defendingArmies--;
                }

                //defender still has a unit and kill an attacking unit
                if (defendingArmies != 0 && rand() % 100 < 70) {
                    attackingArmies--;
                }
            }

            //check winner
            if (defendingArmies == 0) //attack won
            {
                //remove army from source
                int *leave = new int(*(source->getArmyCount()) - *nbArmies);
                delete source->getArmyCount();
                source->setArmyCount(leave);

                //move army and change owner of target
                delete target->getArmyCount();
                target->setArmyCount(new int(attackingArmies)); //change army count

                //remove territory from defender
                Player *otherPlayer = target->getOwner();

                vector<Territory *> *newTerritories = otherPlayer->getPlayerTerritories();
                auto it = std::find(newTerritories->begin(), newTerritories->end(), target);
                if (it != newTerritories->end()) {
                    newTerritories->erase(it);
                }

                otherPlayer->setPlayerTerritories(newTerritories);

                target->setOwner(getPlayer()); //change ownership

                //add territory to attacker
                vector<Territory *> *newTerritories2 = getPlayer()->getPlayerTerritories();
                newTerritories2->push_back(target);
                getPlayer()->setPlayerTerritories(newTerritories2);

                //Give card to player
                int ID = *getPlayer()->getId();
                if (std::find(GameEngine::conqStatus->begin(), GameEngine::conqStatus->end(), ID) ==
                    GameEngine::conqStatus->end()) //ID not in vector, first time conquering this round
                {
                    GameEngine::conqStatus->push_back(ID);
                    Card *theCard = new Card();
                    getPlayer()->getHand()->insert(theCard); //ading card to Players hand
                    GameEngine::conqStatus->push_back(ID);

                    cout << "DEBUG: Card Given" << endl;

                }

                execEffect =
                        "Player " + to_string(*(getPlayer()->getId())) + " conquered " + *(target->getTerritoryName());
            } else //defender won
            {
                //remove army from source
                int *leave = new int(*(source->getArmyCount()) - *nbArmies);
                source->setArmyCount(leave);

                //remove defender that died
                target->setArmyCount(new int(defendingArmies));

                execEffect = ("Defender won the battle");
            }


        }

        //set effect
        setEffect(execEffect);
        return true;
    } else {
        cout << "DEBUG: Advance order not executed" << endl;
        return false;
    }

    Notify(this);
}

//assign op
void Advance::operator=(Advance const &obj) {
    Order::operator=(obj);
    nbArmies = obj.nbArmies;
    source = obj.source;
    target = obj.target;
}

//bomb class
Bomb::Bomb(LogObserver *observer) : Order(observer) {
    setDesc("This is a Bomb order");
}

Bomb::Bomb(Player *_issuer, Territory *_target, LogObserver *observer) : Order(_issuer, observer) {

    string desc = "Bomb order: Player " + to_string(*(_issuer->getId())) + " bombs " + (*(_target->getTerritoryName()));
    setDesc(desc);
    target = _target;
}

Bomb::Bomb(const Bomb &_o) : Order(_o) {
    //copy target
    target = _o.getTarget();
}

Bomb::~Bomb() {

}

//GETTE AND SETTER
Territory *Bomb::getTarget() const {
    return target;
}

void Bomb::setTarget(Territory _target) {
    *target = _target;
}

//check owner of target
// check if adjacent
bool Bomb::validate() {

    //check playerID and targetID are the same
    if ((*(target->getOwner())->getId()) == (*(getPlayer()->getId()))) {
        cout << "DEBUG: Bomb not valid, player targets himself" << endl;
        return false;
    }

    //check if players at peace
    string peaceDuo1 = to_string(*(getPlayer()->getId())) + "/" + to_string(*(target->getOwner()->getId()));
    string peaceDuo2 = to_string(*(target->getOwner()->getId())) + "/" + to_string(*(getPlayer()->getId()));


    if (GameEngine::peaceStatus->count(peaceDuo1) > 0 || GameEngine::peaceStatus->count(peaceDuo2) > 0) {
        cout << "DEBUG: Bomb not valid, players at peace" << endl;
        return false;
    }

    //check if adjacent to one of the player's territories
    bool adjacent = false;

    for (int i = 0; i < getPlayer()->getPlayerTerritories()->size(); i++) {
        vector<int> *bvec = (*(getPlayer()->getPlayerTerritories()))[i]->getBorders();

        if (find(bvec->begin(), bvec->end(), (*(target->getId()))) != bvec->end()) {
            adjacent = true;
            break;
        }
    }

    if (!adjacent) {
        cout << "DEBUG: Bomb not valid, target is not adjacent" << endl;
        return false;
    }

    return true;
}

//Removes half of the armies
bool Bomb::execute() {
    bool valid = validate();

    if (valid) {
        cout << "DEBUG: Bomb order executed" << endl;

        //check if target is a neutral strategy
        Neutral *neutralCheck = dynamic_cast<Neutral *>(target->getOwner()->getStrategy());

        if (neutralCheck != nullptr) {
            //change target player strategy to aggressive
            delete target->getOwner()->getStrategy();
            target->getOwner()->setStrategy(new Aggressive(target->getOwner()));
            cout << "DEBUG: Neutral player strategy changed to aggressive" << endl;
        }

        //calc new nb of armies
        int *survive = new int((*(target->getArmyCount())) / 2);
        delete target->getArmyCount();
        target->setArmyCount(survive);

        string execEffect = *(target->getTerritoryName()) + " now has " + to_string(*survive) + " armies";
        setEffect(execEffect);
        return true;
    } else {
        cout << "DEBUG: Bomb order not executed" << endl;
        return false;
    }

    Notify(this);
}

//assign op
void Bomb::operator=(Bomb const &obj) {
    Order::operator=(obj);
    target = obj.target;
}

//blockade class
Blockade::Blockade(LogObserver *observer) : Order(observer) {
    setDesc("This is a Blockade order");
}

Blockade::Blockade(Player *_issuer, Territory *_target, LogObserver *observer) : Order(_issuer, observer) {
    string desc = "Blockade order: Player " + to_string(*(_issuer->getId())) + " blockades " +
                  (*(_target->getTerritoryName()));
    setDesc(desc);
    target = _target;
}

Blockade::Blockade(const Blockade &o) : Order(o) {
    //copy target
    target = o.getTarget();
}

Blockade::~Blockade() {

}

//GETTER AND SETTER BLOCKADE
Territory *Blockade::getTarget() const {
    return target;
}

void Blockade::setTarget(Territory _target) {
    *target = _target;
}

//check owner of target
bool Blockade::validate() {

    //check if Player owns target
    if ((*(target->getOwner())->getId()) != (*(getPlayer()->getId()))) {
        cout << "DEBUG: Blockade not valid, player doesn't own the target" << endl;
        return false;
    }

    return true;
}

//prints Order type + add exec message 
//have to change when Orders are defined
bool Blockade::execute() {

    //GameEngine::neutral->getId(); anhtu

    bool valid = validate();

    if (valid) {
        cout << "DEBUG: Blockade order executed" << endl;

        //double nb of armies
        int *doubled = new int((*(target->getArmyCount())) * 2);
        delete target->getArmyCount();
        target->setArmyCount(doubled);

        string execEffect = *(target->getTerritoryName()) + " now has " + to_string(*doubled) +
                            " armies and is owned by Neutral player";
        setEffect(execEffect);

        //REMOVE territory from player
        vector<Territory *> *newTerritories = getPlayer()->getPlayerTerritories();


        auto it = std::find(newTerritories->begin(), newTerritories->end(), target);
        if (it != newTerritories->end()) {
            newTerritories->erase(it);
        }
        getPlayer()->setPlayerTerritories(newTerritories);

        //GIVE TERRITORY TO NEUTRAL PLAYER
        GameEngine::neutral->getPlayerTerritories()->push_back(target);
        target->setOwner(GameEngine::neutral);

        return true;
    } else {
        cout << "DEBUG: Blockade order not executed" << endl;
        return false;
    }

    Notify(this);
}

//assign op
void Blockade::operator=(Blockade const &obj) {
    Order::operator=(obj);
    target = obj.target;
}

//airlift class
Airlift::Airlift(LogObserver *observer) : Order(observer) {
    setDesc("This is an Airlift order");
}

Airlift::Airlift(Player *_issuer, int _nbArmies, Territory *_source, Territory *_target, LogObserver *observer) : Order(
        _issuer, observer) {
    string desc = "Airlift order: Player " + to_string(*(_issuer->getId())) + " airlifts " + to_string(_nbArmies) +
                  " armies from " + (*(_source->getTerritoryName())) + " to " + (*(_target->getTerritoryName()));
    setDesc(desc);
    nbArmies = new int(_nbArmies);
    source = _source;
    target = _target;
}

Airlift::Airlift(const Airlift &_o) : Order(_o) {
    nbArmies = new int(_o.getNbArmies());
    source = _o.getSource();
    target = _o.getTarget();
}

Airlift::~Airlift() {
    delete nbArmies;
    nbArmies = nullptr;
}

//GETTER AND SETTER AIRLIFT
int Airlift::getNbArmies() const {
    return *nbArmies;
}

void Airlift::setNbArmies(int _nbArmies) {
    *nbArmies = _nbArmies;
}

Territory *Airlift::getSource() const {
    return source;
}

void Airlift::setSource(Territory _source) {
    *source = _source;
}

Territory *Airlift::getTarget() const {
    return target;
}

void Airlift::setTarget(Territory _target) {
    *target = _target;
}

//check if player owns source and target
bool Airlift::validate() {

    //check if playerID and targetID are the same
    if ((*(target->getOwner())->getId()) != (*(getPlayer()->getId()))) {
        cout << "DEBUG: Airlift not valid, player doesn't own the target" << endl;
        return false;
    }

    //check owner of source
    if ((*(source->getOwner())->getId()) != (*(getPlayer()->getId()))) {
        cout << "DEBUG: Airlift not valid, player doesn't own the source" << endl;
        return false;
    }

    return true;
}

//moves player to another territory
bool Airlift::execute() {
    bool valid = validate();

    if (valid) {
        cout << "DEBUG: Airlift order executed" << endl;

        //calc new nb of armies
        int *fly = new int(*(source->getArmyCount()) - *nbArmies);
        int *land = new int(*(target->getArmyCount()) + *nbArmies);

        //set new nb of armies
        delete source->getArmyCount();
        delete target->getArmyCount();
        source->setArmyCount(fly);
        target->setArmyCount(land);

        //create exec effect string
        string execEffect = *(target->getTerritoryName()) + " now has " + to_string(*land) + " armies";
        setEffect(execEffect);
        return true;
    } else {
        cout << "DEBUG: Airlift order not executed" << endl;
        return false;
    }

    Notify(this);
}

//assign op
void Airlift::operator=(Airlift const &obj) {
    Order::operator=(obj);
    nbArmies = obj.nbArmies;
    source = obj.source;
    target = obj.target;
}

//negotiate class
Negotiate::Negotiate(LogObserver *observer) : Order(observer) {
    setDesc("This is a Negotiate order");
}

Negotiate::Negotiate(Player *_issuer, int _victimID, LogObserver *observer) : Order(_issuer, observer) {
    string desc = "Negotiate order: Player " + to_string(*(_issuer->getId())) + " negotiates with Player " +
                  to_string(_victimID);
    setDesc(desc);
    victim = new int(_victimID);

}

Negotiate::Negotiate(const Negotiate &_o) : Order(_o) {
    victim = new int(_o.getVictim());
}

Negotiate::~Negotiate() {

}

//GETTER AND SETTER NEGOTIATE
int Negotiate::getVictim() const {
    return *victim;
}

void Negotiate::setVictim(int _victimID) {
    *victim = _victimID;
}


//check if player is negotating with himself
bool Negotiate::validate() {

    //check if player and victim are the same player
    if (*victim == (*(getPlayer()->getId()))) {
        cout << "DEBUG: Negotiate not valid, target is same as issuer" << endl;
        return false;
    }

    return true;
}


//prints Order type + add exec message 
//have to change when Orders are defined
bool Negotiate::execute() {
    bool valid = validate();

    if (valid) {
        cout << "DEBUG: Negotiate order executed" << endl;
        string peaceDuo = to_string(*getPlayer()->getId()) + "/" + to_string(*victim); //Create a string with both IDs
        GameEngine::peaceStatus->insert(make_pair(peaceDuo, true)); //add duo to peaceStatus map

        string execEffect = "Players " + to_string(*getPlayer()->getId()) + " and " + to_string(*victim) +
                            " are at peace for the rest of the round.";
        setEffect(execEffect);
        return true;
    } else {
        cout << "DEBUG: Negotiate order not executed" << endl;
        return false;
    }

    Notify(this);
}

//assign op
void Negotiate::operator=(Negotiate const &obj) {
    Order::operator=(obj);
    victim = obj.victim;
}

//CHEAT class
Cheat::Cheat(Player *_issuer, LogObserver *observer) : Order(_issuer, observer) {
    setDesc("This is a Cheat order");
}

Cheat::Cheat(const Cheat &_o) : Order(_o) {
}

Cheat::~Cheat() {
}

bool Cheat::validate() {

    //check if player is already conqured this turn
    int ID = *getPlayer()->getId();
    if (std::find(GameEngine::conqStatus->begin(), GameEngine::conqStatus->end(), ID) ==
        GameEngine::conqStatus->end()) {
        return true;
    }

    return false;

}

bool Cheat::execute() {
    bool valid = validate();

    if (valid) {
        cout << "DEBUG: Cheat order executed" << endl;
        string execEffect = "Player " + to_string(*getPlayer()->getId()) + " conquers all adjacent territories";
        setEffect(execEffect);
        GameEngine::conqStatus->push_back(*getPlayer()->getId());

        //create a copy of player territories
        vector<Territory *> originalTerritories = *getPlayer()->getPlayerTerritories();

        //conquer all territories adjacent to player's originalterritories and add them to player's territory list
        for (int i = 0; i < originalTerritories.size(); i++) {
            for (int j = 0; j < originalTerritories.at(i)->getBorderedTerritories()->size(); j++) {
                //check if territory is already owned by the player
                if (originalTerritories.at(i)->getBorderedTerritories()->at(j)->getOwner()->getId() !=
                    getPlayer()->getId()) {
                    //remove territory from other player's territory list
                    Player *otherPlayer = originalTerritories.at(i)->getBorderedTerritories()->at(j)->getOwner();

                    vector<Territory *> *newTerritories = otherPlayer->getPlayerTerritories();
                    auto it = std::find(newTerritories->begin(), newTerritories->end(),
                                        originalTerritories.at(i)->getBorderedTerritories()->at(j));
                    if (it != newTerritories->end()) {
                        newTerritories->erase(it);
                    }

                    //add territory to player's territory list
                    getPlayer()->getPlayerTerritories()->push_back(
                            originalTerritories.at(i)->getBorderedTerritories()->at(j));

                    //set new owner
                    originalTerritories.at(i)->getBorderedTerritories()->at(j)->setOwner(getPlayer());
                }
            }
        }


        Notify(this);
        return true;
    } else {
        cout << "DEBUG: Cheat order not executed" << endl;
        return false;
    }

}

void Cheat::operator=(Cheat const &obj) {
    Order::operator=(obj);
}


//OrderList class
OrderList::OrderList(LogObserver *observer) : Subject(observer) {
    m_theListPtr = new std::vector<Order *>;
}

OrderList::OrderList(const OrderList &o, LogObserver *observer) {
    m_theListPtr = new vector<Order *>(*(o.getList()));
}


OrderList::~OrderList() {
    for (Order *obj: *m_theListPtr) {
        delete obj;
    }
    delete m_theListPtr;
}


vector<Order *> *OrderList::getList() const {
    return m_theListPtr;
}

bool OrderList::Add(Order *_obj) {
    m_theListPtr->push_back(_obj);
    Notify(this);
    return true;
}

bool OrderList::remove(int _i) {
    if (m_theListPtr->size() <= _i || _i < 0) {
        cout << "DEBUG: out of index" << endl;
        return false;
    } else {
        m_theListPtr->erase(m_theListPtr->begin() + _i);
        return true;
    }
}

bool OrderList::move(int _objIndex, int _newIndex) {
    if (m_theListPtr->size() <= _objIndex || _objIndex < 0 || m_theListPtr->size() <= _newIndex || _newIndex < 0) {
        cout << "debug: out of index" << endl;
        return false;
    } else {
        Order *temp = m_theListPtr->at(_objIndex);
        m_theListPtr->erase(m_theListPtr->begin() + _objIndex);
        m_theListPtr->insert(m_theListPtr->begin() + _newIndex, temp);
        return true;
    }

}

std::ostream &operator<<(std::ostream &OUT, const OrderList &theOrderList) {
    for (Order *obj: *(theOrderList.getList())) {
        OUT << *obj;
    }

    return OUT;
}

void OrderList::operator=(OrderList const &_other) {
    m_theListPtr = _other.m_theListPtr;
}

void OrderList::stringToLog() {

    //creating file string
    string filename = "../Log/gamelog.txt";
    ofstream outputFile;

    //checking if file exists
    ifstream exists(filename);

    if (exists.bad()) {
        outputFile.open(filename);
    }

    // Append data to the file
    outputFile.open(filename, std::ios_base::app);
    outputFile << "Adding order: " << this->getList()->back()->getDesc() << endl;
    outputFile.close();
}



