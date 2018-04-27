#pragma once
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include "Date.h"
#include "Stock.h"
#include "TickerBook.h"
#include "Group.h"


class Bootstrapping {
private:
	double Threshold;
	int Resampletime;
	std::vector<double> AARlist = std::vector<double>(90);
	std::vector<double> CAARlist = std::vector<double>(90);

public:
	Bootstrapping();
	Bootstrapping(double threshold, int resampletime);
	Bootstrapping(const Bootstrapping& boot);
	~Bootstrapping();

	void setThreshold(const double &threshold) { Threshold = threshold; }
	void setResampletime(const int &resampletime) { Resampletime = resampletime; }
	double getThreshold() const { return Threshold; }
	int getResampletime() const { return Resampletime; }
	void run(Group group, Market market, TickerBook tickerbook);
};

