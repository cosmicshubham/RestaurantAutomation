/*
 * Calculations.h
 *
 *  Created on: 04-Jul-2015
 *      Author: Shubham Kumar
 */

#ifndef CALCULATION_H_
#define CALCULATION_H_
#include <iostream>

#ifndef TOTAL_ITEMS
#define TOTAL_ITEMS 20
#endif

using namespace std;
class Calculation {

public:

	pair <string , int > p1[TOTAL_ITEMS];


	Calculation() {

	//  PRODUCT NAME								PRODUCT PRICE

		p1[0].first = "Samosa"; 				p1[0].second = 10;
		p1[1].first = "Venilla Icecream";	  	p1[1].second = 30;
		p1[2].first = "Pizza Mania";  			p1[2].second = 60;
		p1[3].first = "Imarti";		  			p1[3].second = 15;
		p1[4].first = "Gulaab Jaamun";  		p1[4].second = 12;
		p1[5].first = "Veg Momos";  			p1[5].second = 30;
		p1[6].first = "Chawmeen";	  			p1[6].second = 35;
		p1[7].first = "Dosa";		  			p1[7].second = 40;
		p1[8].first = "Burger";					p1[8].second = 30;
		p1[9].first = "Tikki";		  			p1[9].second = 25;
		p1[10].first = "Paani Poori";  			p1[10].second = 30;
		p1[11].first = "Colddrink";  			p1[11].second = 50;
		p1[12].first = "Double Cheese Pizza";  	p1[12].second = 120;
		p1[13].first = "French Fries";  		p1[13].second = 50;
		p1[14].first = "Fried Rice";  			p1[14].second = 35;
		p1[15].first = "Veg Rolls";  			p1[15].second = 30;
		p1[16].first = "Pastery";	  			p1[16].second = 35;
		p1[17].first = "Paneer Bread";  		p1[17].second = 30;
		p1[18].first = "Veg Hot Dog";  			p1[18].second = 30;
		p1[19].first = "Aloo Patty";  			p1[19].second = 15;

	}


	int price_Calculator(int productID, std::string& productName) {

		if (productID > 0 && productID < TOTAL_ITEMS) {
			productName = p1[productID].first;		return (p1[productID].second);
		}
		else {
			cout<<endl<<"Invalid Product ID"<<endl;
			productName = "Nothing";
			return (0);
		}
	}

	bool paymentThroughCard() {
		std::string cardNumber;
		cout<<"Enter 16 digit card number : ";
		cin>>cardNumber;

		int code;
		cout<<"Enter Code : ";
		cin>>code;

		cout<<"YOUR PAYMENT IS DONE"<<endl;

		return (true);
	}

	void displayMenu() {
		cout<<endl;
		cout<<setw(10)<<"PRODUCT ID"<<"|"<<setw(20)<<"PRODUCT NAME"<<"|"<<setw(8)<<"PRICE"<<endl;
		for (int i = 0; i < TOTAL_ITEMS; i++ ) {
			cout<<setw(10)<<i<<"|"<<setw(20)<<p1[i].first<<"|"<<setw(8)<<p1[i].second<<endl;
		}
		cout<<endl;
	}
};






#endif /* CALCULATION_H_ */
