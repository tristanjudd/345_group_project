#include "Orders.h"
#include <iostream>
using namespace std;
#include <string>

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
	return *description;
}

void Order::setDesc(string desc) {
	description = new string(desc);
}

string Order::getEffect() const{
	return *effect;
}

void Order::setEffect(string execMessage) {
	effect = new string(execMessage);
}

//stream insertion operator
std::ostream& operator<<(std::ostream& OUT, const Order& theOrder) {
	OUT << theOrder.getDesc() << endl;

	//outputs effect if the order was executed
	if (!(theOrder.getEffect() == "") && !(theOrder.getEffect() == "invalid")) {
		OUT << "Effect: " << theOrder.getEffect();
	}

	return OUT;
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
deploy::deploy() : Order(){
}

deploy::deploy(string execMessage) : Order(execMessage) {

}

deploy::~deploy() {
	delete effect;
	delete description;
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
Advance::Advance() : Order(){

}

Advance::Advance(string execMessage) : Order(execMessage) {

}

Advance::~Advance() {
	delete effect;
	delete description;
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
bomb::bomb() : Order() {

}

bomb::bomb(string execMessage) : Order(execMessage) {

}

bomb::~bomb() {
	delete effect;
	delete description;
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
blockade::blockade() : Order() {

}

blockade::blockade(string execMessage) : Order(execMessage) {

}

blockade::~blockade() {
	delete effect;
	delete description;
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
airlift::airlift() : Order() {

}

airlift::airlift(string execMessage) : Order(execMessage) {

}

airlift::~airlift() {
	delete effect;
	delete description;
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
negotiate::negotiate() : Order() {

}

negotiate::negotiate(string execMessage) : Order(execMessage) {

}

negotiate::~negotiate() {
	delete effect;
	delete description;
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

