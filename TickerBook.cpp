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
/*
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

/*vector<string> TickerBook::Divide(double threshold, int number) {
	if (getSize() == RequiredSize) {
		vector<string> mapofgroup;
		reorder();
		auto it = BookPage.begin();
		for (it; it != BookPage.end();) {
			while ((Book.find(*it)->second).getEPSbeat() >= threshold && it != BookPage.end()) {
				if (number == 1) mapofgroup.push_back(*it++);
				else it++;
			}
			while ((Book.find(*it)->second).getEPSbeat() > -1 * threshold && (Book.find(*it)->second).getEPSbeat() < threshold && it != BookPage.end()) {
				if (number == 2) mapofgroup.push_back(*it++);
				else it++;
			}
			while ((Book.find(*it)->second).getEPSbeat() < -1 * threshold && it != BookPage.end()) {
				if (number == 3) mapofgroup.push_back(*it++);
				else it++;
			}
		}
		return mapofgroup;
	}
	else {
		cout << "The number of the Stock is not Right" << endl;
		return ;
	}
}*/

void TickerBook::Divide(double threshold, TickerBook *group1, TickerBook *group2, TickerBook *group3) {
	//reorder();
	auto it = BookPage.begin();
	for (it; it != BookPage.end(); it++) {
		if ((Book.find(*it)->second).getEPSbeat() >= threshold && it != BookPage.end()) {
			group1->BookPage.push_back(*it);
			group1->Book.insert(pair<string, Stock>(*it, Book.find(*it)->second));
		}
		else if ((Book.find(*it)->second).getEPSbeat() > -1 * threshold && (Book.find(*it)->second).getEPSbeat() < threshold && it != BookPage.end()) {
			group2->BookPage.push_back(*it);
			group2->Book.insert(pair<string, Stock>(*it, Book.find(*it)->second));
		}
		else if ((Book.find(*it)->second).getEPSbeat() < -1 * threshold && it != BookPage.end()) {
			group3->BookPage.push_back(*it);
			group3->Book.insert(pair<string, Stock>(*it, Book.find(*it)->second));
		}
	}

}

bool TickerBook::Compute(Market market) {
	for (auto it = BookPage.begin(); it != BookPage.end(); it++) {
		int a = 0;
		for (int t = 0; t < 90; t++) {
			auto itb = Book.find(*it);
			cout << "yeah" << endl;
			AAR[t] = AAR[t] * a / (a + 1) + (itb->second).getReturns(t) / (a + 1);
			cout << "yeah" << endl;
			Market slicedmarket(market.getTicker(), market.getStartTime(), market.getEndTime(),
				market.getEPSactual(), market.getEPSestimate());
			market.slice((itb->second).getStartTime(), (itb->second).getEndTime(),&slicedmarket);
			cout << "yeah" << endl;
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