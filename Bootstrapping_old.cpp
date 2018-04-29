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
#include "Group.h"

using namespace std;

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
	return;
}

void Bootstrapping::run(Group group, Market market, TickerBook tickerbook) {
	srand(time(NULL));
	for (int i = 0; i <= Resampletime; i++) {
		int a = group.getsize();
		vector<int> rs = vector<int>(60);
		for (int j = 0; j < 60; ++j) rs[j] = j;
		for (int j = 59; j >= 1; --j) swap(rs[j], rs[rand() % j]);

		Group newgroup;
		vector<string> newmap;

		for (int j = 0; j < 60; j++) {
			vector<string>::iterator it = group.getGroup_Map().begin();
			advance(it, rs[j]);
			newmap.push_back(*it);
		}
		newgroup.setgroupmap(newmap);
		if (newgroup.Compute(market, tickerbook)) {
			for (int t = 0; t <= 90; t++) {
				AARlist[t] = AARlist[t] * i / (i + 1) + newgroup.GetAAR()[t] / (i + 1);
				CAARlist[t] = CAARlist[t] * i / (i + 1) + newgroup.GetCAAR()[t] / (i + 1);
			}
		}
	}
	return;
}
