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

vector<string> TickerBook::Divide(double threshold, int number) {
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
	}
}
