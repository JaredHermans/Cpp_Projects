//order_class.cpp
#include <iostream>
#include <fstream>
#include <iomanip>
#include "order_class.h"
using namespace std;



/************************************************************************************************************************************/
//Name: Default Constructor
//Decription: Reads the data file of purchase order information (plant name, county name, plant cost and quantity) into the dynamic array of order records, 
		//STR. If the count become equal to the size the function double_size is called and the memory allocated to STR is doubled.
/************************************************************************************************************************************/
order_class::order_class()
{
	cout << "The default constructor has been called\n";
	count = 0;
	size = 1;
	STR = new order_record[size];
	ifstream in;
	in.open("nursery_stock.txt");
	if (in.fail())
		cout << "Input file did not open correctly";
	else
	{
		for (int i = 0; i < size && !in.eof(); i++)
		{
			in >> STR[count].pname >> STR[count].cname >> STR[count].plant_cost >> STR[count].quantity;
			count++;

			if (is_full())
				double_size();
		}
	}
	in.close();
}

/************************************************************************************************************************************/
//Name: copy constructor
//Decription: The function performs a deep copy of the formal parameter org.
/************************************************************************************************************************************/
order_class::order_class(const order_class& org)
{
	cout << "Copy constructor has been called\n";
	(*this).size = org.size;
	this->count = org.count;
	this->STR = new order_record[size];
	for (int i = 0; i < count; i++)
	{
		STR[i] = org.STR[i];
	}
}

/***********************************************************************************************************************************/
//Decription: returns true if STR is empty
/**********************************************************************************************************************************/
bool order_class::is_Empty()
{
	return count == 0;
}

/**********************************************************************************************************************************/
//Decription: returns true if STR is full
/*********************************************************************************************************************************/
bool order_class::is_full()
{
	return count == size;
}

/**********************************************************************************************************************************/
//Decription: locates key in STR if it is there; otherwise -1 is returned
/*********************************************************************************************************************************/
int order_class::search(const string key)
{
	return -1;
}

/*********************************************************************************************************************************/
//Decription: adds a order_record to STR; if STR is full, double_size is called to increase the size of STR. The user 
//            is prompted to enter the plant name, county name, plant cost and quantity.
/********************************************************************************************************************************/
void order_class::add()
{
	char ans = 'Y';
	while (ans == 'Y' || ans == 'y')
	{
		cout << "Enter Plant Name, County Name, Plant Cost, and Quantity of plants and return after each: \n";
		cin >> STR[count].pname >> STR[count].cname >> STR[count].plant_cost >> STR[count].quantity;
		count++;
		cout << "Enter another order? Y for yes, N for no\n";
		cin >> ans;
	}
	process();
}

/********************************************************************************************************************************/
//Name: operator-
//Decription: removes all order records in STR with a plant name field that matches key, if it is there.
/*******************************************************************************************************************************/
order_class& order_class::operator-(const string key)
{
	int trigger = -1, i;
	for (i = 0; i < count; i++)
	{
		if (STR[i].pname == key)
		{
			trigger = i;
			break;
		}
	}
	if (trigger != -1)
	{
		for (i = trigger; i < count - 1; i++)
		{
			STR[i] = STR[i + 1];
		}
		count--;
	}
	if (trigger != -1)
	{
		order_class::operator-(key);
	}
	return *this; //returning the current object
}

/******************************************************************************************************************************/
//Decription: doubles the size (capacity) of STR
/******************************************************************************************************************************/
void order_class::double_size()
{
	size *= 2;
	order_record* temp = new order_record[size];

	for (int i = 0; i < count; i++)
	{
		temp[i] = STR[i];
	}

	delete[] STR;
	STR = temp;
}


/******************************************************************************************************************************/
//Decription: calculate the net cost, tax rate, order tax, discount and total cost for every order record in STR. for every call record in STR.
/*****************************************************************************************************************************/
void order_class::process()
{
	for (int i = 0; i < count; i++)
	{
		STR[i].net_cost = STR[i].quantity * STR[i].plant_cost;					//Calculating net cost

		if (STR[i].cname == "dade")												//determining purchase_tax based on county
		{
			STR[i].tax_rate = 0.065;
			STR[i].purchase_tax = STR[i].tax_rate * STR[i].net_cost;
		}
		else if (STR[i].cname == "broward")
		{
			STR[i].tax_rate = 0.06;
			STR[i].purchase_tax = STR[i].tax_rate * STR[i].net_cost;
		}
		else if (STR[i].cname == "palm")
		{
			STR[i].tax_rate = 0.07;
			STR[i].purchase_tax = STR[i].tax_rate * STR[i].net_cost;
		}


		if (STR[i].quantity <= 0)													//calculating discount rate based on quantity
			STR[i].discount = 0;
		else if ((STR[i].quantity >= 1) && (STR[i].quantity <= 5))
			STR[i].discount = 0.01 * STR[i].net_cost;
		else if ((STR[i].quantity >= 6) && (STR[i].quantity <= 11))
			STR[i].discount = 0.03 * STR[i].net_cost;
		else if ((STR[i].quantity >= 12) && (STR[i].quantity <= 20))
			STR[i].discount = 0.05 * STR[i].net_cost;
		else if ((STR[i].quantity >= 21) && (STR[i].quantity <= 50))
			STR[i].discount = 0.08 * STR[i].net_cost;
		else if (STR[i].quantity > 50)
			STR[i].discount = 0.12 * STR[i].net_cost;

		//Calculating total_cost
		STR[i].total_cost = STR[i].net_cost + STR[i].purchase_tax - STR[i].discount;
	}
}


/****************************************************************************************************************************/
//Name: operator<<
//Decription: prints every field of every call_record in STR formatted to a file and return the stream.
/***************************************************************************************************************************/
ostream& operator<<(ostream& out, order_class& org)
{

	static int run = 1;

	//put code here for the loop to print the data in the array to the stream out.

	out.setf(ios::showpoint);														//Seting precision to 2 decimal places
	out.precision(2);
	out.setf(ios::fixed);

	out << "**********************************************************************\n";
	out << "RUN " << run << "\n**********************************************************************\n";
	for (int i = 0; i < org.count; i++)
	{
		out << left << setw(15) << org.STR[i].pname << "\t"
			<< left << setw(10) << org.STR[i].cname << "\t"
			<< right << setw(7) << org.STR[i].plant_cost << "\t"
			<< right << setw(6) << setprecision(0) << noshowpoint << org.STR[i].quantity << "\t"
			<< right << setw(8) << setprecision(2) << org.STR[i].net_cost << "\t"
			<< right << setw(6) << setprecision(3) << org.STR[i].tax_rate << "\t"
			<< right << setw(7) << setprecision(2) << org.STR[i].purchase_tax << "\t"
			<< right << setw(7) << org.STR[i].discount << "\t"
			<< right << setw(9) << org.STR[i].total_cost << endl;
	}
	run++;
	return out;//returning object that invoked the function
}

/****************************************************************************************************************************/
//Name: destructor
//Decription: de-allocates all memory allocated to STR.  This will be the last function to be called (automatically by the compiler)
//before the program is exited.
/***************************************************************************************************************************/
order_class::~order_class()
{
	count = 0;
	size = 0;
	delete[] STR;
}
