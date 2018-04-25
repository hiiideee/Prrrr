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

using namespace std;

void adjustHeap(vector<double> list, int root, int n) {
	double temproot = list[root];
	int child = 2 * root + 1;
	while (child <= n)
	{
		if (child<n&&list[child]<list[child + 1])
		{
			child++;
		}
		if (temproot>list[child])
			break;
		else
		{
			list[(child - 1) / 2] = list[child];
		}
		child = 2 * child + 1;

	}
	list[(child - 1) / 2] = temproot;
}

void heapSort(vector<double> v , int n) {
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		adjustHeap(v, i, n - 1);
	}
	for (int i = n - 1; i >= 0; i--)
	{
		double temp = v[0];
		v[0] = v[i];
		v[i] = temp;
		if (i>0)
			adjustHeap(v, 0, i - 1);
	}
}

void TickerBook::setStock(const Stock& stock) {
	BookPage.push_back(stock.getTicker());
	Book.insert(pair<string, Stock>(stock.getTicker(), stock));
	Size += 1;
}

void TickerBook::reorder() {
	int s = getSize();
	vector<double> heap;
	
	for (vector<string>::const_iterator iter = BookPage.begin(); iter != BookPage.end(); iter++) {
		auto it = Book.find(*iter);
		heap.push_back((it->second).getEPSbeat());
	}
	heapSort(heap, s);
}


void Group::Divide(double threshold) {
	reorder();
	auto it = BookPage.begin();
	while ((Book.find(*it)->second).getEPSbeat() >= threshold  && it != BookPage.end()) {
		map_group.insert(make_pair(1, *it));
	}
	while ((Book.find(*it)->second).getEPSbeat() > -1 * threshold && (Book.find(*it)->second).getEPSbeat() < threshold && it != BookPage.end()) {
		map_group.insert(make_pair(2, *it));
	}
	while ((Book.find(*it)->second).getEPSbeat() < -1 * threshold && it != BookPage.end()) {
		map_group.insert(make_pair(3, *it));
	}
}

typedef multimap <int, string>::const_iterator CIT;
typedef pair<CIT, CIT> Range;

bool Group::Compute(Stock Market) {
	Range range = map_group.equal_range(1);
	for (CIT i = range.first; i != range.second; i++) {
		for (int t = 0; t <= 120; t++) {
			auto it = Book.find(i->second);
			AAR[t][0] = AAR[t][0] * (t / (t + 1)) + ((it->second).getReturns(t)) / (t + 1) ; 
			auto itr = (it->second).GetReturns().begin();
			advance(itr, t);
			AAR[t][0] = AAR[t][0] - (it->second).getMarketReturns(itr->first) /(t + 1);
		}
	}
	Range range = map_group.equal_range(2);
	for (CIT i = range.first; i != range.second; i++) {
		for (int t = 0; t <= 120; t++) {
			auto it = Book.find(i->second);
			AAR[t][1] = AAR[t][1] * (t / (t + 1)) + ((it->second).getReturns(t)) / (t + 1); 
			auto itr = (it->second).GetReturns().begin();
			advance(itr, t);
			AAR[t][0] = AAR[t][0] - (it->second).getMarketReturns(itr->first) / (t + 1);
		}
	}
	Range range = map_group.equal_range(3);
	for (CIT i = range.first; i != range.second; i++) {
		for (int t = 0; t <= 120; t++) {
			auto it = Book.find(i->second);
			AAR[t][2] = AAR[t][2] * (t / (t + 1)) + ((it->second).getReturns(t)) / (t + 1); 
			auto itr = (it->second).GetReturns().begin();
			advance(itr, t);
			AAR[t][0] = AAR[t][0] - (it->second).getMarketReturns(itr->first) / (t + 1);
		}
	}
	
	CAAR[1] = AAR[1];
	for (int j = 1; j <= 120; j++) {
		CAAR[j][0] = AAR[j][0] + CAAR[j - 1][0];
	}
	return true;
}



