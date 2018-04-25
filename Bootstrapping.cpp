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

using namespace std;

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
	return;
}

typedef multimap <int, string>::const_iterator CIT;
typedef pair<CIT, CIT> Range;

Group Bootstrapping::intoGroup(Group group) {
	Group ggg = group;
	int rs[60];
	for (int j = 0; j < 60; ++j) rs[j] = j;
	for (int j = 59; j >= 1; --j) swap(rs[j], rs[rand() % j]);
	Range range = group.getMap_group().equal_range(1);
	CIT i = range.first;
	advance(i, rs[0]);
	for (int a = 0; a <= 59; a++) {
		ggg.

		for (int b = rs[a]; b <= rs[a + 1]; b++) i++;

		
		
	}

}

bool Bootstrapping::run(Group group, Stock Market) {
	srand(time(NULL));;
	group.Divide(Threshold);
	for (int i = 0; i <= Resampletime; i++) {
		Group ggg = intoGroup(group);
		if(ggg.Compute(Market))
		{
			for (int t = 0; t <= 120; t++) {
				AARlist[t][0] = AARlist[t][0] * i / (i + 1) + ggg.GetAAR()[t][0] / (i + 1);
				AARlist[t][1] = AARlist[t][1] * i / (i + 1) + ggg.GetAAR()[t][1] / (i + 1);
				AARlist[t][2] = AARlist[t][2] * i / (i + 1) + ggg.GetAAR()[t][2] / (i + 1);
			}
			CAARlist[1] = AARlist[1];
			for (int j = 1; j <= 120; j++) {
				CAARlist[j][0] = AARlist[j][0] + CAARlist[j - 1][0];
				CAARlist[j][1] = AARlist[j][1] + CAARlist[j - 1][1];
				CAARlist[j][2] = AARlist[j][2] + CAARlist[j - 1][2];
			}
		}
	}
	return true;
}
