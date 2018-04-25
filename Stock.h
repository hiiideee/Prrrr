#pragma once
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include "Date.h"

struct CmpByKeyDate {
	bool operator()(Date d1, Date d2) {
		return d1.toT() < d2.toT();
	}
};

class Stock {
protected:
	static std::map<Date, double, CmpByKeyDate> MarketPrices;
	static std::map<Date, double, CmpByKeyDate> MarketReturns;
	std::string Ticker;
	Date Releasingdate;
	std::map<Date, double, CmpByKeyDate> Prices;
	std::map<Date, double, CmpByKeyDate> Returns;
	double EPSestimate;
	std::string StartTime;
	std::string EndTime;
	double EPSactual;

public:
	Stock() {}
	Stock(std::string ticker, Date releasingdate, std::map<Date, double> prices, std::map<Date, double> returns);
	Stock(const Stock& stock) :Ticker(stock.Ticker), Releasingdate(stock.Releasingdate), Prices(stock.Prices), Returns(stock.Returns) {}
	virtual ~Stock() {}

	double getMarketReturns(Date date) { auto it = MarketReturns.find(date); return it->second; };
	std::string getTicker() const;
	std::string getStartTime() { return StartTime; }
	std::string getStartTime() { return EndTime; }
	double getEPSbeat() const { return (EPSactual/EPSestimate) - 1; }
	const Date& getReleasingdate() const { return Releasingdate; }
	double getPrices(int t) { slice();  auto it = Prices.begin(); advance(it, t); return it->second; }
	double getReturns(int t) { slice();  auto it = Returns.begin(); advance(it, t); return it->second; }
	const std::map<Date, double, CmpByKeyDate> GetPrices() const { return Prices; }
	const std::map<Date, double, CmpByKeyDate> GetReturns() const { return Returns; }
	void slice();
	virtual void Display();
};

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
