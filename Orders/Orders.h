#pragma once

#include <iostream>
using std::cout;
#include<vector>
using std::vector;
#include <string>
#include <cstdlib>
using std::rand;
#include <unordered_map>
using std::string;
using std::unordered_map;
using std::to_string;

#include "../Map/Map.h"
#include "../GameLog/LoggingObserver.h"

//forward declaration
class Player;
class Territory;

class Order: public ILoggable, public Subject
{
public:

	Order(LogObserver* observer);
	Order(Player* _issuer, LogObserver* observer);
	Order(const Order& _o);
	virtual ~Order();

	virtual bool validate() = 0;
	virtual bool execute() = 0;

	string getEffect() const;
	void setEffect(string _execMessage);
	string getDesc() const;
	void setDesc(string _desc);
	Player* getPlayer() const;
	void setPlayer(Player _player);
    void stringToLog();

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
	Deploy(LogObserver* observer);
	Deploy(Player* _issuer, int _nbArmies, Territory* _target, LogObserver* observer);
	Deploy(const Deploy& _o);
	~Deploy();

	int getNbArmies() const;
	void setNbArmies(int _nbArmies);
	Territory* getTarget() const;
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
	Advance(LogObserver* observer);
	Advance(Player* _issuer,int _nbArmies, Territory* _source, Territory* _target, LogObserver* observer);
	Advance(const Advance& _o);
	~Advance();

	//getter and setters
	int getNbArmies() const;
	void setNbArmies(int _nbArmies);
	Territory* getSource() const;
	void setSource(Territory _source);
	Territory* getTarget() const;
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
	Bomb(LogObserver* observer);
	Bomb(Player* _issuer, Territory* _target, LogObserver* observer);
	Bomb(const Bomb& _o);
	~Bomb();

	//getter and setter
	Territory* getTarget() const;
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
	Blockade(LogObserver* observer);
	Blockade(Player* _issuer, Territory* _target, LogObserver* observer);
	Blockade(const Blockade& _o);
	~Blockade();

	//getter and setter
	Territory* getTarget() const;
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
	Airlift(LogObserver* observer);
	Airlift(Player* _issuer, int _nbArmies, Territory* _source, Territory* _target, LogObserver* observer);
	Airlift(const Airlift& _o);
	~Airlift();

	//getter and setters
	int getNbArmies() const;
	void setNbArmies(int _nbArmies);
	Territory* getSource() const;
	void setSource(Territory _source);
	Territory* getTarget() const;
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
	Negotiate(LogObserver* observer);
	Negotiate(Player* _issuer, int _victimID, LogObserver* observer);
	Negotiate(const Negotiate& _o);
	~Negotiate();

	//getter and setter;
	int getVictim() const;
	void setVictim(int _victimID);

	void operator= (Negotiate const &);

	bool validate();
	bool execute();

private:
	Player* issuer;
	int* victim;
};

//Cheat Order for Cheater Strategy
class Cheat: public Order
{
    public:
        Cheat(Player* _issuer, LogObserver* observer);
        Cheat(const Cheat& _o);
        ~Cheat();

        bool validate();
        bool execute();

        void operator= (Cheat const &);

};


class OrderList: public ILoggable, public Subject
{
public:

	OrderList(LogObserver* observer);
	OrderList(const OrderList& o, LogObserver* observer);
	~OrderList();

	bool Add(Order* _obj);
	bool remove(int _i);
	bool move(int _objIndex, int _newIndex);
	vector<Order* >* getList() const;
	void operator= (OrderList const&);
    void stringToLog();

private:
	vector<Order* >* m_theListPtr;
};

//stream insertion operator OrderList
std::ostream& operator<<(std::ostream& OUT, const OrderList& theOrderList);


