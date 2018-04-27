#pragma once
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include "Date.h"
//#include "Group.h"
#include "Stock.h"

class TickerBook {
private:
	//int Size;
	//int RequiredSize;

public:
	std::map<std::string, Stock> Book;
	std::vector<std::string> BookPage;
	std::vector<double> AAR = std::vector<double>(90);
	std::vector<double> CAAR = std::vector<double>(90);

	TickerBook() {}
	TickerBook(const TickerBook& tickerbook): Book(tickerbook.Book), BookPage(tickerbook.BookPage){}
	~TickerBook() {}


	//void setStock(const Stock& stock);
	//void setRequiredSize(int R) { RequiredSize = R; };
	//int getSize() const { return Size; };
	//void reorder();
	std::vector<double > GetAAR() const { return AAR; }
	std::vector<double> GetCAAR() const { return CAAR; }
	int getsize() const { return BookPage.size(); }
	//std::vector<std::string> Divide(double threshold, int number);
	void Divide(double threshold, TickerBook *group1, TickerBook *group2, TickerBook *group3);
	//void display();
	bool Compute(Market market);
};


