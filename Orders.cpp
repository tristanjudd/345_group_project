#include "Orders.h"
#include <iostream>
using namespace std;
#include <string>

//Order class
Order::Order() {
	effect = new string("");
}

Order::Order(string execMessage) {
	effect = new string(execMessage);
}

Order::~Order() {
	delete effect;
}

//deploy class
deploy::deploy() : Order() {

}

deploy::deploy(string execMessage) : Order(execMessage) {

}

deploy::~deploy() {
	delete effect;
}

//advance class
advance::advance() : Order(){

}

advance::advance(string execMessage) : Order(execMessage) {

}

advance::~advance() {
	delete effect;
}

//bomb class
bomb::bomb() : Order() {

}

bomb::bomb(string execMessage) : Order(execMessage) {

}

bomb::~bomb() {
	delete effect;
}

//blockade class
blockade::blockade() : Order() {

}

blockade::blockade(string execMessage) : Order(execMessage) {

}

blockade::~blockade() {
	delete effect;
}

//deploy class
deploy::deploy() : Order() {

}

deploy::deploy(string execMessage) : Order(execMessage) {

}

deploy::~deploy() {
	delete effect;
}

//airlift class
airlift::airlift() : Order() {

}

airlift::airlift(string execMessage) : Order(execMessage) {

}

airlift::~airlift() {
	delete effect;
}

//negotiate class
negotiate::negotiate() : Order() {

}

negotiate::negotiate(string execMessage) : Order(execMessage) {

}

negotiate::~negotiate() {
	delete effect;
}