#pragma once
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include "Date.h"
#include "Stock.h"

class TickerBook {
protected:
	std::map<std::string, Stock> Book;
	std::list<std::string> BookPage;
	int Size;

public:
	TickerBook() {}
	~TickerBook() {}

	void setStock(const Stock& stock);
	int getSize() const { return Size; };
	void reorder();
};

class Group : TickerBook {
private:
	std::vector<std::vector<std::string>> map_keys; // three groups of ticker from tickerbook
	std::vector<std::vector<double>> AAR = std::vector<std::vector<double>>(120);
	std::vector<std::vector<double>> CAAR = std::vector<std::vector<double>>(120);

public:
	Group() {}
	~Group() {}
	void Divide(double threshold) const;
	const std::vector<double>& GetAAR() const;
	const std::vector<double>& GetCAAR() const;
	bool Compute();
};

