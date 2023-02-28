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
	Order(string _execMessage);
	Order(const Order& _o);
	virtual ~Order();

	virtual bool validate() = 0;
	virtual bool execute() = 0;

	string getEffect() const;
	void setEffect(string _execMessage);
	string getDesc() const;
	void setDesc(string _desc);
	void operator= (Order const &);
	
private:
	string* m_descriptionPtr;
	string* m_effectPtr;
};

//stream insertion operator ORDER
std::ostream& operator<<(std::ostream& OUT, const Order& theOrder);


class Deploy : public Order
{
public:
	Deploy();
	Deploy(string _execMessage);
	Deploy(const Deploy& _o);
	~Deploy();

	bool validate();
	bool execute();

private:
};

class Advance : public Order
{
public:
	Advance();
	Advance(string _execMessage);
	Advance(const Advance& _o);
	~Advance();

	bool validate();
	bool execute();

private:

};

class Bomb : public Order
{
public:
	Bomb();
	Bomb(string _execMessage);
	Bomb(const Bomb& _o);
	~Bomb();

	bool validate();
	bool execute();

private:

};

class Blockade : public Order
{
public:
	Blockade();
	Blockade(string _execMessage);
	Blockade(const Blockade& _o);
	~Blockade();

	bool validate();
	bool execute();

private:

};


class Airlift : public Order
{
public:
	Airlift();
	Airlift(string _execMessage);
	Airlift(const Airlift& _o);
	~Airlift();

	bool validate();
	bool execute();

private:

};

class Negotiate : public Order
{
public:
	Negotiate();
	Negotiate(string _execMessage);
	Negotiate(const Negotiate& _o);
	~Negotiate();

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

	bool Add(Order* _obj);
	bool remove(int _i);
	bool move(int _objIndex, int _newIndex);
	vector<Order* >* getList() const;
	void operator= (OrderList const&);

private:
	vector<Order* >* m_theListPtr;
};

//stream insertion operator OrderList
std::ostream& operator<<(std::ostream& OUT, const OrderList& theOrderList);


