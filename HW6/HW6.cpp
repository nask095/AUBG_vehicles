// HW6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <list>
#include <cstdlib>
#include <stack>

using namespace std;

#pragma region Vehicle
class Vehicle
{
private:
	string producer;
	string model;
	int year;
	bool Check_Year(int checkYear);
	bool Check_Producer(string checkProducer); //Introduces the list of producers and checks whether the user has inputed a producer from that list only.

public:
	Vehicle();
	virtual void addVehicle();
	virtual void addVehicleProducer(string producer);// These three functions are later used in the Spare_part class in order to store 
	virtual void addVehicleModel(string model);     // the previously inputed producer, model and year in the buffer, 
	virtual void addVehicleYear(string year);      // so we don't have to ask the user to input them again.
	string getProducer()
	{
		return producer;
	}
	void setProducer(string value)
	{
		producer = value;
	}
	string getModel()
	{
		return model;
	}
	int getYear()
	{
		return year;
	}


};

Vehicle::Vehicle()
{
	producer = "";
	model = "";
	year = 0;
}
void Vehicle::addVehicle() //Method to add a vehicle.
{
	string yearS;
	do
	{
		cout << "Producer: ";
		cin >> producer;
	} while (Check_Producer(producer) != true);

	cout << "\nModel: ";
	do
	{
		getline(cin, model);
	} while (model == "");
	{

	}
	do
	{
		cout << "\nYear: ";
		getline(cin, yearS);
		year = atoi(yearS.c_str());
	} while (Check_Year(year) != true);
}
void Vehicle::addVehicleProducer(string prod)
{
	std::istringstream buffer(prod);
	buffer >> producer;
}
void Vehicle::addVehicleModel(string mod)
{
	std::istringstream buffer2(mod);
	buffer2 >> model;
}
void Vehicle::addVehicleYear(string yr)
{
	std::istringstream buffer3(yr);
	buffer3 >> year;
}
bool Vehicle::Check_Year(int checkYear)
{
	if (checkYear > 1949 && checkYear < 2017)
	{
		return true;
	}
	else
	{
		cout << "\nThe year of production should be between 1950 and 2016.\nEnter year again.\n";
		return false;
	}
}
bool Vehicle::Check_Producer(string checkProducer)
{
	vector<string> Producers;
	Producers.push_back("Toyota");
	Producers.push_back("Nissan");
	Producers.push_back("Honda");
	Producers.push_back("Mazda");
	Producers.push_back("Audi");
	Producers.push_back("BMW");
	Producers.push_back("Mercedes");
	Producers.push_back("Ford");
	Producers.push_back("Citroen");
	Producers.push_back("Renault");
	Producers.push_back("KIA");
	for (int i = 0; i < Producers.size(); i++)
	{
		if (checkProducer == Producers.at(i))
		{
			return true;
		}
	}
	cout << producer << " is not in the list of producers.\nEnter again producer.\nPossible producers:\n";
	for (int i = 0; i < Producers.size(); i++)
	{
		cout << Producers.at(i) << "\n\n";
	}
	return false;
}
#pragma endregion

#pragma region Spare Part
class Spare_part
{
private:
	string ID, name, description, instruction, producer1, producer2, model1, model2;
	Vehicle* vehicle;
	double price;
	bool status; // 1 - new / 0 - recylced
	int replacement;


public:
	Spare_part();
	virtual bool addSparePart(vector<Vehicle*>&); //Adds a spare part. If there are no vehicles, outputs a message for the user to add a vehicle. Returns true if 
	virtual void addQuantity() {};                   // the user has successfully added a spare part.
	virtual void subtractQuantity() {};
	void substitute();
	virtual void Output() {};
	virtual int getQuantity() { return 0; };
	virtual string getLocation() { return ""; };
	double getPrice()
	{
		return price;
	}
	string getID()
	{
		return ID;
	}
	string getDescription()
	{
		return description;
	}
	bool getStatus()
	{
		return status;
	}
	int getReplacement()
	{
		return replacement;
	}
	string getName()
	{
		return name;
	}

	string getProducer1()
	{
		return producer1;
	}
	string getProducer2()
	{
		return producer2;
	}
	string getModel1()
	{
		return model1;
	}
	string getModel2()
	{
		return model2;
	}
	Vehicle getVehicle()
	{
		return *vehicle;
	}

	string getProducer()
	{
		return vehicle->getProducer();
	}
	string getModel()
	{
		return vehicle->getModel();
	}
	int getYear()
	{
		return vehicle->getYear();
	}
	string Warranty()
	{
		if (status == 1)
		{
			return "3 years";
		}
		else
		{
			return "3 months";
		}
	}
	virtual double Price()
	{
		return price + replacement * 20;
	}

};

Spare_part::Spare_part()
{
	ID = "";
	name = "";
	description = "";
	instruction = "";
	price = 0;
	replacement = 0;
	vehicle = new Vehicle;
}
bool Spare_part::addSparePart(vector<Vehicle*>& newModel)
{
	string yearS;
	string model, producer;
	int year;
	bool count = false;
	bool repeat = false;
	cout << "Producers:\n";
	for (int i = 0; i < newModel.size(); i++)
	{
		repeat = false;
		for (int j = 0; j < i; j++)
		{
			if (newModel.at(i)->getProducer() == newModel.at(j)->getProducer())
				repeat = true;

		}
		if (repeat == false)
		{
			cout << newModel.at(i)->getProducer() << "\n";
			count++;
		}
	}
	if (count == 0)
	{
		cout << "\nThere is no found vehicle. You should add the vehicle before adding spare parts\n";
		Sleep(7000);
		return false;

	}
	cout << "\nSelect Producer: ";
	cin >> producer;
	count = 0;
	cout << "\nModels:\n";
	for (int i = 0; i < newModel.size(); i++)
	{
		repeat = false;
		if (newModel.at(i)->getProducer() == producer)
		{
			for (int j = 0; j < i; j++)
			{
				if (newModel.at(i)->getModel() == newModel.at(j)->getModel())
					repeat = true;
			}
			if (repeat == false)
			{
				cout << newModel.at(i)->getModel() << "\n";
				count++;
			}

		}

	}
	if (count == 0)
	{
		cout << "\nThere is no found vehicle. You should add the vehicle before adding spare parts\n";
		Sleep(7000);
		return false;

	}
	cout << "\nSelect model: ";
	getline(cin, model);
	getline(cin, model);
	count = 0;
	cout << "\nYears:\n";
	for (int i = 0; i < newModel.size(); i++)
	{
		repeat = false;
		if (newModel.at(i)->getProducer() == producer && newModel.at(i)->getModel() == model)
		{
			for (int j = 0; j < i; j++)
			{
				if (newModel.at(i)->getYear() == newModel.at(j)->getYear() && newModel.at(i)->getModel() == newModel.at(j)->getModel())
					repeat = true;
			}
			if (repeat == false)
			{
				count++;
				cout << newModel.at(i)->getYear() << "\n";
			}
		}

	}
	if (count == 0)
	{
		cout << "\nThere is no found vehicle. You should add the vehicle before adding spare parts\n";
		Sleep(7000);
		return false;

	}
	do
	{
		cout << "\nSelect year: ";
		getline(cin, yearS);
		year = atoi(yearS.c_str());
		if (year < 1)
		{
			cout << "\nThe year should be positive integer.";
		}
	} while (year < 1);
	count = 0;
	for (int i = 0; i < newModel.size(); i++)
	{
		if (newModel.at(i)->getYear() == year)
		{
			count++;
		}
	}

	if (count == 0)
	{
		cout << "\nThere is no found vehicle. You should add the vehicle before adding spare parts\n";
		Sleep(7000);
		return false;

	}
	vehicle->addVehicleProducer(producer);
	vehicle->addVehicleModel(model);
	vehicle->addVehicleYear(yearS);
	std::cout << "\nID: ";
	getline(cin, ID);
	std::cout << "\nName of the part: ";
	getline(cin, name);
	std::cout << "\nDescription: ";
	getline(cin, description);
	std::cout << "\nInstructions: ";
	getline(cin, instruction);
	string priceS;
	do
	{
		std::cout << "\nPrice: ";
		getline(cin, priceS);
		price = atof(priceS.c_str());
		if (price <= 0)
		{
			cout << "\nWrong input. The price should be positive number.\n";
		}
	} while (price <= 0);


	string statusS;
	do
	{
		cout << "\nStatus(1 for new, 0 for recycled): ";
		getline(cin, statusS);
		if (statusS == "1")
		{
			status = true;
		}
		else if (statusS == "0")
		{
			status = false;
		}
		else
		{
			cout << "\n Wrong input. Enter 1 for new, enter 0 for recycled.";
		}
	} while (statusS != "1" && statusS != "0");

	string replacementS;
	do
	{
		cout << "\nReplacement: ";
		getline(cin, replacementS);
		replacement = atoi(replacementS.c_str());
		if (replacement<1)
		{
			cout << "\nWrong input. The replacement price should be positive number.\n";
		}

	} while (replacement <1);

	return true;
}

void Spare_part::substitute()
{
	//vector<string> subst;
	cout << "Part Name: ";
	getline(cin, name);
	cout << "\nOF producer: ";
	getline(cin, producer1);
	cout << "\nOF model: ";
	getline(cin, model1);
	cout << "\nCan be used for producer: ";
	getline(cin, producer2);
	cout << "\nfor model: ";
	getline(cin, model2);
}


#pragma endregion

#pragma region Vendor
class Vendor
{
private:
	string name;
	string address;
	string phone;
	list<string>delivery{ "Opel", "Ford", "Honda", "Toyota", "Nissan", "BMW", "Audi", "Mercedes", "Renault", "KIA" };

public:
	Vendor();
	virtual void addVendor();
	string getName()
	{
		return name;
	}
};

Vendor::Vendor()
{
	name = "";
	address = "";
	phone = "";
}

void Vendor::addVendor()
{
	cout << "\nName of the vendor: ";
	getline(cin, name);
	cout << "\nAdress of the vendor: ";
	getline(cin, address);
	cout << "\nPhone of the vendor: ";
	getline(cin, phone);
}
#pragma endregion


#pragma region AvailableSP
class AvailableSP : public Spare_part
{
private:
	int quantity;
	string location;

public:

	AvailableSP();
	virtual double Price();
	void Output();
	bool addSparePart(vector<Vehicle*>&);
	void addQuantity();
	void subtractQuantity();
	int getQuantity()
	{
		return quantity;
	}
	string getLocation()
	{
		return location;
	}
};
AvailableSP::AvailableSP()
{
	quantity = 0;
	location = "";
}
void AvailableSP::addQuantity() //Increases the quantity of a selected available spare part.
{
	string quantityS;
	int temp;
	do
	{
		std::cout << "Enter quantity: ";
		getline(cin, quantityS);
		temp = atoi(quantityS.c_str());
		if (temp <1)
		{
			cout << "\nWrong input. The quantity should be positive integer.\n";
		}
	} while (temp <1);
	quantity += temp;

}

void AvailableSP::subtractQuantity()
{
	string quantityS;
	int temp;
	do
	{
		std::cout << "Enter quantity: ";
		getline(cin, quantityS);
		temp = atoi(quantityS.c_str());
		if (temp > quantity)
		{
			cout << "\nThere are not enough spare parts\n";
		}
		if (temp <1)
		{
			cout << "\nWrong input. The quantity should be positive integer.\n";
		}
	} while (temp <1 || temp > quantity);
	quantity -= temp;
}
double AvailableSP::Price()
{
	return quantity*getPrice();
}

void AvailableSP::Output()
{
	bool stat = getStatus();
	string convert;
	if (stat == true)
		convert = "new";
	else convert = "recycled";
	cout << setw(10) << getName() << '|' << setw(5) << getID() << '|' << setw(7) << getPrice() << '|' << setw(10) << convert << '|' << setw(13) << getReplacement() << '|' << setw(20) << quantity << '|' << setw(15) << location << "\n";
}

bool AvailableSP::addSparePart(vector<Vehicle*>& newModel)
{
	if (Spare_part::addSparePart(newModel) == true)
	{
		string quantityS;
		do
		{
			cout << "\nAvailable quantity: ";
			getline(cin, quantityS);
			quantity = atoi(quantityS.c_str());
			if (quantity <1)
			{
				cout << "\nWrong input. The quantity should be positive integer.\n";
			}
		} while (quantity <1);

		cout << "\nAdd location: ";
		getline(cin, location);
		return true;
	}
	return false;
}
#pragma endregion

#pragma region ContractedSP
class ContractedSP : public Spare_part
{
private:
	Vendor* vendor;
	int time;
	double delivery_price;

public:
	ContractedSP();
	double Price();
	int Time();
	void Output();
	bool addSparePart(vector<Vehicle*>&);

};

ContractedSP::ContractedSP()
{
	time = 0;
	delivery_price = 0;
	vendor = new Vendor;
}


double ContractedSP::Price()
{
	return getPrice() + getReplacement() + delivery_price;
}

int ContractedSP::Time()
{
	return time;
}
bool ContractedSP::addSparePart(vector<Vehicle*>& newModel) //Adds information about the contracted spare parts.
{
	if (Spare_part::addSparePart(newModel) == true)
	{
		string timeS;
		do
		{
			cout << "\nHours of delivery: ";
			getline(cin, timeS);
			time = atoi(timeS.c_str());
			if (time <1)
			{
				cout << "\nWrong input. The time should be positive integer.\n";
			}
		} while (time <1);
		string delivery_priceS;
		do
		{
			cout << "\nDelivery Price: ";
			getline(cin, delivery_priceS);
			delivery_price = atof(delivery_priceS.c_str());
			if (delivery_price <= 0)
			{
				cout << "\nWrong input. The delivery price should be positive integer.\n";
			}
		} while (delivery_price <= 0);
		vendor->addVendor();
		return true;
	}
	return false;
}

void ContractedSP::Output() //Outputs the the contracted spare parts only.
{
	bool stat = getStatus();
	string convert;
	if (stat == true)
		convert = "new";
	else convert = "recycled";

	cout << setw(10) << getName() << '|' << setw(5) << getID() << '|' << setw(7) << getPrice() << '|' << setw(10) << convert << '|' << setw(13) << getReplacement() << '|' << setw(10) << vendor->getName() << '|' << setw(15) << time << '|' << setw(6) << Price();
}
#pragma endregion


bool searchSP(vector<Spare_part*>& SparePart, int &index, int mode, bool &finish)
{
	string yearS;
	string model, producer, partName;
	int year;
	bool count = false;
	bool repeat = false;
	cout << "Producers:\n";
	for (int i = 0; i < SparePart.size(); i++)
	{
		repeat = false;
		for (int j = 0; j < i; j++)
		{
			if (SparePart.at(i)->getProducer() == SparePart.at(j)->getProducer())
				repeat = true;

		}
		if (repeat == false)
		{
			cout << SparePart.at(i)->getProducer() << "\n";
			count++;
		}
	}
	if (count == 0)
	{
		cout << "\nThere is no found vehicle. You should add the vehicle and the spare parts\n";
		Sleep(7000);
		return false;

	}
	cout << "\nSelect Producer: ";
	cin >> producer;
	count = 0;
	cout << "\nModels:\n";
	for (int i = 0; i < SparePart.size(); i++)
	{
		repeat = false;
		if (SparePart.at(i)->getProducer() == producer)
		{
			for (int j = 0; j < i; j++)
			{
				if (SparePart.at(i)->getModel() == SparePart.at(j)->getModel())
					repeat = true;
			}
			if (repeat == false)
			{
				cout << SparePart.at(i)->getModel() << "\n";
				count++;
			}

		}

	}
	if (count == 0)
	{
		cout << "\nThere is no found vehicle. You should add the vehicle and the spare parts\n";
		Sleep(7000);
		return false;

	}
	cout << "\nSelect model: ";
	getline(cin, model);
	getline(cin, model);
	count = 0;
	cout << "\nYears:\n";
	for (int i = 0; i < SparePart.size(); i++)
	{
		repeat = false;
		if (SparePart.at(i)->getProducer() == producer && SparePart.at(i)->getModel() == model)
		{
			for (int j = 0; j < i; j++)
			{
				if (SparePart.at(i)->getYear() == SparePart.at(j)->getYear() && SparePart.at(i)->getModel() == SparePart.at(j)->getModel())
					repeat = true;
			}
			if (repeat == false)
			{
				count++;
				cout << SparePart.at(i)->getYear() << "\n";
			}
		}

	}
	if (count == 0)
	{
		cout << "\nThere is no found vehicle. You should add the vehicle and the spare parts\n";
		Sleep(7000);
		return false;

	}
	do
	{
		cout << "\nSelect year: ";
		getline(cin, yearS);
		year = atoi(yearS.c_str());
		if (year < 1)
		{
			cout << "\nThe year should be positive integer.";
		}
	} while (year < 1);

	if (mode == 0)
	{
		count = 0;
		cout << "\nParts:\n";
		for (int i = 0; i < SparePart.size(); i++)
		{
			repeat = false;
			if (SparePart.at(i)->getProducer() == producer && SparePart.at(i)->getModel() == model && SparePart.at(i)->getYear() == year)
			{
				for (int j = 0; j < i; j++)
				{
					if (SparePart.at(i)->getYear() == SparePart.at(j)->getYear() && SparePart.at(i)->getModel() == SparePart.at(j)->getModel() && SparePart.at(i)->getName() == SparePart.at(j)->getName())
						repeat = true;
				}
				if (repeat == false)
				{
					count++;
					cout << SparePart.at(i)->getName() << "\n";
				}
			}
		}

		if (count == 0)
		{
			cout << "\nThere is no found vehicle. You should add the vehicle and the spare parts\n";
			Sleep(7000);
			return false;

		}
		count = 0;
		cout << "\nSelect part: ";
		getline(cin, partName);
		for (int i = 0; i < SparePart.size(); i++)
		{
			if (SparePart.at(i)->getName() == partName && SparePart.at(i)->getProducer() == producer && SparePart.at(i)->getModel() == model && SparePart.at(i)->getYear() == year)
			{
				count++;
				index = i;
			}
		}

		if (count == 0)
		{
			cout << "\nThere is no found vehicle. You should add the vehicle and the spare parts\n";
			Sleep(7000);
			return false;

		}
	}
	else
	{
		count = 0;
		for (int i = 0; i < SparePart.size(); i++)
		{
			if (SparePart.at(i)->getYear() == year)
			{
				count++;
				index = i;
			}
		}

		if (count == 0)
		{
			cout << "\nThere is no found vehicle. You should add the vehicle and the spare parts\n";
			Sleep(7000);
			return false;

		}
	}
	finish = true;
}


void quicksort(vector<Spare_part*>& sparePart, int start, int end, int mid, bool(&check)[100])
{
	int beg = 0;
	int len = end;
	int par1, par2;
	for (int n = start, k = end; n < k; n++, k--)
	{
		do
		{
			par1 = n;
			if (sparePart.at(par1)->getPrice() < sparePart.at(mid)->getPrice())
			{
				n++;
			}
		} while (sparePart.at(par1)->getPrice() <sparePart.at(mid)->getPrice());

		do
		{
			par2 = k;
			if (sparePart.at(par2)->getPrice() > sparePart.at(mid)->getPrice())
			{
				k--;
			}
		} while (sparePart.at(par2)->getPrice() > sparePart.at(mid)->getPrice());


		swap(sparePart[par1], sparePart[par2]);
		bool temp;
		temp = check[par1];
		check[par1] = check[par2];
		check[par2] = temp;
		start = n;
	}
	if (start != end)
	{
		quicksort(sparePart, beg, start, start / 2, check);

	}
	else
	{
		beg = end;
	}
	if (start != len)
	{

		quicksort(sparePart, start + 1, len, start + (len - start) / 2, check);
	}
}


#pragma region BM
int BM(string text, string pattern)
{
	int decrement = 0;
	int check, check2;
	int move = 0;
	int match = 0;
	for (int i = pattern.length() - 1; i < text.length();)//start checking the description
	{
		move = 0;
		decrement = 0;
		do
		{
			check = i - decrement;
			check2 = pattern.length() - 1 - decrement;
			if (text[check] == pattern[check2])//if the characters are the same, move to the previous character
			{
				decrement++;
				if (decrement == pattern.length())//if there are no more previous characters in the patter, we have a match
				{
					match++;
				}
			}
			else
			{
				move = max(1, (pattern.length() - decrement - 1) - (pattern.find_last_of(text[check]) > pattern.length() - 1) ? 0 : pattern.find_last_of(text[check]));//determine how many characters to the right to move the pattern
			}
		} while (decrement<pattern.length() && move == 0);
		i += move;
		if (move == 0)
			i++;
	}
	return match;//returns the number of matches in the description
};
#pragma endregion

void header()
{
	cout << " -----------------------------------------------------------";
	cout << "\n";
	cout << "|                 AUBG Vehicles Spare Parts                 |";
	cout << "\n";
	cout << " -----------------------------------------------------------";
	cout << "\n";
}

#pragma region linkedList
struct node
{
	int number;
	node *next;
	string part;
};

bool isEmpty(node *head)
{
	if (head == NULL)
		return true;
	else return false;
}
void insertFirst(node *&head, node *&tail, int number, string part)
{
	node *temp = new node;
	temp->part = part;
	temp->number = number;
	temp->next = NULL;
	head = temp;
	tail = temp;
}
void insert(node *&head, node *&tail, int number, string part)
{
	bool status = false;
	if (isEmpty(head))
	{
		insertFirst(head, tail, number, part);
	}
	else
	{

		node *temp, *left, *right, *size;//nodes to manipulate the lists
		temp = new node;
		temp->part = part;
		temp->number = number;
		right = head;
		int count = 1;
		size = head;
		while (size != NULL)
		{
			if (temp->number < size->number)
			{
				count++;
				size = size->next;
			}
			else break;
		}
		left = right;
		if (count == 1)
		{
			temp->next = head;
			head = temp;
		}
		else
		{
			for (int i = 1; i < count; i++)//loop to find where the list should be inserted, in order to have sorted lists
			{
				left = right;
				right = right->next;
			}
			left->next = temp;//inserting the new list
			left = temp;
			left->next = right;
		}
	}
}
void remove(node *&head, node *&tail)
{
	head = NULL;
	tail = NULL;
}
void show(node *current)
{
	if (isEmpty(current))
	{
		cout << "The list is empty\n";
	}
	else
	{
		while (current != NULL)
		{
			cout << current->part << endl;
			current = current->next;
		}
	}
}

#pragma endregion

bool searchOptions(string producer, string model, string searchPart, int price, int replacement, vector<Spare_part*>& sparePart, vector <Spare_part*>& subst, bool result)
{
	stack<string> myStack;
	stack<string> search;
	string producers[200];
	string models[200];
	string parts[200];
	bool ASP[2];
	int positionProducer = 0, positionModel = 0, positionPart = 0, positionASP = 0;
	bool repeat2 = false;
	bool available = false;
	bool found = false;
	for (int i = 0; i < sparePart.size(); i++)
	{
		for (int n = 0; n < 200; n++)
		{
			if (sparePart.at(i)->getProducer() == producers[n])
				repeat2 = true;
		}
		if (repeat2 == false)
		{
			producers[positionProducer] = sparePart.at(i)->getProducer();
			myStack.push(sparePart.at(i)->getProducer());
			positionProducer++;
		}
		repeat2 = false;
	}
	while (!myStack.empty())
	{
		if (myStack.top() == producer)
		{
			myStack.pop();
			for (int i = 0; i < sparePart.size(); i++)
			{
				for (int n = 0; n < 200; n++)
				{
					if (sparePart.at(i)->getModel() == models[n])
						repeat2 = true;
				}
				if (repeat2 == false && sparePart.at(i)->getProducer() == producer)
				{
					models[positionModel] = sparePart.at(i)->getModel();
					myStack.push(sparePart.at(i)->getModel());
					positionModel++;
				}
				repeat2 = false;
				while (positionModel != 0)
				{
					if (myStack.top() == model)
					{
						myStack.pop();
						for (int i = 0; i < sparePart.size(); i++)
						{
							for (int n = 0; n < 200; n++)
							{
								if (sparePart.at(i)->getName() == parts[n])
									repeat2 = true;
							}
							if (repeat2 == false && sparePart.at(i)->getProducer() == producer && sparePart.at(i)->getModel() == model)
							{
								parts[positionPart] = sparePart.at(i)->getName();
								myStack.push(sparePart.at(i)->getName());
								positionPart++;
							}
							repeat2 = false;
						}
						while (positionPart != 0)
						{
							if (myStack.top() == searchPart)
							{
								myStack.pop();
								for (int i = 0; i < sparePart.size(); i++)
								{
									if (sparePart.at(i)->getQuantity()>0)
									{
										available = true;
										break;
									}
								}
								if (available)
								{
									
									for (int i = 0; i < sparePart.size(); i++)
									{
										if (sparePart.at(i)->getProducer() == producer && sparePart.at(i)->getModel() == model && sparePart.at(i)->getName() == searchPart && sparePart.at(i)->getPrice()<price && sparePart.at(i)->getReplacement()<replacement)
										{
											cout << "\n" << producer << setw(15) << model << setw(15) << searchPart << setw(15) << sparePart.at(i)->getPrice() << setw(5) << sparePart.at(i)->getReplacement();
											result = true;
										}
									}
									found = true;									
								}								
							}
							else
							{
								myStack.pop();
							}
							positionPart--;
						}
					}
					else
					{
						myStack.pop();
					}
					positionModel--;

				}
			}
		}
		else
		{
			myStack.pop();
		}
	}
	if (!found)
	{
		for (int i = 0; i < subst.size(); i++)
		{
			if (subst.at(i)->getProducer2() == producer && subst.at(i)->getModel2() == model && subst.at(i)->getName() == searchPart)
			{
				for (int j = 0; j < sparePart.size(); j++)
				{
					if (sparePart.at(j)->getProducer() == subst.at(i)->getProducer1() && sparePart.at(j)->getModel() == subst.at(i)->getModel1() && sparePart.at(j)->getName() == subst.at(i)->getName() && sparePart.at(j)->getQuantity()>0)
					{
						result=searchOptions(subst.at(i)->getProducer1(), subst.at(i)->getModel1(), searchPart, price, replacement, sparePart, subst, result);
					}
				}
			}
		}
	}
	if (!result)
	{
		cout << "\nNothing found."; 
	}
	return result;
}

int main()
{
#pragma region vars
	bool checkVector[100];//Used to determine which Output method to use(the one for Available spare parts or the one for Contracted spare parts.)
	int k = 0;
	::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);//Starts the console on full screen.(Doesn't work on older Windows versions.)
	vector <Vehicle*> newModel;
	vector <Spare_part*> sparePart;
	vector <Vendor*> newVendor;
	vector <Spare_part*> subst;
	string part, location;
	int choice, choice2;
	string choiceS = "", choice2S = "";
	bool repeat = false; //Used to filter the repeated elements(producer, model, year).
	int count = 0;
	string exit;
	int index = 0, mode = 0;
	bool finish = false;
	string pattern;
	int repetitions;
	node *head = NULL;
	node *tail = NULL;
	string producer, model, searchPart;
	stack<string> myStack;
	stack<string> search;
	int price, replacement;
	string priceS;
	string replacementS;
#pragma endregion
#pragma region menu
	do
	{
		do
		{
			system("CLS");
			header();
			cout << "                           MENU";
			cout << "\n";
			cout << "1) Add new vehicle";
			cout << "\n";
			cout << "2) Add new spare part";
			cout << "\n";
			cout << "3) Add new quantity of a spare part";
			cout << "\n";
			cout << "4) Calculate the cost of replacement";
			cout << "\n";
			cout << "5) Add new vendor";
			cout << "\n";
			cout << "6) List Spare Parts";
			cout << "\n";
			cout << "7) Request a spare part";
			cout << "\n";
			cout << "8) Search";
			cout << "\n";
			cout << "9) Add substitutions";
			cout << "\n";
			cout << "10) Sort";
			cout << "\n";
			cout << "11) Search in descriptions";
			cout << "\n";
			cout << "12) Search repair option";
			cout << "\n";
			cout << "0) EXIT";
			cout << "\n";
			cout << "\n";

			cout << "Choice: ";
			getline(cin, choiceS);
			choice = atoi(choiceS.c_str());
			if (choice<0 || choice > 12)
			{
				cout << "There is no option with number " << choiceS << "\nPlease select option number between 0 and 12";
				Sleep(3000);
			}
		} while (choice<0 || choice > 12);
		choice = atoi(choiceS.c_str());
#pragma endregion
		switch (choice)
		{
#pragma region case1
		case 1:
			system("CLS");
			header();
			cout << "                        ADD VEHICLE";
			cout << "\n";
			newModel.push_back(new Vehicle);
			newModel.back()->addVehicle();
			cout << "Vehicle is successfully added";
			cout << "\n\nEnter 0 to go back to the menu\n";
			do
			{
				getline(cin, exit);
			} while (exit != "0");
			break;
#pragma endregion
#pragma region case2
		case 2:
			system("CLS");
			header();
			cout << "                       ADD SPARE PART";
			cout << "\n";
			int temp;
			if (newModel.empty())
			{
				cout << "\nThere are no added vehicles.";
				Sleep(2000);
				break;
			}
			cout << "\nPress 1 to add available spare parts\nPress 2 to add contracted spare parts\nPress 0 to go back.\n";
			do
			{
				cout << "\nChoice: ";
				cin >> temp;
				if (temp<0 || temp>2)
				{
					system("CLS");
					header();
					cout << "                        ADD SPARE PART";
					cout << "\n";
					cout << "\nWrong input\nPress 1 to add available spare parts\nPress 2 to add contracted spare parts\nPress 0 to go back.\n";
				}
			} while (temp<0 || temp>2);
			if (temp == 1)
			{
				sparePart.push_back(new AvailableSP());
				system("CLS");
				header();
				cout << "                  ADD AVAILABLE SPARE PART";
				cout << "\n";
				sparePart.back()->addSparePart(newModel);
				if (sparePart.at(sparePart.size() - 1)->getName() == "")//Prevents the input of empty vector.
				{
					sparePart.pop_back();
				}
				else
				{
					checkVector[k] = 0;
					k++;
					cout << "Part is successfully added";
					Sleep(2000);
				}
				break;
			}
			else if (temp == 2)
			{
				sparePart.push_back(new ContractedSP());
				system("CLS");
				header();
				cout << "                  ADD CONTRACTED SPARE PART";
				cout << "\n";
				sparePart.back()->addSparePart(newModel);
				if (sparePart.at(sparePart.size() - 1)->getName() == "") //Prevents the input of empty vector.
				{
					sparePart.pop_back();
				}
				else
				{
					checkVector[k] = 1;
					k++;
					cout << "Part is successfully added";
					Sleep(2000);
				}
				break;
			}
			break;
#pragma endregion
#pragma region case3
		case 3:
			system("CLS");
			header();
			cout << "                      ADD NEW QUANTITY";
			cout << "\n";
			if (sparePart.empty())
			{
				cout << "\nThere are no spare parts.";
				Sleep(2000);
				break;
			}
			count = 0;
			cout << "\nParts:\n";
			for (int i = 0; i < sparePart.size(); i++)
			{
				if (checkVector[i] == 0)
				{
					count++;
					cout << sparePart.at(i)->getName() << "\n";
				}
			}
			if (count != 0)
			{
				cout << "\nChoose part:";
				getline(cin, part);
				count = 0;
				for (int i = 0; i < sparePart.size(); i++)
				{
					if (checkVector[i] == 0)
					{
						if (sparePart.at(i)->getName() == part)
						{
							cout << "\nSpare parts at the moment: " << sparePart.at(i)->getQuantity() << '\n';
							sparePart.at(i)->addQuantity();
							cout << "\nTotal Spare parts: " << sparePart.at(i)->getQuantity();
							Sleep(2000);
							count++;
							break;
						}
					}
				}
				if (count == 0)
				{
					cout << "\nThere is no part with this name.\n";
					Sleep(2000);
				}
			}
			else
			{
				cout << "\nThere are no spare parts.";
				Sleep(2000);
				break;
			}
			break;
#pragma endregion
#pragma region case4
		case 4:
			system("CLS");
			header();
			cout << "                     COST OF REPLACEMENT";
			cout << "\n";
			if (sparePart.empty())
			{
				cout << "\nThere are no spare parts.";
				Sleep(2000);
				break;
			}
			cout << "\nParts:\n";
			for (int i = 0; i < sparePart.size(); i++)
			{
				cout << sparePart.at(i)->getName() << "\n";

			}
			cout << "\nChoose part:";
			getline(cin, part);
			count = 0;
			for (int i = 0; i < sparePart.size(); i++)
			{
				if (sparePart.at(i)->getName() == part)
				{
					cout << "\nThe cost for replacement of part " << part << " is: ";
					cout << sparePart.at(i)->Spare_part::Price();
					count++;
				}
			}
			if (count == 0)
			{
				cout << "No parts were found.";
			}
			cout << "\n\nEnter 0 to go back to the menu\n";
			do
			{
				getline(cin, exit);
			} while (exit != "0");
			break;
#pragma endregion
#pragma region case5
		case 5:
			system("CLS");
			header();
			cout << "                        ADD VENDOR";
			cout << "\n";
			newVendor.push_back(new Vendor);
			newVendor.back()->addVendor();
			cout << "\nVendor is added.\n";
			Sleep(2000);
			break;
#pragma endregion
#pragma region case6
		case 6:
			system("CLS");
			header();
			cout << "                       LIST SPARE PARTS";
			cout << "\n";
			cout << "Enter 1 to list available spare parts\nEnter 2 to list contracted spare parts.\n";
			do
			{
				cin >> temp;
				if (temp != 2 && temp != 1)
				{
					system("CLS");
					cout << "\nWrong input\nEnter 1 to list available spare parts\nEnter 2 to list contracted spare parts.\n";
				}
			} while (temp != 1 && temp != 2);
			if (temp == 1)
			{
				cout << "\n" << setw(10) << "Name" << '|' << setw(5) << "ID" << '|' << setw(7) << "Price" << '|' << setw(10) << "Status" << '|' << setw(13) << "Replacement" << '|' << setw(20) << "Available quantity" << '|' << setw(15) << "Location\n";
				for (int i = 0; i < sparePart.size(); i++)
				{
					if (checkVector[i] == 0)
						sparePart.at(i)->Output();
				}
			}
			else
			{
				cout << "\n" << setw(10) << "Name" << '|' << setw(5) << "ID" << '|' << setw(7) << "Price" << '|' << setw(10) << "Status" << '|' << setw(13) << "Replacement" << '|' << setw(10) << "Vendor" << '|' << setw(15) << "Delivery Time" << '|' << setw(6) << "Cost\n";
				for (int i = 0; i < sparePart.size(); i++)
				{
					if (checkVector[i] == 1)
						sparePart.at(i)->Output();
				}
			}

			cout << "\n\nEnter 0 to go back to the menu\n";
			do
			{
				getline(cin, exit);
			} while (exit != "0");
			break;
#pragma endregion
#pragma region case7
		case 7:
			system("CLS");
			header();
			cout << "                     Request Spare Part";
			cout << "\n";
			if (sparePart.empty())
			{
				cout << "\nThere are no spare parts.";
				Sleep(2000);
				break;
			}
			searchSP(sparePart, index, 0, finish);//calling method, so the user can choose the producer, model, year and name for the requested spare part
			if (finish)
			{
				system("CLS");
				cout << "\n" << setw(10) << "Name" << '|' << setw(5) << "ID" << '|' << setw(7) << "Price" << '|' << setw(10) << "Status" << '|' << setw(13) << "Replacement" << '|' << setw(20) << "Available quantity" << '|' << setw(15) << "Location\n";
				count = 0;
				for (int i = 0; i < sparePart.size(); i++)
				{
					if (checkVector[i] == 0 && sparePart.at(i)->getName() == sparePart.at(index)->getName() && sparePart.at(i)->getProducer() == sparePart.at(index)->getProducer() && sparePart.at(i)->getModel() == sparePart.at(index)->getModel() && sparePart.at(i)->getYear() == sparePart.at(index)->getYear())//checking if there are available spare parts
					{
						sparePart.at(i)->Output();
						count++;
					}
				}
				if (count != 0)
				{
					cout << "\nChoose spare part ID: ";
					getline(cin, part);
					cout << "\nChoose location: ";
					getline(cin, location);
					count = 0;
					for (int i = 0; i < sparePart.size(); i++)
					{
						if (checkVector[i] == 0)
						{
							if (sparePart.at(i)->getID() == part && sparePart.at(i)->getLocation() == location && sparePart.at(i)->getQuantity()>0 && sparePart.at(i)->getProducer() == sparePart.at(index)->getProducer() && sparePart.at(i)->getModel() == sparePart.at(index)->getModel() && sparePart.at(i)->getYear() == sparePart.at(index)->getYear())//checking if there are available spare parts
							{
								int temp = sparePart.at(i)->getQuantity();
								cout << "\nSpare parts at the moment: " << sparePart.at(i)->getQuantity() << '\n';
								sparePart.at(i)->subtractQuantity();
								if (temp != sparePart.at(i)->getQuantity())
								{
									cout << "\The request is successfull\nRemaining Spare parts: " << sparePart.at(i)->getQuantity();

								}
								Sleep(2000);
								count++;
								break;
							}
						}
					}
				}
				if (count == 0)
				{
					cout << "\nThere is no spare part.\n";
					Sleep(2000);
				}
			}
			finish = false;
			break;
#pragma endregion
#pragma region case8
		case 8:
			index = 0;
			do
			{
				system("CLS");
				header();
				cout << "		                  Search";
				cout << "\n";
				cout << "1) Available original new parts\n";
				cout << "2) Substitute original part\n";
				cout << "3) Delivery contracted original part\n";
				cout << "4) Second hand part\n";
				cout << "0) Back\n";
				cout << "\nChoice: ";
				getline(cin, choice2S);
				choice2 = atoi(choice2S.c_str());
				if (choice2<0 || choice2>4)
				{
					cout << "There is no option with number " << choice2S << "\nPlease select option number between 0 and 4";
					Sleep(3000);
				}

			} while (choice2<0 || choice2>4);
			switch (choice2)
			{
			case 1:
				system("CLS");
				searchSP(sparePart, index, 1, finish);//searching for producer, model and year
				if (finish)
				{
					system("CLS");
					cout << "\n" << setw(10) << "Name" << '|' << setw(5) << "ID" << '|' << setw(7) << "Price" << '|' << setw(10) << "Status" << '|' << setw(13) << "Replacement" << '|' << setw(20) << "Available quantity" << '|' << setw(15) << "Location" << '|' << setw(10) << "Warranty\n";

					for (int i = 0; i < sparePart.size(); i++)
					{
						if (checkVector[i] == 0 && sparePart.at(i)->getProducer() == sparePart.at(index)->getProducer() && sparePart.at(i)->getModel() == sparePart.at(index)->getModel() && sparePart.at(i)->getYear() == sparePart.at(index)->getYear() && sparePart.at(i)->getStatus())//check if there are results from the user's search
						{
							sparePart.at(i)->Output();
							cout << "|  " << sparePart.at(i)->Warranty();
						}
					}
					cout << "\n\nEnter 0 to go back to the menu\n";
					do
					{
						getline(cin, exit);
					} while (exit != "0");
				}
				finish = false;
				break;
			case 2:
				system("CLS");
				searchSP(sparePart, index, 0, finish);//search for producer, model, year and spare part
				if (finish)
				{
					count = 0;
					system("CLS");
					cout << "Possible parts for substitution:";
					for (int i = 0; i < subst.size(); i++)//loop to find spare parts that can be used as substitutes. The parts, which can be used as substitutes, first should be defined in the option Add Substitutions
					{
						if (subst.at(i)->getProducer2() == sparePart.at(index)->getProducer() && subst.at(i)->getModel2() == sparePart.at(index)->getModel() && subst.at(i)->getName() == sparePart.at(index)->getName())
						{
							for (int j = 0; j < sparePart.size(); j++)
							{
								if (sparePart.at(j)->getProducer() == subst.at(i)->getProducer1() && sparePart.at(j)->getModel() == subst.at(i)->getModel1() && sparePart.at(j)->getName() == subst.at(i)->getName() && sparePart.at(j)->getStatus() && sparePart.at(j)->getQuantity()>0)
								{
									cout << "\n\nProducer: ";
									cout << subst.at(i)->getProducer1();
									cout << "\nModel: ";
									cout << subst.at(i)->getModel1();
									cout << "\nPrice: ";
									cout << sparePart.at(j)->getPrice();
									cout << "\nWarranty: ";
									cout << sparePart.at(j)->Warranty();
									count++;
								}
							}

						}
					}

					if (count == 0)
					{
						cout << "\nThere are no available spare parts.";
						Sleep(2000);
					}

					cout << "\n\nEnter 0 to go back to the menu\n";
					do
					{
						getline(cin, exit);
					} while (exit != "0");
				}
				finish = false;
				break;
			case 3:
				system("CLS");
				searchSP(sparePart, index, 1, finish);//search for producer, model and year
				if (finish)
				{
					system("CLS");
					cout << "\n" << setw(10) << "Name" << '|' << setw(5) << "ID" << '|' << setw(7) << "Price" << '|' << setw(10) << "Status" << '|' << setw(13) << "Replacement" << '|' << setw(10) << "Vendor" << '|' << setw(15) << "Delivery Time" << '|' << setw(6) << "Cost" << '|' << setw(10) << "Warranty\n";

					for (int i = 0; i < sparePart.size(); i++)
					{
						if (checkVector[i] == 1 && sparePart.at(i)->getProducer() == sparePart.at(index)->getProducer() && sparePart.at(i)->getModel() == sparePart.at(index)->getModel() && sparePart.at(i)->getYear() == sparePart.at(index)->getYear() && sparePart.at(i)->getStatus())//checking for results from the search
						{
							sparePart.at(i)->Output();
							cout << "|  " << sparePart.at(i)->Warranty();
						}
					}
					cout << "\n\nEnter 0 to go back to the menu\n";
					do
					{
						getline(cin, exit);
					} while (exit != "0");
				}
				finish = false;
				break;
			case 4:
				system("CLS");
				searchSP(sparePart, index, 1, finish);//search for produced, model and year
				if (finish)
				{
					system("CLS");
					cout << "AVAILABLE SPARE PARTS:";
					cout << "\n" << setw(10) << "Name" << '|' << setw(5) << "ID" << '|' << setw(7) << "Price" << '|' << setw(10) << "Status" << '|' << setw(13) << "Replacement" << '|' << setw(20) << "Available quantity" << '|' << setw(15) << "Location" << '|' << setw(10) << "Warranty\n";

					for (int i = 0; i < sparePart.size(); i++)
					{
						if (checkVector[i] == 0 && sparePart.at(i)->getProducer() == sparePart.at(index)->getProducer() && sparePart.at(i)->getModel() == sparePart.at(index)->getModel() && sparePart.at(i)->getYear() == sparePart.at(index)->getYear() && !sparePart.at(i)->getStatus())//checking for results
						{
							sparePart.at(i)->Output();
							cout << "|  " << sparePart.at(i)->Warranty();
						}
					}
					cout << "\nCONTRACTED SPARE PARTS";
					cout << "\n" << setw(10) << "Name" << '|' << setw(5) << "ID" << '|' << setw(7) << "Price" << '|' << setw(10) << "Status" << '|' << setw(13) << "Replacement" << '|' << setw(10) << "Vendor" << '|' << setw(15) << "Delivery Time" << '|' << setw(6) << "Cost" << '|' << setw(10) << "Warranty\n";

					for (int i = 0; i < sparePart.size(); i++)
					{
						if (checkVector[i] == 1 && sparePart.at(i)->getProducer() == sparePart.at(index)->getProducer() && sparePart.at(i)->getModel() == sparePart.at(index)->getModel() && sparePart.at(i)->getYear() == sparePart.at(index)->getYear() && !sparePart.at(i)->getStatus())//checking for results
						{
							sparePart.at(i)->Output();
							cout << "|  " << sparePart.at(i)->Warranty();
						}
					}
					cout << "\n\nEnter 0 to go back to the menu\n";
					do
					{
						getline(cin, exit);
					} while (exit != "0");
				}
				finish = false;
				break;
			case 0:
				break;
			}
			break;
#pragma endregion
#pragma region case9
		case 9:

			do
			{
				do
				{
					system("CLS");
					cout << "Press 1 to add substitution\nPress 0 to go back\nChoice: ";
					getline(cin, exit);
				} while (exit != "0" && exit != "1");
				if (exit == "1")
				{
					//adding database of parts, which can be used as substitutes
					subst.push_back(new Spare_part);
					subst.back()->substitute();
					cout << "\nThe substitute is added.\n";
					Sleep(2000);
				}
			} while (exit != "0");
			break;
#pragma endregion
#pragma region case10
		case 10:
			if (sparePart.empty())
			{
				cout << "\nThere are no spare parts.";
				Sleep(2000);
				break;
			}
			quicksort(sparePart, 0, sparePart.size() - 1, (sparePart.size() - 1) / 2, checkVector);
			cout << "The spare parts are sorted. To view them select option \"List Spare Parts\"\n";
			Sleep(4000);
			break;
#pragma endregion
#pragma region case11
		case 11:
			system("CLS");
			if (sparePart.empty())
			{
				cout << "\nThere are no spare parts.";
				Sleep(2000);
				break;
			}
			header();
			cout << "	           Search for description";
			cout << "\n";
			cout << "Search description: ";
			getline(cin, pattern);
			count = 0;
			for (int i = 0; i < sparePart.size(); i++)
			{
				repetitions = BM(sparePart.at(i)->getDescription(), pattern);
				if (repetitions != 0)
				{
					count++;
					insert(head, tail, repetitions, sparePart.at(i)->getName());
				}
			}
			if (count == 0)
			{
				cout << "\nThere is no spare part.\n";
				Sleep(2000);
			}
			else
			{
				show(head);
				cout << "\n\nEnter 0 to go back to the menu\n";
				do
				{
					getline(cin, exit);
				} while (exit != "0");
			}
			remove(head, tail);
			break;
#pragma endregion

#pragma region case12
		case 12:
			myStack.empty();
			system("CLS");
			if (sparePart.empty())
			{
				cout << "\nThere are no spare parts.";
				Sleep(2000);
				break;
			}
			header();
			cout << "	           Search repair option";
			cout << "\n";
			cout << "Producer: ";
			getline(cin, producer);
			cout << "\nModel: ";
			getline(cin, model);
			cout << "\nSpare part: ";
			getline(cin, searchPart);
			do
			{
				cout << "\nPrice: ";
				getline(cin, priceS);
				price = atof(priceS.c_str());
				if (price <= 0)
				{
					cout << "\nWrong input. The price should be positive number.\n";
				}
			} while (price <= 0);
			do
			{
				cout << "\nReplacement: ";
				getline(cin, replacementS);
				replacement = atoi(replacementS.c_str());
				if (replacement<1)
				{
					cout << "\nWrong input. The replacement price should be positive number.\n";
				}

			} while (replacement <1);
			cout << "\nProducer" << setw(15) << "Model" << setw(15) << "Part" << setw(15) << "Price" << setw(5) << "Time";
			searchOptions(producer, model, searchPart, price, replacement, sparePart, subst, false);

			
			cout << "\n\nEnter 0 to go back to the menu\n";
			do
			{
				getline(cin, exit);
			} while (exit != "0");
			break;
#pragma endregion
		case 0:
			break;
		}


	} while (choice != 0);
	return 0;
}

