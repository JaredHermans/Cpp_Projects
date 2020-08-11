//#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#ifndef ORDER_CLASS_H
#define ORDER_CLASS_H

class order_record
{
public:
	string pname;
	string cname;
	double plant_cost;
	int quantity;
	double net_cost;
	double tax_rate;
	double purchase_tax;
	double discount;
	double total_cost;
};

class order_class
{
public:
	order_class();
	order_class(const order_class& org);							//copy constructor
	~order_class();													//de-allocates all memory allocate to STR by operator new.
	bool is_Empty();												//inline implementation
	bool is_full();													//inline implementation
	int search(const string key);									//returns location of key if in STR; otherwise return -1
	void add();														//adds a order record to STR
	order_class& operator-(const string key);						//removes all items in STR with a plant name that matches key.
	void double_size();
	void process();
	friend ostream& operator<<(ostream& out, order_class& ORG);		//prints all the elements in ORG's STR to the screen
private:
	int count;
	int size;
	order_record* STR;
};



#endif // !ORDER_CLASS_H