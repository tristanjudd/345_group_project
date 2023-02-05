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
	~Order();

	bool validate();
	bool execute();

	friend ostream& operator <<(ostream& OUT, const Order& theOrder);

protected:
	string* effect;
private:
	
};

class deploy : public Order
{
public:
	deploy();
	deploy(string execMessage);
	~deploy();

	bool validate();
	bool execute();

	friend ostream& operator <<(ostream& OUT, const deploy& theOrder);
private:
	
};

class advance : public Order
{
public:
	advance();
	advance(string execMessage);
	~advance();

	bool validate();
	bool execute();
	friend ostream& operator <<(ostream& OUT, const advance& theOrder);

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
	friend ostream& operator <<(ostream& OUT, const bomb& theOrder);

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
	friend ostream& operator <<(ostream& OUT, const blockade& theOrder);
private:

};

class deploy : public Order
{
public:
	deploy();
	deploy(string execMessage);
	~deploy();

	bool validate();
	bool execute();
	friend ostream& operator <<(ostream& OUT, const deploy& theOrder);

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
	friend ostream& operator <<(ostream& OUT, const airlift& theOrder);

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
	friend ostream& operator <<(ostream& OUT, const negotiate& theOrder);

private:

};
