#include "Orders.h"
#include "../Player/Player.h"


//Order class
Order::Order() {
	m_playerPtr = NULL; //player issuing the order
	m_descriptionPtr = new string("This is an Order."); //Description of the Order
	m_effectPtr = new string(""); //Effect of the Order after being executed
}

Order::Order(Player* _issuer) {
	m_playerPtr = _issuer;
	m_descriptionPtr = new string("This is an Order.");
	m_effectPtr = new string("");
}

//copy constructor
Order::Order(const Order& o) {
	m_playerPtr = o.getPlayer();
	m_descriptionPtr = new string(o.getDesc());
	m_effectPtr = new string(o.getEffect());
}

Order::~Order() {
	delete m_descriptionPtr;
	delete m_effectPtr;
}

//GETTER AND SETTER ORDER
string Order::getDesc() const{
	if (m_descriptionPtr != NULL) {
		return *m_descriptionPtr;
	}
	return "null";
}

void Order::setDesc(string _desc) {
	*m_descriptionPtr = _desc;
}

string Order::getEffect() const{
	if (m_effectPtr != NULL) {
		return *m_effectPtr;
	}
	return "null";
}

void Order::setEffect(string _execMessage) {
	*m_effectPtr = _execMessage;
}

Player* Order::getPlayer() const {
	return m_playerPtr;
}

void Order::setPlayer(Player _player) {
	*m_playerPtr = _player;
}

//stream insertion operator
std::ostream& operator<<(std::ostream& OUT, const Order& theOrder) {
	OUT << theOrder.getDesc() <<endl;

	//outputs effect if the order was executed
	if (!(theOrder.getEffect() == "") && !(theOrder.getEffect() == "invalid")) {
		OUT << "Effect: " << theOrder.getEffect();
	}

	return OUT;
}

//assignment operator
void Order::operator= (Order const &obj)
{
	m_playerPtr = obj.m_playerPtr;
	m_descriptionPtr = obj.m_descriptionPtr;
	m_effectPtr = obj.m_effectPtr;
}

//deploy class
Deploy::Deploy()
{
	setDesc("This is a Deploy order");
}

Deploy::Deploy(Player* _issuer, int _nbArmies, Territory* _target) : Order( _issuer)
{

	string desc = "Deploy order: Player " + to_string(*(_issuer->getId())) + "  deploys " + to_string(_nbArmies) + " armies to " + (*(_target->getTerritoryName()));
	setDesc(desc);

	nbArmies = new int(_nbArmies);
	target = _target;
}

Deploy::Deploy(const Deploy& _o) : Order(_o)
{
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

Territory* Deploy::getTarget() const {
	return target;
}

void Deploy::setTarget(Territory _target) {
	*target = _target;
}

Deploy::~Deploy() 
{
	delete nbArmies;
	nbArmies = nullptr;
}

//check if territory belongs to player
bool Deploy::validate() {

	
	if( (*(target->getOwner())->getId()) != (*(getPlayer()->getId())) ){
		cout << "DEBUG: Order not valid" << endl;
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
		cout << "DEBUG: did something no yet defined" << endl;
		setEffect("did something");
		return true;
	}
	else {
		cout << "DEBUG: Deploy order not executed" << endl;
		return false;
	}
}

//assign op
void Deploy::operator= (Deploy const& obj)
{
	Order::operator=(obj);
	nbArmies = obj.nbArmies;
	target = obj.target;
}

//Advance class
Advance::Advance()
{
	setDesc("This is an Advance order");
}

Advance::Advance(Player* _issuer, int _nbArmies, Territory* _source, Territory* _target) : Order(_issuer)
{
	string desc = "Advance order: Player"+ to_string(*(_issuer->getId())) +" Advances" + to_string(_nbArmies) + " armies from "+ (*(_source->getTerritoryName())) + " to " + (*(_target->getTerritoryName()));
	setDesc(desc);

	nbArmies = new int(_nbArmies);
	source = _source;
	target = _target;
}

Advance::Advance(const Advance& _o) : Order(_o)
{
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

Territory* Advance::getSource() const {
	return source;
}

void Advance::setSource(Territory _source) {
	*source = _source;
}

Territory* Advance::getTarget() const {
	return target;
}

void Advance::setTarget(Territory _target) {
	*target = _target;
}


//check if source belongs to player
//check if source and target are adjacent
bool Advance::validate() {
	
	//check owner
	if ((*(target->getOwner())->getId()) != (*(getPlayer()->getId()))) {
		cout << "DEBUG: Order not valid" << endl;
		return false;
	}

	//check if adjacent
	vector<int>* vec = source->getBorders();

	if (find(vec->begin(), vec->end(), (*(target->getId())) ) != vec->end()) {
		return true;
	}

	cout << "DEBUG: Order not valid" << endl;
	return false;
}

//prints Order type + add exec message 
//have to change when Orders are defined
bool Advance::execute() {
	bool valid = validate();

	if (valid) {
		cout << "DEBUG: Advance order executed" << endl;
		cout << "DEBUG: did something no yet defined" << endl;
		setEffect("did something");
		return true;
	}
	else {
		cout << "DEBUG: Advance order not executed" << endl;
		return false;
	}
}

//assign op
void Advance::operator= (Advance const& obj)
{
	Order::operator=(obj);
	nbArmies = obj.nbArmies;
	source = obj.source;
	target = obj.target;
}

//bomb class
Bomb::Bomb()
{
	setDesc("This is a Bomb order");
}

Bomb::Bomb(Player* _issuer, Territory* _target) : Order(_issuer)
{

	string desc = "Bomb order: Player " + to_string(*(_issuer->getId())) + " bombs " + (*(_target->getTerritoryName()));
	setDesc(desc);
	target = _target;
}

Bomb::Bomb(const Bomb& _o) : Order(_o)
{
	//copy target
	target = _o.getTarget();
}

Bomb::~Bomb() {
	
}

//GETTE AND SETTER
Territory* Bomb::getTarget() const {
	return target;
}

void Bomb::setTarget(Territory _target) {
	*target = _target;
}

//check owner of target
// check if adjacent
bool Bomb::validate() {
	//check owner
	if ((*(target->getOwner())->getId()) == (*(getPlayer()->getId()))) {
		cout << "DEBUG: Order not valid" << endl;
		return false;
	}

	bool adjacent = false;
	
	//check if target is adjacent to one of the players territory
	for (int i = 0; i < getPlayer()->getTerritories()->size(); i++) 
	{
		vector<int>*bvec = (*(getPlayer()->getTerritories()))[i]->getBorders();

		if (find(bvec->begin(), bvec->end(), (*(target->getId()))) != bvec->end()) 
		{
			adjacent = true;
			break;
		}
	}

	if (!adjacent)
	{
		cout << "DEBUG: Order not valid" << endl;
		return false;
	}

	return true;
}

//prints Order type + add exec message 
//have to change when Orders are defined
bool Bomb::execute() {
	bool valid = validate();

	if (valid) {
		cout << "DEBUG: Bomb order executed" << endl;
		cout << "DEBUG: did something no yet defined" << endl;
		setEffect("did something");
		return true;
	}
	else {
		cout << "DEBUG: Bomb order not executed" << endl;
		return false;
	}
}

//assign op
void Bomb::operator= (Bomb const& obj)
{
	Order::operator=(obj);
	target = obj.target;
}

//blockade class
Blockade::Blockade()
{
	setDesc("This is a Blockade order");
}

Blockade::Blockade(Player* _issuer, Territory* _target) : Order(_issuer)
{
	string desc = "Blockade order: Player "+ to_string(*(_issuer->getId())) + " blockades " + (*(_target->getTerritoryName()));
	setDesc(desc);
	target = _target;
}

Blockade::Blockade(const Blockade& o) : Order(o)
{
	//copy target
	target = o.getTarget();
}

Blockade::~Blockade() {
	
}

//GETTER AND SETTER BLOCKADE
Territory* Blockade::getTarget() const {
	return target;
}

void Blockade::setTarget(Territory _target) {
	*target = _target;
}

//check owner of target
bool Blockade::validate() {
	
	//check owner
	if ((*(target->getOwner())->getId()) != (*(getPlayer()->getId()))) {
		cout << "DEBUG: Order not valid" << endl;
		return false;
	}

	return true;
}

//prints Order type + add exec message 
//have to change when Orders are defined
bool Blockade::execute() {
	bool valid = validate();

	if (valid) {
		cout << "DEBUG: Blockade order executed" << endl;
		cout << "DEBUG: did something no yet defined" << endl;
		setEffect("did something");
		return true;
	}
	else {
		cout << "DEBUG: Blockade order not executed" << endl;
		return false;
	}
}

//assign op
void Blockade::operator= (Blockade const& obj)
{
	Order::operator=(obj);
	target = obj.target;
}

//airlift class
Airlift::Airlift()
{
	setDesc("This is an Airlift order");
}

Airlift::Airlift(Player* _issuer, int _nbArmies, Territory* _source, Territory* _target) : Order(_issuer)
{
	string desc = "Airlift order: Player "+ to_string(*(_issuer->getId())) +" airlifts " + to_string(_nbArmies) + " armies from "+ (*(_source->getTerritoryName()))+ " to " + (*(_target->getTerritoryName()));
	setDesc(desc);
	nbArmies = new int(_nbArmies);
	source = _source;
	target = _target;
}

Airlift::Airlift(const Airlift& _o) : Order(_o)
{
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

Territory* Airlift::getSource() const {
	return source;
}

void Airlift::setSource(Territory _source) {
	*source = _source;
}

Territory* Airlift::getTarget() const {
	return target;
}

void Airlift::setTarget(Territory _target) {
	*target = _target;
}

//check if player owns source and target
bool Airlift::validate() {
	
	//check owner of target
	if ((*(target->getOwner())->getId()) != (*(getPlayer()->getId()))) {
		cout << "DEBUG: Order not valid" << endl;
		return false;
	}

	//check owner of source
	if ((*(source->getOwner())->getId()) != (*(getPlayer()->getId()))) {
		cout << "DEBUG: Order not valid" << endl;
		return false;
	}
	
	return true;
}

//prints Order type + add exec message 
//have to change when Orders are defined
bool Airlift::execute() {
	bool valid = validate();

	if (valid) {
		cout << "DEBUG: Airlift order executed" << endl;
		cout << "DEBUG: did something no yet defined" << endl;
		setEffect("did something");
		return true;
	}
	else {
		cout << "DEBUG: Airlift order not executed" << endl;
		return false;
	}
}

//assign op
void Airlift::operator= (Airlift const& obj)
{
	Order::operator=(obj);
	nbArmies = obj.nbArmies;
	source = obj.source;
	target = obj.target;
}

//negotiate class
Negotiate::Negotiate()
{
	setDesc("This is a Negotiate order");
}

Negotiate::Negotiate(Player* _issuer, Player* _victim) : Order(_issuer)
{
	string desc = "Negotiate order: Player " + to_string(*(_issuer->getId())) + " negotiates with Player " + to_string(*(_victim->getId()));
	setDesc(desc);
	victim = _victim;
	
}

Negotiate::Negotiate(const Negotiate& _o) : Order(_o)
{
	victim = _o.getVictim();
}

Negotiate::~Negotiate() {

}

//GETTER AND SETTER NEGOTIATE
Player* Negotiate::getVictim() const {
	return victim;
}

void Negotiate::setVictim(Player _victim) {
	*victim = _victim;
}


//check if player is negotating with himself
bool Negotiate::validate() {
	
	//check if player and victim are the same
	if ((*(victim->getId())) == (*(getPlayer()->getId()))) {
		cout << "DEBUG: Order not valid" << endl;
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
		cout << "DEBUG: did something no yet defined" << endl;
		setEffect("did something");
		return true;
	}
	else {
		cout << "DEBUG: Negotiate order not executed" << endl;
		return false;
	}
}

//assign op
void Negotiate::operator= (Negotiate const& obj)
{
	Order::operator=(obj);
	victim = obj.victim;
}

//OrderList class
OrderList::OrderList()
{
	m_theListPtr = new std::vector<Order*>;
}

OrderList::OrderList(const OrderList& o)
{
	m_theListPtr = new vector<Order* >(*(o.getList()));
}


OrderList::~OrderList()
{
	for (Order* obj : *m_theListPtr)
	{
		delete obj;
	}
	delete m_theListPtr;
}


vector<Order* >* OrderList::getList() const
{
	return m_theListPtr;
}

bool OrderList::Add(Order* _obj)
{
	m_theListPtr->push_back(_obj);
	return true;
}

bool OrderList::remove(int _i)
{
	if (m_theListPtr->size() <= _i || _i < 0) 
	{
		cout << "DEBUG: out of index" << endl;
		return false;
	}
	else 
	{
		m_theListPtr->erase(m_theListPtr->begin() + _i);
		return true;
	}	
}

bool OrderList::move(int _objIndex, int _newIndex)
{
	if (m_theListPtr->size() <= _objIndex || _objIndex < 0 || m_theListPtr->size() <= _newIndex || _newIndex < 0)
	{
		cout << "debug: out of index" << endl;
		return false;
	}
	else
	{
		Order* temp = m_theListPtr->at(_objIndex);
		m_theListPtr->erase(m_theListPtr->begin()+_objIndex);
		m_theListPtr->insert(m_theListPtr->begin() + _newIndex, temp);
		return true;
	}
	
}

std::ostream& operator<<(std::ostream& OUT, const OrderList& theOrderList)
{
	for (Order* obj : *(theOrderList.getList()) )
	{
		OUT << *obj;
	}

	return OUT;
}

void OrderList::operator= (OrderList const& _other)
{
	m_theListPtr = _other.m_theListPtr;
}




