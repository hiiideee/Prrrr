//
//  main.cpp
//  Team Project
//
//  Created by Elizabeth Zhang on 4/24/18.
//  Copyright © 2018 Elizabeth Zhang. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "GetData.hpp"
#include "BootStrapping.h"
//#include "Group.h"
using namespace std;

int main(int argc, const char * argv[]) {

	Market Spy("SPY", "2017-09-01", "2018-04-27", 0, 0);
	string filename = "stocks.txt";
	TickerBook StockList;
	GetTickerList(StockList, filename);
	GetStockPrice(StockList);
	GetSPYPrice(Spy);

	TickerBook group1;
	TickerBook group2;
	TickerBook group3;
	double threshold = 0.1;
	StockList.Divide(threshold, &group1, &group2, &group3);

	cout << "The Beat Group has " << group1.BookPage.size() << " Stocks" <<endl;
	cout << "The Meet Group has " << group2.BookPage.size() << " Stocks" <<endl;
	cout << "The Miss Group has " << group3.BookPage.size() << " Stocks"<< endl;	





/*	cout << "The Beat Group:" << endl;
	for (auto ii = group1.BookPage.begin(); ii != group1.BookPage.end(); ii++) {
		auto itt = group1.Book.find(*ii);
		for (int t = 0; t < 90; t++) {
			cout << itt->first << "'s Return at time " << t << " is " << itt->second.getReturns(t) << endl;
		}
	}
	*/
	cout << "The Meet Group:" << endl;
	for (auto ii1 = group2.BookPage.begin(); ii1 != group2.BookPage.end(); ii1++) {
		auto itt1 = group2.Book.find(*ii1);
		for (int t1 = 0; t1 < 90; t1++) {
			cout << itt1->first << "'s Price at time " << t1 << " is " << itt1->second.getPrices(t1) << endl;
			cout << itt1->first << "'s Return at time " << t1 << " is " << itt1->second.getReturns(t1) << endl;
		}
	}
/*
	cout << "The Miss Group:" << endl;
	for (auto ii2 = group3.BookPage.begin(); ii2 != group3.BookPage.end(); ii2++) {
		auto itt2 = group3.Book.find(*ii2);
		for (int t2 = 0; t2 < 57; t2++) {
			cout << itt2->first << "'s Return at time " << t2 << " is " << itt2->second.getReturns(t2) << endl;
//			cout << itt2->first << "'s Price at time " << t2 << " is " << itt2->second.getPrices(t2) << endl;
		}
	}


	Bootstrapping Boot1(threshold, 50), Boot2(threshold, 50), Boot3(threshold, 50);
	Boot1.run(&Spy, &group1);
	Boot2.run(&Spy, &group2);
	Boot3.run(&Spy, &group3);
	cout << "sssssssssssssssssssss" << endl;
	for (int tt = 0; tt < 90; tt++)
		cout << Boot1.getAARlist()[tt] << endl;
	cout << "sssssssssssssssssssss" << endl;
	cout << "sssssssssssssssssssss" << endl;
	for (int tt = 0; tt < 90; tt++)
		cout << Boot1.getCAARlist()[tt] << endl;
	cout << "sssssssssssssssssssss" << endl;
	cout << "sssssssssssssssssssss" << endl;
	for (int tt = 0; tt < 90; tt++)
		cout << Boot2.getAARlist()[tt] << endl;
	cout << "sssssssssssssssssssss" << endl;
	cout << "sssssssssssssssssssss" << endl;
	for (int tt = 0; tt < 90; tt++)
		cout << Boot2.getCAARlist()[tt] << endl;
	cout << "sssssssssssssssssssss" << endl;
	cout << "sssssssssssssssssssss" << endl; 
		for (int tt = 0; tt < 90; tt++)
		cout << Boot3.getAARlist()[tt] << endl;
	cout << "sssssssssssssssssssss" << endl;
	cout << "sssssssssssssssssssss" << endl;
	for (int tt = 0; tt < 90; tt++)
		cout << Boot3.getCAARlist()[tt] << endl;
	cout << "sssssssssssssssssssss" << endl;
	cout << "sssssssssssssssssssss" << endl;
	*/
	system("Pause");
	return 0;
}
/*
//vector<string> a = group1.BookPage;
for (auto i = group1.BookPage.begin(); i != group1.BookPage.end(); i++) {
cout << *i << endl;
}
cout << group1.getsize() << endl;
cout << "__________________________________________" << endl;
for (auto i = group2.BookPage.begin(); i != group2.BookPage.end(); i++) {
cout << *i << endl;
}
cout << group2.getsize() << endl;
cout << "__________________________________________" << endl;
for (auto i = group3.BookPage.begin(); i != group3.BookPage.end(); i++) {
cout << *i << endl;
}
cout << group3.getsize() << endl;
cout << "__________________________________________" << endl;
*/
