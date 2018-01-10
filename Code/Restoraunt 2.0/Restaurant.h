/*
 * Orders.h
 *
 *  Created on: 04-Jul-2015
 *      Author: Shubham Kumar
 */


#ifndef RESTAURANT_H_
#define RESTAURANT_H_

#ifndef TOTAL_TABLES
#define TOTAL_TABLES 20
#endif

#include <vector>
#include <time.h>
#include <iostream>
#include <cstring>
#include <iomanip>
#include "Calculation.h"

#define ADMIN_ID (9999)
#define PASS ("password")

using namespace std;
class Restaurant {
private:
	class Order {
		public:

		int			_orderID;
		int			_productID;
		int			_tableNo;
		int			_quantity;
		int			_employeeID;
		struct tm	_time;
		bool		_isDelivered;
		int			_price;

		Order(int orderID, int productID, int tableNo, int quantity, int employeeID, int price) {
			this -> _orderID = orderID;
			this -> _productID = productID;
			this -> _tableNo = tableNo;
			this -> _employeeID = employeeID;
			this -> _quantity = quantity;

			time_t t = time(NULL);
			this -> _time = *localtime (&t);

			this -> _isDelivered = false;
			this -> _price = price;

		}

		std::string displayDate() {
			char buffer[20];
			strftime(buffer, 20, "%H:%M:%S %d-%m-%Y", &_time);
			return buffer;
		}

		void orderToStringPrint() {
			cout<<setw(9)<<_tableNo<<setw(9)<<_orderID<<setw(9)<<_productID<<setw(22)<<displayDate()
								<<setw(10)<<_isDelivered<<setw(6)<<_price<<endl;
		}
	};

	class Employee {
		public:

		int 		_empID;
		std::string _empName;
		std::string _empPassword;
		int 		_money;

		Employee(int empID, std::string empName, std::string empPassword) {
			this -> _empID = empID;
			this -> _empName = empName;
			this -> _empPassword = empPassword;
			this -> _money = 0;
		}

		void empToStringPrint() {
			cout<<setw(9)<<_empID<<setw(20)<<_empName<<endl;;
		}


	};

	vector<Order> _orderList;
	vector<Employee> _employeeList;
	bool _table[TOTAL_TABLES];

	int totalPriceCalulator(int);

public:
	static int orderInit;
	static int empInit;
	static void printOrderStringHeader();
	static void printEmpStringHeader();

	Calculation c;

	Restaurant();
	void clearTableOrders(int);
	bool payForOrder(int);
	bool placeNewOrder();
	void displayAllOrders();
	void displayAllEmployees();
	void displayAllOrders_ofTable(int);
	bool addNewEmployee();
	int authenticateEmp();
	int getEmpIndex(int);
	void displayEmptyTables();
	bool removeEmployee(int);
	bool clearEmpMoney(int);
	bool addRemoveEmpMoney(int);

};
/*
* Orders.cpp
*
*  Created on: 04-Jul-2015
*      Author: Shubham Kumar
*/
#include "Restaurant.h"

int Restaurant::orderInit = 3512;
int Restaurant::empInit = 4521;

Restaurant::Restaurant() {
	//constructor
	for (int i = 0; i<TOTAL_TABLES; i++) {
		_table[i] = false;
	}
}



void Restaurant::printOrderStringHeader() {
	cout << setw(9) << "TABLE No." << setw(9) << "ORDER ID" << setw(9) << "PRODUCT" << setw(22) << "ORDERING TIME"
		<< setw(10) << "DELIVERED" << setw(6) << "PRICE" << endl;

}

void Restaurant::printEmpStringHeader() {
	cout << setw(9) << "EMP ID" << setw(20) << "EMPLOYEE NAME" << endl;;
}


bool Restaurant::placeNewOrder() {
	cout << "Enter table number : ";
	int tableNo;
	cin >> tableNo;

	cout << "Enter product ID : ";
	int productID;
	cin >> productID;

	cout << "Enter Quantity : ";
	int quantity;
	cin >> quantity;

	string productName;

	int price = quantity * c.price_Calculator(productID, productName);
	if (price == 0) {
		cout << "Invalid Product ID";
		return (false);
	}

	int empID = this->authenticateEmp();

	if (empID == 0) {
		cout << " Invalid Employee ID ";
		return (false);
	}
	_table[tableNo] = true;
	this->_orderList.push_back(Order(orderInit, productID, tableNo, quantity, empID, price));

	cout << "Order of " << productName << " is successfully placed with OrderID : " << orderInit << " and price = Rs " << price << endl;
	orderInit++;
	return (true);
}

void Restaurant::displayAllOrders() {
	for (Order temp : _orderList) {
		temp.orderToStringPrint();
	}
}

void Restaurant::clearTableOrders(int tableNo) {
	vector<Order>::iterator it;
	it = _orderList.begin();
	while (it < _orderList.end()) {
		if ((*it)._tableNo == tableNo) {
			_orderList.erase(it);
			it = _orderList.begin();
		}
		else {
			it++;
		}
	}
	_table[tableNo] = false;

}

bool Restaurant::payForOrder(int tableNo) {

	int price = 0;
	cout << setw(9) << "ORDER ID" << setw(9) << "PRODUCT" << setw(6) << "QUANTITY" << setw(9) << "PRICE" << endl;
	vector<Order>::iterator it;
	for (it = _orderList.begin(); it < _orderList.end(); it++) {
		if ((*it)._tableNo == tableNo) {
			price += (*it)._price;
			cout << setw(9) << (*it)._orderID << setw(9) << (*it)._productID << setw(6) << (*it)._quantity << setw(9) << (*it)._price << endl;
		}
	}
	cout << "TOTAL PRICE : Rs " << price;

	cout << endl << "Choose your payment options. " << endl;;
	cout << " 1). Credit Card (VISA/MasterCard)" << endl;
	cout << " 2). Debit Card (VISA/MasterCard)" << endl;
	cout << " 3). By Cash" << endl;

	cout << " Input : ";
	int choice;
	cin >> choice;
	switch (choice) {

		case 1 || 2: {
			c.paymentThroughCard();
			this->clearTableOrders(tableNo);
			return (true);
		}
		case 3: {
			cout << "Please pay cash to the employee here";
			int index = getEmpIndex(authenticateEmp());
			if (index == -1) {
				return (false);
			}

			_employeeList.at(index)._money += price;
			this->clearTableOrders(tableNo);
			cout << "Payment Done!";
			return (true);
		}
		default:
			cout << "Invalid choice!" << endl;
			return (false);
	}
}

bool Restaurant::addNewEmployee() {
	cout << "Enter Employee name : ";
	string name;
	cin >> name;

	cout << "Create Password : ";
	string password;
	cin >> password;

	this->_employeeList.push_back(Employee(empInit, name, password));

	cout << "Employee successfully created with empID : " << empInit << " and Name : " << name;

	empInit++;
	return (true);
}

int Restaurant::getEmpIndex(int empID) {
	for (unsigned int i = 0; i <_employeeList.size(); i++) {
		if (_employeeList.at(i)._empID == empID) {
			return (i);
		}
	}
	return (-1);
}

int Restaurant::authenticateEmp() {
	cout << "Enter Employee ID : ";
	int empID;
	cin >> empID;

	cout << "Enter Password : ";
	string password;
	cin >> password;

	//admin
	if (empID == ADMIN_ID && password == PASS) {
		return (9999);
	}


	vector<Employee>::iterator it;
	for (it = _employeeList.begin(); it < _employeeList.end(); it++) {

		if ((*it)._empID == empID && (*it)._empPassword == password) {
			return ((*it)._empID);
		}
	}
	return (0);
}

int Restaurant::totalPriceCalulator(int tableNo) {
	int price = 0;
	vector<Order>::iterator it;
	for (it = _orderList.begin(); it < _orderList.end(); it++) {
		if ((*it)._tableNo == tableNo) {
			price += (*it)._price;
		}
	}
	return (price);
}

void Restaurant::displayEmptyTables() {
	cout << "EMPTY TABLES : ";
	for (int i = 0; i < TOTAL_TABLES; i++) {
		if (_table[i] == false) {
			cout << i << " ";
		}
	}

}

bool Restaurant::removeEmployee(int EmpID) {
	vector<Employee>::iterator it;
	it = _employeeList.begin();
	while (it < _employeeList.end()) {
		if ((*it)._empID == EmpID) {
			_employeeList.erase(it);
			return (true);
		}
		it++;
	}
	return (false);
}



bool Restaurant::clearEmpMoney(int EmpID) {
	vector<Employee>::iterator it;
	it = _employeeList.begin();
	while (it < _employeeList.end()) {
		if ((*it)._empID == EmpID) {
			(*it)._money = 0;
			return (true);
		}
		it++;
	}
	return (false);
}

bool Restaurant::addRemoveEmpMoney(int EmpID) {
	vector<Employee>::iterator it;
	it = _employeeList.begin();
	while (it < _employeeList.end()) {
		if ((*it)._empID == EmpID) {
			cout << "Total Balance : Rs " << (*it)._money << endl;
			cout << "Enter Money to be added(+) or removed(-) : ";
			int money;
			cin >> money;
			(*it)._money += money;
			cout << "Remaining balance : " << (*it)._money << endl;
			return (true);
		}
		it++;
	}
	return (false);
}

void Restaurant::displayAllOrders_ofTable(int tableNo) {
	for (Order temp : _orderList) {
		if (temp._tableNo == tableNo) {
			temp.orderToStringPrint();
		}
	}
}

void Restaurant::displayAllEmployees() {
	for (Employee temp : _employeeList) {
		temp.empToStringPrint();
	}
}

#endif /* RESTAURANT_H_ */
