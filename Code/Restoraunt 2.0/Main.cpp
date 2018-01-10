/*
 * Main.cpp
 *
 *  Created on: 04-Jul-2015
 *      Author: Shubham Kumar
 */
#include <iostream>
#include "Restaurant.h"

using namespace std;


int main(int argc, char *argv[]) {

	Restaurant o1;
	do {
		cout<<endl<<"======================================";
		cout<<endl<<"-------  SK RESTAURANT PROGRAM -------";
		cout<<endl<<"======================================";
		cout<<endl;

		cout<<"01). Customer : Place New Order"<<endl;
		cout<<"02). Customer : Payment"<<endl;

		cout<<endl;
		cout<<"06). Employee : Display Empty Tables"<<endl;
		cout<<"07). Employee : Display All Orders of a table"<<endl;
		cout<<"08). Employee : Display All Orders of restaurant"<<endl;

		cout<<endl;
		cout<<"11). Admin    : Add New Employee"<<endl;
		cout<<"12). Admin    : Remove an Employee"<<endl;
		cout<<"13). Admin    : Clear Employee Money"<<endl;
		cout<<"14). Admin    : Add/Remove Employee Money"<<endl;
		cout<<"15). Admin    : View all Employees"<<endl;

		cout<<"20). Exit Program"<<endl;

		cout<<endl<<"Enter your choice : ";
		int choice;
		cin>>choice;
		switch (choice) {
		case 1: {
			cout<<endl<<"----- MENU -----"<<endl;
			o1.c.displayMenu();
			cout<<endl<<" Enter Order Details ....."<<endl;
			o1.placeNewOrder();
			break;
		}
		case 2: {
			cout<<"Enter table number : ";
			int tableNo;
			cin>>tableNo;
			o1.payForOrder(tableNo);
			break;
		}
		case 6: {
			cout<<"--------------------"<<endl;
			cout<<"Login -:"<<endl;
			if (o1.authenticateEmp() == 0) {
				cout<<"Invalid Employee details, Access Denied!"<<endl;
				break;
			}
			cout<<"--------------------"<<endl;
			o1.displayEmptyTables();
			break;
		}
		case 7: {
			cout<<"--------------------"<<endl;
			cout<<"Login -:"<<endl;
			if (o1.authenticateEmp() == 0) {
				cout<<"Invalid Employee details, Access Denied!"<<endl;
				break;
			}
			cout<<"--------------------"<<endl;
			cout<<"Enter table number : ";
			int tableNo;
			cin>>tableNo;
			o1.printOrderStringHeader();
			o1.displayAllOrders_ofTable(tableNo);
			break;
		}
		case 8: {
			cout<<"--------------------"<<endl;
			cout<<"Login -:"<<endl;
			if (o1.authenticateEmp() == 0) {
				cout<<"Invalid Employee details, Access Denied!"<<endl;
				break;
			}
			cout<<"--------------------"<<endl;
			o1.printOrderStringHeader();
			o1.displayAllOrders();
			break;
		}
		case 11: {
			cout<<"--------------------"<<endl;
			cout<<"Login -:"<<endl;
			if (o1.authenticateEmp() != 9999) {
				cout<<"Invalid admin details, Access Denied!"<<endl;
				break;
			}
			cout<<"--------------------"<<endl;
			o1.addNewEmployee();
			break;
		}
		case 12: {
			cout<<"--------------------"<<endl;
			cout<<"Login -:"<<endl;
			if (o1.authenticateEmp() != 9999) {
				cout<<"Invalid admin details, Access Denied!"<<endl;
				break;
			}
			cout<<"--------------------"<<endl;
			cout<<"Enter Employee ID : ";
			int empID;
			cin>>empID;
			if (!o1.removeEmployee(empID)) {
				cout<<"Invalid Employee ID"<<endl;
				break;
			}
			cout<<"Employee removed"<<endl;
			break;
		}
		case 13: {
			cout<<"--------------------"<<endl;
			cout<<"Login -:"<<endl;
			if (o1.authenticateEmp() != 9999) {
				cout<<"Invalid admin details, Access Denied!"<<endl;
				break;
			}
			cout<<"--------------------"<<endl;
			cout<<"Enter Employee ID : ";
			int empID;
			cin>>empID;
			if (!o1.clearEmpMoney(empID)) {
				cout<<"Invalid Employee ID"<<endl;
				break;
			}
			cout<<"Employee Money Cleared"<<endl;
			break;
		}
		case 14: {
			cout<<"--------------------"<<endl;
			cout<<"Login -:"<<endl;
			if (o1.authenticateEmp() != 9999) {
				cout<<"Invalid admin details, Access Denied!"<<endl;
				break;
			}
			cout<<"--------------------"<<endl;
			cout<<"Enter Employee ID : ";
			int empID;
			cin>>empID;
			if (!o1.addRemoveEmpMoney(empID)) {
				cout<<"Invalid Employee ID"<<endl;
				break;
			}
			cout<<"Done!"<<endl;
			break;
		}
		case 15: {
			cout<<"--------------------"<<endl;
			cout<<"Login -:"<<endl;
			if (o1.authenticateEmp() != 9999) {
				cout<<"Invalid admin details, Access Denied!"<<endl;
				break;
			}
			cout<<"--------------------"<<endl;
			o1.printEmpStringHeader();
			o1.displayAllEmployees();
			break;
		}

		case 20:
			cout<<"Exiting...";

			return 0;
		default:
			break;
		}

		cout<<endl<<"Press any key to continue......"<<endl;

	} while (true);


	return 0;



}


