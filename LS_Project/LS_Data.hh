// File LS_Data.hh
#ifndef LS_DATA_HH
#define LS_DATA_HH

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

class LS_Input 
{
  friend ostream& operator<<(ostream& os, const LS_Input& bs);

public:
  LS_Input(string file_name);
  unsigned Periods() const { return periods; }
  unsigned Items() const { return items; }
  unsigned OptimalValue() const { return optimal_value; }
  unsigned Demands(unsigned i, unsigned p) const { return demands[i][p]; }
  unsigned StockingCosts(unsigned i) const { return stocking_costs[i]; }
  unsigned SetupCosts(unsigned i1, unsigned i2) const {return setup_costs[i1][i2]; }
  unsigned AccumulatedDemands(unsigned i, unsigned p) const { return accumulated_demands[i][p]; }
  
protected:
  unsigned periods, items;
  unsigned optimal_value;
  vector<vector<unsigned>> demands;
  vector<unsigned> stocking_costs;
  vector<vector<unsigned>> setup_costs;
  
  // redundant structures
  vector<vector<unsigned>> accumulated_demands;
};

class LS_Output 
{
  friend ostream& operator<<(ostream& os, const LS_Output& out);
  friend istream& operator>>(istream& is, LS_Output& out);

public:
  LS_Output(const LS_Input& i);
  LS_Output& operator=(const LS_Output& out);
  unsigned ProducedItem(unsigned p) const { return produced_items[p]; }
  void SetItem(unsigned i, unsigned p) { produced_items[p] = i; }

protected:
  const LS_Input& in;
  vector<unsigned> produced_items;
};
#endif
