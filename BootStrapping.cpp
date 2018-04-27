#include <iostream>
#include <string>
#include <map>
#include <list>
#include <time.h>
#include <vector>
#include <cmath>
#include "Date.h"
#include "TickerBook.h"
#include "Stock.h"
#include "BootStrapping.h"
//#include "Group.h"

using namespace std;

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
	return;
}

void Bootstrapping::run(Market market, TickerBook tickerbook) {
	srand(time(NULL));
	for (int i = 0; i <= Resampletime; i++) {
		int a = tickerbook.getsize();
		vector<int> rs = vector<int>(a);
		for (int j = 0; j < a; ++j) rs[j] = j;
		for (int j = a - 1; j >= 1; --j) swap(rs[j], rs[rand() % j]);
		cout << "yeah" << endl;
		TickerBook newgroup;
		vector<string> newmap;
		cout << "yeah" << endl;
		for (int j = 0; j < 60; j++) {
			vector<string>::iterator it = tickerbook.BookPage.begin();
			advance(it, rs[j]);
			newmap.push_back(*it);
		}
		cout << "yeah" << endl;
		newgroup.BookPage = newmap;
		cout << "yeah" << endl;
		if (newgroup.Compute(market)) {
			cout << "yeah" << endl;
			for (int t = 0; t < 90; t++) {
				AARlist[t] = AARlist[t] * i / (i + 1) + newgroup.GetAAR()[t] / (i + 1);
				CAARlist[t] = CAARlist[t] * i / (i + 1) + newgroup.GetCAAR()[t] / (i + 1);
			}
		}
		cout << "yeah" << endl;
	}
	return;
}