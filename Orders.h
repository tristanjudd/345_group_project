#pragma once

#include <iostream>
using std::cout;
#include<vector>
using std::vector;
#include <string>
using namespace std;





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
	
private:
	string* description;
	string* effect;
	
};

//stream insertion operator
std::ostream& operator<<(std::ostream& OUT, const Order& theOrder);

class deploy : public Order
{
public:
	deploy();
	deploy(string execMessage);
	deploy(const deploy& o);
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
	Advance(const Advance& o);
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
	bomb(const bomb& o);
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
	blockade(const blockade& o);
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
	airlift(const airlift& o);
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
	negotiate(const negotiate& negotiate);
	~negotiate();

	bool validate();
	bool execute();

private:

};

class OrderList
{
public:

	OrderList();
	OrderList(const OrderList& o);
	~OrderList();

	bool Add(Order obj);
	bool remove(int i);
	bool move(int objIndex, int newIndex);
	std::vector<Order> getList() const;
	void print();

	std::vector<Order>* theList;

private:
	//std::vector<Order>* theList;
};
