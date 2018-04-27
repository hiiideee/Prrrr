#pragma once
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <string>
#include "Date.h"

class Stock {
protected:
	std::string Ticker;
	std::string StartTime;
	std::string EndTime;
	double EPSactual;
	double EPSestimate;


public:
	std::map<Date, double> Prices;
	std::map<Date, double> Returns;

	Stock() {}
	Stock(std::string ticker, std::string starttime, std::string endtime, double eps_act, double eps_est)
		:Ticker(ticker), StartTime(starttime), EndTime(endtime), EPSactual(eps_act), EPSestimate(eps_est) {}
	Stock(const Stock& stock) :Ticker(stock.Ticker), StartTime(stock.StartTime), EndTime(stock.EndTime),
		EPSactual(stock.EPSactual), EPSestimate(stock.EPSestimate) {}
	virtual ~Stock() {} /*constructer uses 5 protected arguments rather than prices and returns*/

	std::string getTicker() const { return Ticker; }
	std::string getStartTime() { return StartTime; }
	std::string getEndTime() { return EndTime; }
	void setReturns();
	double getReturns(int t) { auto it = Returns.begin(); advance(it, t); return it->second; }
	/*double getPrices(int t);
	double getReturns(int t);
	const std::map<Date, double, CmpByKeyDate> GetPrices() const { return Prices; }
	const std::map<Date, double, CmpByKeyDate> GetReturns() const { return Returns; }*/
	/*Currently we dont need these functions because prices and returns are public*/

	double getEPSbeat() const { return (EPSactual / EPSestimate) - 1; }
	void Display();
};

class Market : public Stock {
public:
	Market() {}
	Market(std::string ticker, std::string starttime, std::string endtime, double eps_act, double eps_est)
		:Stock(ticker, starttime, endtime, eps_act, eps_est) {}
	Market(const Market& market) :Stock(market) {}
	Market slice(Date startdate, Date enddate);
};


/*
class Information : public Stock {
private:
std::string address, sector, subindustry;

public:
Information() {}
Information(std::string ticker, Date releasingdate, std::map<Date, double> prices, std::map<Date, double> returns, std::string address_, std::string sector_, std::string subindustry_);
Information(const Information& information);
virtual ~Information() {}

std::string getAddress() const { return address; };
std::string getSector() const { return sector; };
std::string getSubindustry() const { return subindustry; };
virtual void Display();
};
*/
