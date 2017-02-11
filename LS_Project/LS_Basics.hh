// File LS_Basics.hh
#ifndef LS_BASICS_HH
#define LS_BASICS_HH

#include "LS_Data.hh"

class LS_State
{  
  friend ostream& operator<<(ostream& os, const LS_State& st);
  friend bool operator==(const LS_State& st1, const LS_State& st2);
public:
  LS_State(const LS_Input &in);
  LS_State& operator=(const LS_State& s);
  unsigned operator[](unsigned i) const { return produced_items[i]; }
  unsigned& operator[](unsigned i) { return produced_items[i]; }
  unsigned AccumulatedProducedItems(unsigned i, unsigned p) const { return accumulated_produced_items[i][p]; }
  int DiffItems(unsigned i, unsigned p) const { return diff_items[i][p]; }
  void SetItem(unsigned i, unsigned p);
  void RemoveItem(unsigned p);
  
protected:
  const LS_Input & in;
  vector<unsigned> produced_items;
  
  // Redundant structures
  vector<vector<unsigned>> accumulated_produced_items;
  vector<vector<int>> diff_items;                           // diff_items = (accumulated_produced_items - accumulated_demands)
                                                            // diff_items[i][p] < 0 <-> violation
};

class LS_Move
{
  friend bool operator==(const LS_Move& m1, const LS_Move& m2);
  friend bool operator!=(const LS_Move& m1, const LS_Move& m2);
  friend bool operator<(const LS_Move& m1, const LS_Move& m2);
  friend ostream& operator<<(ostream& os, const LS_Move& c);
  friend istream& operator>>(istream& is, LS_Move& c);
 public:
  LS_Move(unsigned pos1 = 0, unsigned pos2 = 0);
  unsigned p1, p2;
};
#endif
