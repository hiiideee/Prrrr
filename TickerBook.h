#pragma once
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include "Date.h"
#include "Stock.h"

class TickerBook {
private:
	int Size;
	int RequiredSize;

public:
	std::map<std::string, Stock> Book;
	std::vector<std::string> BookPage;

	TickerBook() { Size = 0; }
	TickerBook(const TickerBook& tickerbook): Book(tickerbook.Book), BookPage(tickerbook.BookPage), Size(tickerbook.Size) {}
	~TickerBook() {}


	void setStock(const Stock& stock);
	void setRequiredSize(int R) { RequiredSize = R; };
	int getSize() const { return Size; };
	void reorder();
	std::vector<std::string> Divide(double threshold, int number);
	void display();
};


