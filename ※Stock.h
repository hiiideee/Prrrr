#pragma once
#ifndef Sock_h
#define Sock_h
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
	std::map<Date, double> Prices;
	std::map<Date, double> Returns;


public:

	Stock() {}
	Stock(std::string ticker, std::string starttime, std::string endtime, double eps_act, double eps_est)
		:Ticker(ticker), StartTime(starttime), EndTime(endtime), EPSactual(eps_act), EPSestimate(eps_est) {}
	Stock(const Stock& stock) :Ticker(stock.Ticker), StartTime(stock.StartTime), EndTime(stock.EndTime),
		EPSactual(stock.EPSactual), EPSestimate(stock.EPSestimate), Prices(stock.Prices), Returns(stock.Returns) {}
	virtual ~Stock() {} /*constructer uses 5 protected arguments rather than prices and returns*/

	void setPrices(const Date& date, const double& price) { Prices.insert(std::pair<Date, double>(date, price)); }
	void setReturns(const Date& date, const double& returna) { Prices.insert(std::pair<Date, double>(date, returna)); }
	std::string getTicker() const { return Ticker; }
	std::string getStartTime() { return StartTime; }
	std::string getEndTime() { return EndTime; }
	double getEPSactual() { return EPSactual; }
	double getEPSestimate() { return EPSestimate; }
	double getEPSbeat() { return (EPSactual / EPSestimate) - 1; }	
	std::map<Date, double> GetReturns() const { return Returns; }
	void setReturns();
	double getReturns(int t) { auto it = Returns.begin(); advance(it, t); return it->second; }
	double getPrices(int t) { auto it = Prices.begin(); advance(it, t); return it->second; }

	/*Currently we dont need these functions because prices and returns are public*/
	void Display();
};

class Market : public Stock {
public:
	Market() {}
	Market(std::string ticker, std::string starttime, std::string endtime, double eps_act, double eps_est)
		:Stock(ticker, starttime, endtime, eps_act, eps_est) {}
	Market(const Market& market) :Stock(market) {}
	void slice(Date startdate, Date enddate, Market* market);
};
#endif

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
