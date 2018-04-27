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

	Market Spy("SPY", "2017-09-07", "2018-04-27", 0, 0);
	string filename = "stocks.txt";
	TickerBook StockList;
	GetTickerList(StockList, filename);
	//for (int i = 0; i < 500; i++)
		//cout << StockList.Ticker[i] << endl;
	GetStockPrice(StockList);
	GetSPYPrice(Spy);
	/*auto it = StockList.Book.find("AAPL");
	cout << it->second.getReturns(0) << endl;
	cout << it->second.Prices.size() << endl;
	cout << it->second.Returns.size() << endl;
	for (auto ite = it->second.Returns.begin(); ite != it->second.Returns.end(); ite++)
		cout << (ite->first).toString() << ":" << ite->second << endl;
	/*cout << "yeah" << endl;
	cout << Spy.Prices.size() << endl;
	cout << Spy.Returns.size()<<endl;
	cout << "yeah" << endl;
	Date A(2017, 11, 9);
	Date B(2018, 3, 15);
	Market spy(Spy.getTicker(), A.toString(), B.toString(), Spy.getEPSactual(), Spy.getEPSestimate());
	Spy.slice(A, B,&spy);
	cout << spy.Returns.size() << endl;
	cout << "yeah" << endl;
	for (auto i = spy.Returns.begin(); i != spy.Returns.end(); i++)
		cout << i->second << endl;
	cout << spy.Returns.size();*/
	//cout << StockList.getsize() << endl;
	TickerBook group1;
	TickerBook group2 ;
	TickerBook group3 ;
	double threshold = 0.05;
	StockList.Divide(threshold , &group1,&group2,&group3);
	Bootstrapping Boot1(threshold, 30), Boot2(threshold, 30), Boot3(threshold, 30);
	cout << "yeah" << endl;
	Boot1.run(Spy, group1);
	cout << "yeah" << endl;
	for (auto i = Boot1.getAARlist().begin(); i != Boot1.getAARlist().end(); i++)
		cout << *i << endl;

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