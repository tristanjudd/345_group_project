#include "Orders.h"

//Order class
Order::Order() {
	m_descriptionPtr = new string("This is an Order."); //Description of the Order
	m_effectPtr = new string(""); //Effect of the Order after being executed
}

Order::Order(string _execMessage) {
	m_descriptionPtr = new string("This is an Order.");
	m_effectPtr = new string(_execMessage);
}

//copy constructor
Order::Order(const Order& o) {
	m_descriptionPtr = new string(o.getDesc());
	m_effectPtr = new string(o.getEffect());
}

Order::~Order() {
	delete m_descriptionPtr;
	delete m_effectPtr;
}

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
	m_descriptionPtr = obj.m_descriptionPtr;
	m_effectPtr = obj.m_effectPtr;
}

//invalid obj are created with "invalid" exec message
//have to change when Orders are defined
bool Order::validate() {
	if (getEffect() == "invalid") {
		return false;
	}
	
	return true;
}

//prints Order type + add exec message 
//have to change when Orders are defined
bool Order::execute() {
	bool valid = validate();

	if (valid) {
		cout << "DEBUG: Order executed" << endl;
		cout << "DEBUG: did something no yet defined" << endl;
		setEffect("did something");
		return true;
	}
	else {
		cout << "DEBUG: Order not executed" << endl;
		return false;
	}
}

//deploy class
Deploy::Deploy()
{
	setDesc("This is a Deploy order");
}

Deploy::Deploy(string _execMessage) : Order(_execMessage)
{
	setDesc("This is a Deploy order");
	setEffect(_execMessage);
}

Deploy::Deploy(const Deploy& _o) : Order(_o)
{

}

Deploy::~Deploy() 
{

}

//invalid obj are created with "invalid" exec message
//have to change when Orders are defined
bool Deploy::validate() {
	if (getEffect() == "invalid") {
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

//Advance class
Advance::Advance()
{
	setDesc("This is an Advance order");
}

Advance::Advance(string _execMessage)
{
	setDesc("This is an Advance order");
	setEffect(_execMessage);
}

Advance::Advance(const Advance& _o) : Order(_o)
{

}

Advance::~Advance() {

}

//invalid obj are created with "invalid" exec message
//have to change when Orders are defined
bool Advance::validate() {
	if (getEffect() == "invalid") {
		return false;
	}

	return true;
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
		cout << "DEBUG: Avance order not executed" << endl;
		return false;
	}
}

//bomb class
Bomb::Bomb()
{
	setDesc("This is a Bomb order");
}

Bomb::Bomb(string _execMessage) 
{
	setDesc("This is a Bomb order");
	setEffect(_execMessage);
}

Bomb::Bomb(const Bomb& _o) : Order(_o)
{

}

Bomb::~Bomb() {

}

//invalid obj are created with "invalid" exec message
//have to change when Orders are defined
bool Bomb::validate() {
	if (getEffect() == "invalid") {
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

//blockade class
Blockade::Blockade()
{
	setDesc("This is a Blockade order");
}

Blockade::Blockade(string _execMessage)
{
	setDesc("This is a Blockade order");
	setEffect(_execMessage);
}

Blockade::Blockade(const Blockade& o) : Order(o)
{

}

Blockade::~Blockade() {

}

//invalid obj are created with "invalid" exec message
//have to change when Orders are defined
bool Blockade::validate() {
	if (getEffect() == "invalid") {
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

//airlift class
Airlift::Airlift()
{
	setDesc("This is an Airlift order");
}

Airlift::Airlift(string execMessage)
{
	setDesc("This is an Airlift order");
	setEffect(execMessage);
}

Airlift::Airlift(const Airlift& _o) : Order(_o)
{

}

Airlift::~Airlift() {

}

//invalid obj are created with "invalid" exec message
//have to change when Orders are defined
bool Airlift::validate() {
	if (getEffect() == "invalid") {
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

//negotiate class
Negotiate::Negotiate()
{
	setDesc("This is a Negotiate order");
}

Negotiate::Negotiate(string _execMessage)
{
	setDesc("This is a Negotiate order");
	setEffect(_execMessage);
}

Negotiate::Negotiate(const Negotiate& _o) : Order(_o)
{

}

Negotiate::~Negotiate() {

}

//invalid obj are created with "invalid" exec message
//have to change when Orders are defined
bool Negotiate::validate() {
	if (getEffect() == "invalid") {
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




