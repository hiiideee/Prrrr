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


	Bootstrapping Boot1(threshold, 30), Boot2(threshold, 30), Boot3(threshold, 30);
	Boot1.run(&Spy, &group1);
	Boot2.run(&Spy, &group2);
	Boot3.run(&Spy, &group3);
	cout << "sssssssssssssssssssss" << endl;
	for (int tt = 0; tt < 90; tt++)
		cout << Boot1.getAARlist()[tt] << endl;
	cout << "sssssssssssssssssssss" << endl;
	cout << "sssssssssssssssssssss" << endl;
	for (int tt = 0; tt < 90; tt++)
		cout << Boot1.getCAARlist()[tt] << endl;*/
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
	cout << "sssssssssssssssssssss" << endl;*/

	system("Pause");
	return 0;
}
