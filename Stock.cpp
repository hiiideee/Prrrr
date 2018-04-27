#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include "Date.h"
#include "Stock.h"

using namespace std;
/*
double Stock::getPrices(int t) {
auto it = Prices.begin();
advance(it, t);
return it->second;
}

double Stock::getReturns(int t) {
auto it = Returns.begin();
advance(it, t);
return it->second;
}
*/
void Stock::Display() {
	std::cout << "Ticker: " << Ticker << std::endl;
	std::cout << "Start date: " << StartTime << std::endl;
	std::cout << "End date:" << EndTime << std::endl;
	std::cout << "Estimated EPS:" << EPSestimate << std::endl;
	std::cout << "Actual EPS:" << EPSactual << std::endl;
	std::cout << "Prices:" << std::endl;
	std::map<Date, double>::iterator itr;
	for (itr = Prices.begin(); itr != Prices.end(); itr++)
		std::cout << (itr->first).toString() << '    ' << itr->second;
}

Market Market::slice(Date startdate, Date enddate) {
	Market market(Ticker, startdate.toString(), enddate.toString(), EPSactual, EPSestimate);
	for (auto i = Prices.find(startdate); i != ++(Prices.find(enddate)); i++)
		market.Prices.insert(std::pair<Date, double>(i->first, i->second));
	for (auto i = Returns.find(startdate); i != ++(Returns.find(enddate)); i++)
		market.Returns.insert(std::pair<Date, double>(i->first, i->second));
	return market;
}

void Stock::setReturns() {
	auto it = Prices.begin();
	for (it; it != Prices.end(); ) {
		double lstday = it->second;
		it++;
		if (it == Prices.end()) break;
		else Returns.insert(pair<Date, double>(it->first, (it->second - lstday) / lstday));
	}
}

