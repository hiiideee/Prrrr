#include <iostream>
#include <string>
#include <map>
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include "Date.h"
#include "TickerBook.h"
#include "Stock.h"
#include "BootStrapping.h"
#include "Group.h"

bool Group::Compute(Market market, TickerBook tickerbook) {
	for (auto it = group_map.begin(); it != group_map.end(); it++) {
		int a = 0;
		for (int t = 0; t <= 90; t++) {
			auto itb = tickerbook.Book.find(*it);
			AAR[t] = AAR[t] * a / (a + 1) + (itb->second).getReturns(t) / (a + 1);
			Market slicedmarket = market.slice((itb->second).getStartTime(), (itb->second).getEndTime());
			AAR[t] = AAR[t] - slicedmarket.getReturns(t) / (a + 1);
		}
		a++;
	}
	CAAR[1] = AAR[1];
	for (int j = 1; j <= 90; j++) {
		CAAR[j] = AAR[j] + CAAR[j - 1];
	}
	return true;
}


	






