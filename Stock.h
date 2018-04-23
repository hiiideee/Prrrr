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
	std::string Ticker;
	Date Releasingdate;
	std::map<Date, double, CmpByKeyDate> Prices;
	std::map<Date, double, CmpByKeyDate> Returns;
	double EPSbeat;

public:
	Stock() {}
	Stock(std::string ticker, Date releasingdate, std::map<Date, double> prices, std::map<Date, double> returns);
	Stock(const Stock& stock) :Ticker(stock.Ticker), Releasingdate(stock.Releasingdate), Prices(stock.Prices), Returns(stock.Returns) {}
	virtual ~Stock() {}

	std::string getTicker() const;
	double getEPSbeat() const { return EPSbeat; };
	const Date& getReleasingdate() const;
	double getPrices(Date date) const;
	double getReturns(Date date) const;
	const std::map<Date, double, CmpByKeyDate>& GetPrices() const;
	const std::map<Date, double, CmpByKeyDate>& GetReturns() const;
	void slice(const Date &RleaseDate);
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
