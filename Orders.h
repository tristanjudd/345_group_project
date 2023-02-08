#pragma once

#include <iostream>
using namespace std;
#include <string>

class OrderList
{
public:
	bool remove();
	bool move();
	
private:

};

class Order
{
public:

	Order();
	Order(string execMessage);
	Order(const Order& o);
	~Order();

	bool validate();
	bool execute();

	string getEffect() const;
	void setEffect(string execMessage);
	string getDesc() const;
	void setDesc(string desc);

protected:
	string* description;
	string* effect;
private:
	
};

//stream insertion operator
std::ostream& operator<<(std::ostream& OUT, const Order& theOrder);

class deploy : public Order
{
public:
	deploy();
	deploy(string execMessage);
	~deploy();

	bool validate();
	bool execute();

private:
};

class Advance : public Order
{
public:
	Advance();
	Advance(string execMessage);
	~Advance();

	bool validate();
	bool execute();

private:

};

class bomb : public Order
{
public:
	bomb();
	bomb(string message);
	~bomb();

	bool validate();
	bool execute();

private:

};

class blockade : public Order
{
public:
	blockade();
	blockade(string execMessage);
	~blockade();

	bool validate();
	bool execute();

private:

};


class airlift : public Order
{
public:
	airlift();
	airlift(string execMessage);
	~airlift();

	bool validate();
	bool execute();

private:

};

class negotiate : public Order
{
public:
	negotiate();
	negotiate(string execMessage);
	~negotiate();

	bool validate();
	bool execute();

private:

};
