#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include "Date.h"
#include "TickerBook.h"
#include "Stock.h"

using namespace std;

void adjustHeap(double list[], int root, int n) {
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

void heapSort(double list[], int n) {
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		adjustHeap(list, i, n - 1);
	}
	for (int i = n - 1; i >= 0; i--)
	{
		double temp = list[0];
		list[0] = list[i];
		list[i] = temp;
		if (i>0)
			adjustHeap(list, 0, i - 1);
	}
}

void TickerBook::setStock(const Stock& stock) {
	BookPage.push_back(stock.getTicker());
	Book.insert(pair<string, Stock>(stock.getTicker(), stock));
	Size += 1;
}

void TickerBook::reorder() {
	int s = getSize();
	//list<double> heap;
	vector<double> heap;
	for (list<string>::const_iterator iter = BookPage.begin(); iter != BookPage.end(); iter++) {
		auto it = Book.find(*iter);
		heap.push_back((it->second).getEPSbeat());
	}
	vector<double>::iterator it = heap.begin();
	heapSort(it, s);


}
