#include <iostream>
#include <vector>
#include <iterator>
#include <random>
#include <map>

#include <random>

using namespace std;

// breaks down tickers into three groups
map<string, vector<string>> break_into_three_groups(vector<string> tickers, string gName1, string gName2, string gName3);

// N is the number of random stocks
vector<double> generate_random_stocks(int N);

// N is the number of random tickers
vector<string> generate_tickers(int N);

// Generate random stocks
map<string, vector<double>> generate_all_stocks(vector<string> tickers, int N);

// Bootstrap
map<string, vector<double>> Bootstrap(map<string, vector<double>> stock_prices, map<string, vector<string>> groups, int num_of_samples);
// Bootstrap Single
map<string, double> BootstrapSingle(map<string, vector<double>> stock_prices, map<string, vector<string>> groups, vector<double> spy_returns);
// Calculate Bootstrap means
map<string, double> CalculateBootstrapMeans(map<string, vector<double>> CAARmap);

vector<double> CalculateReturns(vector<double> prices);
double CalculateMean(const vector<double> values);
vector<double> CalculateARitForGroup(map<string, vector<double>> stock_returns, vector<double> spy_retuns, vector<string> group);

vector<double> SubtractVectors(const vector<double> &v1, const vector<double> &v2);
double VectorSum(vector<double> values);

int main(int argc, char *argv[])
{

  vector<string> tickers = generate_tickers(500);
  map<string, vector<double>> stock_prices = generate_all_stocks(tickers, 121);
  map<string, vector<string>> group_map = break_into_three_groups(tickers, "High", "Mid", "Low");
  stock_prices["SPY"] = generate_random_stocks(121);

  auto bootstrap_results = Bootstrap(stock_prices, group_map, 60);
  auto bootstrap_mean = CalculateBootstrapMeans(bootstrap_results);
  for (const auto &bm : bootstrap_mean)
  {
    cout << bm.first << ": " << bm.second << endl;
  }
}

// randomly pick 60 stocks from each group 30 times (bootstrap)
// calculate the CAAR for each of the 60 stocks, so you have 3 groups of 30 numbers for each of the 30 times
// take the average of the CAAR for each group
map<string, vector<double>> Bootstrap(map<string, vector<double>> stock_prices, map<string, vector<string>> groups, int num_of_samples)
{
  vector<double> spy_returns = CalculateReturns(stock_prices["SPY"]);
  map<string, vector<double>> stock_returns;
  for (const auto &stock_price : stock_prices)
  {
    stock_returns[stock_price.first] = CalculateReturns(stock_price.second);
  }

  map<string, vector<double>> CAARmap;

  for (int i = 0; i < num_of_samples; i++)
  {
    auto bootstrap_single = BootstrapSingle(stock_returns, groups, spy_returns);
    for (const auto &bs : bootstrap_single)
    {
      CAARmap[bs.first].push_back(bs.second);
    }
  }

  //output a map of 3 groups of 30 numbers vector CAAR
  return CAARmap;
}

map<string, double> BootstrapSingle(map<string, vector<double>> stock_returns, map<string, vector<string>> groups, vector<double> spy_returns)
{
  map<string, double> CAARmap;

  // 1. Get 60 (randomly) stocks from each `groups`
  random_device rd;
  mt19937 gen(rd());

  map<string, vector<string>> randomGroups;
  for (const auto &group : groups)
  {
    uniform_int_distribution<> dist(0, group.second.size() - 1);
    vector<string> randomGroup(60, "");
    for (int n = 0; n < 60; n++)
    {
      randomGroup[n] = group.second[dist(gen)];
    }
    randomGroups[group.first] = randomGroup;
  }

  // 2. Get the prices of these 60 stock from `stock_prices`
  for (const auto &group : randomGroups)
  {
    auto aritForGroup = CalculateARitForGroup(stock_returns, spy_returns, group.second);
    CAARmap[group.first] = CalculateMean(aritForGroup);
  }

  //output a map of 3 groups of 30 numbers vector CAAR
  return CAARmap;
}

map<string, double> CalculateBootstrapMeans(map<string, vector<double>> CAARmap)
{
  map<string, double> CAARmeans;
  for (map<string, vector<double>>::iterator it = CAARmap.begin(); it != CAARmap.end(); it++)
  {
    CAARmeans[it->first] = CalculateMean(it->second);
  }
  return CAARmeans;
}

// Do this first
double CalculateMean(const vector<double> values)
{
  double sum = 0;
  for (double i = 0; i < values.size(); ++i)
  {
    sum += values[i];
  }
  return sum / values.size();
}

vector<double> CalculateReturns(vector<double> prices)
{
  vector<double> returns(prices.size() - 1, 1);

  for (int i = 0; i < returns.size(); i++)
  {
    returns[i] = (prices[i + 1] - prices[i]) / prices[i];
  }
  return returns;
}

vector<double> CalculateARitForGroup(map<string, vector<double>> stock_returns, vector<double> spy_retuns, vector<string> group)
{
  vector<double> output(spy_retuns.size(), 0);
  for (const auto &g : group)
  {
    auto diff = SubtractVectors(stock_returns[g], spy_retuns);
    for (int i = 0; i < diff.size(); i++)
    {
      output[i] += diff[i];
    }
  }
  return output;
}

double VectorSum(vector<double> values)
{
  double sum = 0;
  for (double i = 0; i < values.size(); ++i)
  {
    sum += values[i];
  }
  return sum;
}

vector<double> SubtractVectors(const vector<double> &v1, const vector<double> &v2)
{
  vector<double> output(v1.size(), 0);
  for (int i = 0; i < v1.size(); i++)
  {
    output[i] = v1[i] - v2[i];
  }
  return output;
}

// breaks down tickers into three groups
map<string, vector<string>> break_into_three_groups(vector<string> tickers, string gName1, string gName2, string gName3)
{
  map<string, vector<string>> output;
  vector<string> group1(166, ""), group2(167, ""), group3(167, "");
  for (int i = 0; i < 166; i++)
  {
    group1[i] = tickers[i];
  }
  for (int i = 0; i < 167; i++)
  {
    group2[i] = tickers[166 + i];
  }
  for (int i = 0; i < 166; i++)
  {
    group3[i] = tickers[333 + i];
  }
  output[gName1] = group1;
  output[gName2] = group2;
  output[gName3] = group3;
  return output;
}

// N is the number of random stocks
vector<double> generate_random_stocks(int N)
{
  random_device rd{};
  mt19937 gen{rd()};

  lognormal_distribution<> dist(0.0, 0.01);
  double S0 = 100;
  double curReturn = 1;

  vector<double> output(N, 1);
  for (int i = 0; i < N; i++)
  {
    output[i] = S0 * curReturn;
    curReturn *= dist(rd);
  }
  return output;
}

// N is the number of random tickers
vector<string> generate_tickers(int N)
{
  vector<string> output(N, "");
  for (int i = 0; i < N; i++)
  {
    output[i] = "A" + to_string(i);
  }
  return output;
}

map<string, vector<double>> generate_all_stocks(vector<string> tickers, int N)
{

  map<string, vector<double>> all_stocks;
  for (const auto &tick : tickers)
  {
    all_stocks[tick] = generate_random_stocks(N);
  }
  return all_stocks;
}
