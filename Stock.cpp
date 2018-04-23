#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include "Date.h"
#include "TickerBook.h"
#include "Stock.h"

using namespace std;



void Stock::slice(const Date &RleaseDate) {

	map<Date, double, CmpByKeyDate>::iterator it1;
	map<Date, double, CmpByKeyDate>::iterator it2;
	it1 = Prices.find(RleaseDate);
	it2 = Prices.find(RleaseDate);
	int c1 = 0, c2 = 0;
	while (it1 != Prices.begin()) {
		if (c1 >= 60) {
			Prices.erase(it1--);
			c1 ++;
		}
		else {
			-- it1;
			c1++;
		}
	}

	while (it2 != Prices.end()) {
		if (c2 >= 60) {
			Prices.erase(it2++);
			c2++;
		}
		else {
			++it2;
			c2 ++;
		}
	}

	if (Prices.size() != 121) cout << "wtf" << endl;
}

