#pragma once
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include "Date.h"
#include "Stock.h"
#include "BootStrapping.h"
#include "TickerBook.h"




class Group {
private:
	std::vector<std::string> group_map; // three groups of ticker from tickerbook
	std::vector<double> AAR = std::vector<double>(90);
	std::vector<double> CAAR = std::vector<double>(90);

public:
	Group() {}
	~Group() {}
	void setgroupmap(const std::vector<std::string>& mapofgroup) { group_map = mapofgroup; }
	std::vector<std::string> getGroup_Map() const { return group_map; }
	const std::vector<double > GetAAR() const { return AAR; }
	const std::vector<double> GetCAAR() const { return CAAR; }
	const int getsize() const { return group_map.size(); }
	//void setmapgroup(std::multimap<int, std::string> groupmap) { map_group = groupmap; }
	bool Compute(Market market, TickerBook tickerbook); // Create a Stock with no other information but the Prices

};
