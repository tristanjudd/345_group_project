#pragma once

#include <iostream>
using std::cout;
#include<vector>
using std::vector;
#include <string>
using namespace std;
#include "../Player/Player.h"


class Order
{
public:

	Order();
	Order(Player* _issuer);
	Order(const Order& _o);
	virtual ~Order();

	virtual bool validate() = 0;
	virtual bool execute() = 0;

	string getEffect() const;
	void setEffect(string _execMessage);
	string getDesc() const;
	void setDesc(string _desc);
	Player getPlayer() const;
	void setPlayer(Player _player);

	void operator= (Order const &);
	
private:
	string* m_descriptionPtr;
	string* m_effectPtr;
	Player* m_playerPtr;
};

//stream insertion operator ORDER
std::ostream& operator<<(std::ostream& OUT, const Order& theOrder);


class Deploy : public Order
{
public:
	Deploy();
	Deploy(Player* _issuer, int _nbArmies, Territory* _target);
	Deploy(const Deploy& _o);
	~Deploy();

	int getNbArmies() const;
	void setNbArmies(int _nbArmies);
	Territory getTarget() const;
	void setTarget(Territory _target);

	bool validate();
	bool execute();

	void operator= (Deploy const &);

private:
	int *nbArmies;
	Territory* target;
};

class Advance : public Order
{
public:
	Advance();
	Advance(Player* _issuer,int _nbArmies, Territory* _source, Territory* _target);
	Advance(const Advance& _o);
	~Advance();

	//getter and setters
	int getNbArmies() const;
	void setNbArmies(int _nbArmies);
	Territory getSource() const;
	void setSource(Territory _source);
	Territory getTarget() const;
	void setTarget(Territory _target);
	
	void operator= (Advance const &);

	bool validate();
	bool execute();

private:
	int* nbArmies;
	Territory* source;
	Territory* target;
};

class Bomb : public Order
{
public:
	Bomb();
	Bomb(Player* _issuer, Territory* _target);
	Bomb(const Bomb& _o);
	~Bomb();

	//getter and setter
	Territory getTarget() const;
	void setTarget(Territory _target);

	void operator= (Bomb const &);

	bool validate();
	bool execute();

private:
	Territory* target;
};

class Blockade : public Order
{
public:
	Blockade();
	Blockade(Player* _issuer, Territory* _target);
	Blockade(const Blockade& _o);
	~Blockade();

	//getter and setter
	Territory getTarget() const;
	void setTarget(Territory _target);

	void operator= (Blockade const &);

	bool validate();
	bool execute();

private:
	Territory* target;
};


class Airlift : public Order
{
public:
	Airlift();
	Airlift(Player* _issuer, int _nbArmies, Territory* _source, Territory* _target);
	Airlift(const Airlift& _o);
	~Airlift();

	//getter and setters
	int getNbArmies() const;
	void setNbArmies(int _nbArmies);
	Territory getSource() const;
	void setSource(Territory _source);
	Territory getTarget() const;
	void setTarget(Territory _target);

	void operator= (Airlift const &);

	bool validate();
	bool execute();

private:
	int* nbArmies;
	Territory* source;
	Territory* target;
};

class Negotiate : public Order
{
public:
	Negotiate();
	Negotiate(Player* _issuer, Player* _victim);
	Negotiate(const Negotiate& _o);
	~Negotiate();

	//getter and setter;
	Player getVictim() const;
	void setVictim(Player _victim);

	void operator= (Negotiate const &);

	bool validate();
	bool execute();

private:
	Player* issuer;
	Player* victim;
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


