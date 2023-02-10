#include "Orders.h"
#include <iostream>
using std::cout;
#include <vector>
using std::vector;
#include <string>
using namespace std;

//Order class
Order::Order() {
	description = new string("This is an Order.");
	effect = new string("");
}

Order::Order(string execMessage) {
	description = new string("This is an Order.");
	effect = new string(execMessage);
}

//copy constructor
Order::Order(const Order& o) {
	description = new string(o.getDesc());
	effect = new string(o.getEffect());
}

Order::~Order() {
	delete description;
	delete effect;
}

string Order::getDesc() const{
	if (description != NULL) {
		return *description;
	}
	return "null";
}

void Order::setDesc(string desc) {
	delete description;
	description = new string(desc);
}

string Order::getEffect() const{
	if (effect != NULL) {
		return *effect;
	}
	return "null";
}

void Order::setEffect(string execMessage) {
	delete effect;
	effect = new string(execMessage);
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
	description = obj.description;
	effect = obj.effect;
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
		cout << "DEBUG: order executed" << endl;
		cout << "DEBUG: did something no yet defined" << endl;
		setEffect("did something");
		return true;
	}
	else {
		cout << "DEBUG: order not executed" << endl;
		return false;
	}
}

//deploy class
deploy::deploy()
{
	setDesc("This is a deploy order");
}

deploy::deploy(string execMessage) : Order(execMessage)
{
	setDesc("This is a deploy order");
	setEffect(execMessage);
}

deploy::deploy(const deploy& o) : Order(o)
{

}

deploy::~deploy() 
{

}

//invalid obj are created with "invalid" exec message
//have to change when Orders are defined
bool deploy::validate() {
	if (getEffect() == "invalid") {
		return false;
	}

	return true;
}

//prints Order type + add exec message 
//have to change when Orders are defined
bool deploy::execute() {
	bool valid = validate();

	if (valid) {
		cout << "DEBUG: order executed" << endl;
		cout << "DEBUG: did something no yet defined" << endl;
		setEffect("did something");
		return true;
	}
	else {
		cout << "DEBUG: deploy order not executed" << endl;
		return false;
	}
}

//Advance class
Advance::Advance()
{
	setDesc("This is an advance order");
}

Advance::Advance(string execMessage)
{
	setDesc("This is an advance order");
	setEffect(execMessage);
}

Advance::Advance(const Advance& o) : Order(o)
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
		cout << "DEBUG: order executed" << endl;
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
bomb::bomb()
{
	setDesc("This is a bomb order");
}

bomb::bomb(string execMessage) 
{
	setDesc("This is a bomb order");
	setEffect(execMessage);
}

bomb::bomb(const bomb& o) : Order(o)
{

}

bomb::~bomb() {

}

//invalid obj are created with "invalid" exec message
//have to change when Orders are defined
bool bomb::validate() {
	if (getEffect() == "invalid") {
		return false;
	}

	return true;
}

//prints Order type + add exec message 
//have to change when Orders are defined
bool bomb::execute() {
	bool valid = validate();

	if (valid) {
		cout << "DEBUG: order executed" << endl;
		cout << "DEBUG: did something no yet defined" << endl;
		setEffect("did something");
		return true;
	}
	else {
		cout << "DEBUG: bomb order not executed" << endl;
		return false;
	}
}

//blockade class
blockade::blockade()
{
	setDesc("This is a blockade order");
}

blockade::blockade(string execMessage)
{
	setDesc("This is a blockade order");
	setEffect(execMessage);
}

blockade::blockade(const blockade& o) : Order(o)
{

}

blockade::~blockade() {

}

//invalid obj are created with "invalid" exec message
//have to change when Orders are defined
bool blockade::validate() {
	if (getEffect() == "invalid") {
		return false;
	}

	return true;
}

//prints Order type + add exec message 
//have to change when Orders are defined
bool blockade::execute() {
	bool valid = validate();

	if (valid) {
		cout << "DEBUG: order executed" << endl;
		cout << "DEBUG: did something no yet defined" << endl;
		setEffect("did something");
		return true;
	}
	else {
		cout << "DEBUG: blockade order not executed" << endl;
		return false;
	}
}

//airlift class
airlift::airlift()
{
	setDesc("This is an airlift order");
}

airlift::airlift(string execMessage)
{
	setDesc("This is an airlift order");
	setEffect(execMessage);
}

airlift::airlift(const airlift& o) : Order(o)
{

}

airlift::~airlift() {

}

//invalid obj are created with "invalid" exec message
//have to change when Orders are defined
bool airlift::validate() {
	if (getEffect() == "invalid") {
		return false;
	}

	return true;
}

//prints Order type + add exec message 
//have to change when Orders are defined
bool airlift::execute() {
	bool valid = validate();

	if (valid) {
		cout << "DEBUG: order executed" << endl;
		cout << "DEBUG: did something no yet defined" << endl;
		setEffect("did something");
		return true;
	}
	else {
		cout << "DEBUG: airlift order not executed" << endl;
		return false;
	}
}

//negotiate class
negotiate::negotiate()
{
	setDesc("This is a negotiate order");
}

negotiate::negotiate(string execMessage)
{
	setDesc("This is a negotiate order");
	setEffect(execMessage);
}

negotiate::negotiate(const negotiate& o) : Order(o)
{

}

negotiate::~negotiate() {

}

//invalid obj are created with "invalid" exec message
//have to change when Orders are defined
bool negotiate::validate() {
	if (getEffect() == "invalid") {
		return false;
	}

	return true;
}

//prints Order type + add exec message 
//have to change when Orders are defined
bool negotiate::execute() {
	bool valid = validate();

	if (valid) {
		cout << "DEBUG: negotiate order executed" << endl;
		cout << "DEBUG: did something no yet defined" << endl;
		setEffect("did something");
		return true;
	}
	else {
		cout << "DEBUG: order not executed" << endl;
		return false;
	}
}

//OrderList class
OrderList::OrderList()
{
	theList = new std::vector<Order*>;
}

//OrderList::OrderList(const OrderList& o)
//{
//	theList = new std::vector<Order> (*(o.getList()));
//}

OrderList::~OrderList()
{
	for (Order* obj : *theList)
	{
		delete obj;
	}
	delete theList;
}

//vector<Order>* OrderList::getList() const
//{
//	return theList;
//}

bool OrderList::Add(Order* obj)
{
	theList->push_back(obj);
	return true;
}

bool OrderList::remove(int i)
{
	if (theList->size() <= i || i < 0) 
	{
		cout << "DEBUG: out of index" << endl;
		return false;
	}
	else 
	{
		theList->erase(theList->begin() + i);
		return true;
	}	
}

bool OrderList::move(int _objIndex, int newIndex)
{
	if (m_theList->size() <= objIndex || objIndex < 0 || theList->size() <= newIndex || newIndex < 0)
	{
		cout << "debug: out of index" << endl;
		return false;
	}
	else
	{
		Order* temp = theList->at(objIndex);
		theList->erase(theList->begin()+objIndex);
		theList->insert(theList->begin() + newIndex, temp);
		return true;
	}
	
}

void OrderList::print() 
{
	for (Order *obj : *theList)
	{
		cout << *obj;
	}
}




