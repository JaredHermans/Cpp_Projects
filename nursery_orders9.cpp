/************************************************************************************************************************
Jared Hermans

Description: Program takes nursery_stock.txt file as an input and prints it to an output file nursery_result30.txt. The 
program also allows the user to enter order fields to add them and calculate the remaining fields and allows the user to 
delete duplicate order fields.

*************************************************************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

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
	~order_class();																			//de-allocates all memory allocate to STR by operator new.
	bool is_Empty();																		//inline implementation
	bool is_full();																			//inline implementation
	int search(const string key);															//returns location of key if in STR; otherwise return -1
	void add();																				//adds a order record to STR
	void remove(const string key);															//removes all items in STR with a plant name that matches key.
	void double_size();
	void process();
	void print();																			//prints all the elements in STR to the screen
private:
	int count;
	int size;
	order_record* STR;
};



int main()
{
	order_class myOrders;																	//declaring order_class object myOrders; the default constructor is called automically.
	cout << "**********************************************************************\n";
	//Test 1:
	cout << "Test 1: Testing default construcor, double_size, process, is_full and print " << endl
		<< "Run 1:\n";
	myOrders.process();
	myOrders.print();
	cout << "End of Test 1" << endl;
	cout << "**********************************************************************\n";
	cout << "**********************************************************************\n";

	//Test 2:
	cout << "Test 2: Testing add, double_size, process, is_full, and print " << endl
		<< "Run 2\n";
	myOrders.add();																			//test case: pname = rose, cname = dade, plant cost = 1, quantity = 1 
	myOrders.print();
	cout << "End of Test 2" << endl;
	cout << "**********************************************************************\n";
	cout << "**********************************************************************\n";

	//Test 3:
	cout << "Test 3: Testing remove, is_Empty, search and print " << endl;
	cout << "Removing rose (Run 3)\n";
	myOrders.remove("rose");
	myOrders.print();
	cout << "Removing bergenia (Run 4)\n";
	myOrders.remove("bergenia");
	myOrders.print();
	cout << "Removing yarrow (Run 5)\n";
	myOrders.remove("yarrow");
	myOrders.print();
	cout << "Removing rose (Run 6)\n";
	myOrders.remove("rose");
	myOrders.print();
	cout << "End of Test 3" << endl;
	cout << "**********************************************************************\n";
	cout << "**********************************************************************\n";

	//Test 4:
	//destructor will be invoked when object myOrders goes out of scope
	cout << "Test 4: Destructor called" << endl;
	cout << "End of Test 4" << endl;
	cout << "**********************************************************************\n";
	cout << "**********************************************************************\n";

	return 0;
}




/************************************************************************************************************************************/
//Name: default constructor
//Decription: Reads the data file of purchase order information (plant name, county name, plant cost and quantity) into the dynamic array of order records, 
//STR. If the count become equal to the size the function double_size is called and the memory allocated to STR is doubled.
/************************************************************************************************************************************/
order_class::order_class()
{
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

/***********************************************************************************************************************************/
//Name: is_Empty
//Decription: returns true if STR is empty
/**********************************************************************************************************************************/
bool order_class::is_Empty()
{
	return count == 0;
}

/**********************************************************************************************************************************/
//Name: is_full 
//Decription: returns true if STR is full
/*********************************************************************************************************************************/
bool order_class::is_full()
{
	return count == size;
}

/**********************************************************************************************************************************/
//Name: search
//Decription: locates key in STR if it is there; otherwise -1 is returned
/*********************************************************************************************************************************/
int order_class::search(const string key)
{
	return -1;
}

/*********************************************************************************************************************************/
//Name: add
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
//Name: remove
//Decription: removes all order records in STR with a plant name field that matches key, if it is there.
/*******************************************************************************************************************************/
void order_class::remove(const string key)
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
		order_class::remove(key);
	}
}

/******************************************************************************************************************************/
//Name: double_size
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
//Name: process
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
//Name: print
//Decription: prints every field of every call_record in STR formatted to a file.
/***************************************************************************************************************************/
void order_class::print()
{
	ofstream out;
	out.open("nursery_result30.txt", fstream::app);
	static int run = 1;

	out.setf(ios::showpoint);														//Seting precision to 2 decimal places
	out.precision(2);
	out.setf(ios::fixed);

	out << "**********************************************************************\n";
	out << "RUN " << run << "\n**********************************************************************\n";
	for (int i = 0; i < count; i++)
	{
		out << left << setw(16) << STR[i].pname << "\t"
			<< left << setw(11) << STR[i].cname << "\t"
			<< right << setw(8) << STR[i].plant_cost << "\t"
			<< right << setw(7) << setprecision(0) << noshowpoint << STR[i].quantity << "\t"
			<< right << setw(9) << setprecision(2) << STR[i].net_cost << "\t"
			<< right << setw(7) << setprecision(3) << STR[i].tax_rate << "\t"
			<< right << setw(8) << setprecision(2) << STR[i].purchase_tax << "\t"
			<< right << setw(8) << STR[i].discount << "\t"
			<< right << setw(10) << STR[i].total_cost << endl;
	}

	run++;
	out.close();
}

/****************************************************************************************************************************/
//Name: destructor
//Decription: de-allocates all memory allocated to STR.  This will be the last function to be called (automatically by the compiler)
//before the program is exited.
/***************************************************************************************************************************/
order_class::~order_class()
{
	delete[] STR;
}
