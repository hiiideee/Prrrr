#pragma once
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include "Date.h"
#include "Stock.h"
#include "TickerBook.h"

typedef std::vector<std::vector<std::vector<double, long>>> Matrix;

class Bootstrapping {
private:
	double Threshold;
	int Resampletime;
	Matrix AAR_CAAR;

public:
	Bootstrapping();
	Bootstrapping(double threshold, int resampletime);
	Bootstrapping(const Bootstrapping& boot);
	~Bootstrapping();

	void setThreshold(const double &threshold) { Threshold = threshold; }
	void setResampletime(const int &resampletime) { Resampletime = resampletime; }
	double getThreshold() const { return Threshold; }
	int getResampletime() const { return Resampletime; }

	std::list<std::vector<double, long>> getCAARlist() const;
	std::list<std::vector<double, long>> getAARlist() const;
	Group intoGroup(Group group); // BookPage by Regroup;


};

