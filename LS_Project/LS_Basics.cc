// File LS_Basics.cc
#include "LS_Basics.hh"

LS_State::LS_State(const LS_Input &i) 
  : in(i), produced_items(in.Periods(),0),
           accumulated_produced_items(in.Items(),vector<unsigned>(in.Periods(),0))
{
  vector<int> row;
  unsigned i1, p;
  for(i1 = 0; i1 < in.Items(); i1++)
  {
    for(p = 0; p < in.Periods(); p++)
    {
      row.push_back(-in.AccumulatedDemands(i1,p));
    }
    diff_items.push_back(row);
    row.clear();
  }
}

LS_State& LS_State::operator=(const LS_State& st)
{
  produced_items = st.produced_items;
  accumulated_produced_items = st.accumulated_produced_items;
  diff_items = st.diff_items;
  return *this;
}

bool operator==(const LS_State& st1, const LS_State& st2)
{
  unsigned i;
  for (i = 0; i < st1.in.Periods(); i++)
    if (st1[i] != st2[i])
      return false;
  return true;
}

ostream& operator<<(ostream& os, const LS_State& st)
{
  unsigned p;
  os << "[";
  for (p = 0; p < st.in.Periods()-1; p++)
    os << st[p] << ", ";
  os << st[st.in.Periods()-1] << "]";
  return os;
}

void LS_State::SetItem(unsigned i, unsigned p)
{
  unsigned p1;
  for(p1 = p; p1 < in.Periods(); p1++)
  {
    accumulated_produced_items[i][p1]++;
    diff_items[i][p1]++;
  }
  
  produced_items[p] = i;
}

void LS_State::RemoveItem(unsigned p)
{
  unsigned p1;
  for(p1 = p; p1 < in.Periods(); p1++)
  {
    accumulated_produced_items[produced_items[p]][p1]--;
    diff_items[produced_items[p]][p1]--;
  }
}

LS_Move::LS_Move(unsigned pos1, unsigned pos2)
{
  p1 = pos1;
  p2 = pos2;
}

bool operator==(const LS_Move& mv1, const LS_Move& mv2)
{
  return mv1.p1 == mv2.p1 && mv1.p2 == mv2.p2;
}

bool operator!=(const LS_Move& mv1, const LS_Move& mv2)
{
  return mv1.p1 != mv2.p1 || mv1.p2 != mv2.p2;
}

bool operator<(const LS_Move& mv1, const LS_Move& mv2)
{
  return mv1.p1 < mv2.p1 || (mv1.p1 == mv2.p1 && mv1.p2 < mv2.p2);
}

istream& operator>>(istream& is, LS_Move& mv)
{
  char ch;
  is >> ch >> mv.p1 >> ch >> mv.p2 >> ch;
  return is;
}

ostream& operator<<(ostream& os, const LS_Move& mv)
{
  os << "<" << mv.p1 << "," << mv.p2 << ">";
  return os;
}
