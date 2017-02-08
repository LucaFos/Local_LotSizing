// File LS_Data.cc
#include "LS_Data.hh"
#include <fstream>
#include <cassert>
#include <string>

LS_Input::LS_Input(string file_name)
{
  ifstream is(file_name.c_str());
  assert(!is.fail());
  
  unsigned i, p, i1, i2, item;
  string s;
  is >> s >> s >> s;
  periods = stoi(s.substr(0,s.length()));
  is >> s >> s >> s;
  items = stoi(s.substr(0,s.length()));
  
  demands.resize(items, vector<unsigned>(periods,false));
  accumulated_demands.resize(items, vector<unsigned>(periods,false));
  //demands_positions.resize(items, vector<unsigned>(0,0));
  is >> s >> s;
  for (i = 0; i < items; i++)
  {
    for (p = 0; p < periods; p++)
    {
      is >> s;
      
      if (i==0 && p==0)
      {
        item = stoi(s.substr(2,2));
        demands[0][0] = item;
        accumulated_demands[0][0] = item;
        //if(item != 0)
          //demands_positions[i].push_back(p);
      }
      else if (p==0)
      {
        item = stoi(s.substr(1,1));
        demands[i][0] = item;
        accumulated_demands[i][0] = item;
        //if(item != 0)
          //demands_positions[i].push_back(p);
      }
      else
      {
        item = stoi(s.substr(0,1));
        demands[i][p] = item;
        accumulated_demands[i][p] = accumulated_demands[i][p-1] + item;
        //if(item != 0)
          //demands_positions[i].push_back(p);
      }
    }
  }
  
  stocking_costs.resize(items);
  is >> s >> s;
  for (i = 0; i < items; i++)
  {
    is >> s;
	
    if (i==0) stocking_costs [0] = stoi(s.substr(1,s.length()-1));
    else stocking_costs [i] = stoi(s.substr(0,s.length()-1));
  }
  
  setup_costs.resize(items, vector<unsigned>(items,false));
  is >> s >> s;
  for (i1 = 0; i1 < items; i1++)
  {
    for (i2 = 0; i2 < items; i2++)
    {
      is >> s;
      
      if (i1==0 && i2==0) setup_costs[0][0] = stoi(s.substr(2,s.length()-1));
      else if (i2==0) setup_costs[i1][0] = stoi(s.substr(1,s.length()-1));
      else setup_costs[i1][i2] = stoi(s.substr(0,s.length()));
    }
  }
  

  // DEBUG
  /*
  cout << "periods: " << periods << endl;
  cout << "items: " << items << endl;
  
  cout << "demands:\n";
  for (i = 0; i < items; i++)
  {  
    for (p = 0; p < periods; p++)
    {
      cout << demands[i][p] << " ";
      if (p==periods-1) cout << endl;
    }
  }
  
  cout << "accumulated_demands:\n";
  for (i = 0; i < items; i++)
  {  
    for (p = 0; p < periods; p++)
    {
      cout << accumulated_demands[i][p] << " ";
      if (p==periods-1) cout << endl;
    }
  }
  
  cout << "demands_positions:\n";
  for(i = 0; i < items; i++)
  {
    for(p = 0; p < demands_positions[i].size(); p++)
    {
      cout << demands_positions[i][p] << " ";
      if (p==demands_positions[i].size()-1) cout << endl;
    }
  }
  
  cout << "stocking_costs:\n";
  for (i = 0; i < items; i++) cout << stocking_costs[i] << " ";
  cout << endl << "setup_costs:\n";
  for (i1 = 0; i1 < items; i1++)
  {
    for (i2 = 0; i2 < items; i2++)
    {
      cout << setup_costs[i1][i2] << " ";
      if (i2==items-1) cout << endl;
    }
  }
  cout << endl;
  
  cout << "Periods = " << periods << ";\n";
  cout << "Items = " << items << ";\n";
  cout << "Demands = [";
  for (i = 0; i < items; i++)
  {
    for (p = 0; p < periods; p++)
    {
      if (i!=0 && p==0) cout << "\n           |";
      else if (p==0) cout << "|";
      if (p==periods-1) cout << demands[i][p];
      else cout << demands[i][p] << ", ";
    }
  }
  cout << "|];\n";
  cout << "StockingCosts = [";
  for (i = 0; i < items-1; i++)
    cout << stocking_costs[i] << ", ";
  cout << stocking_costs[items-1] << "];\n";
  cout << "SetupCosts = [";
  for (i1 = 0; i1 < items; i1++)
  {
    for (i2 = 0; i2 < items; i2++)
    {
      if (i1!=0 && i2==0) cout << "\n              |";
      else if (i2==0) cout << "|";
      if (i2==items-1) cout << setup_costs[i1][i2];
      else cout << setup_costs[i1][i2] << ", ";
    }
  }
  cout << "|];\n";
  */
}

ostream& operator<<(ostream& os, const LS_Input& bs)
{
  unsigned i, p, i1, i2;
  os << "Periods = " << bs.periods << ";\n";
  os << "Items = " << bs.items << ";\n";
  os << "Demands = [";
  for (i = 0; i < bs.items; i++)
  {
    for (p = 0; p < bs.periods; p++)
    {
      if (i!=0 && p==0) os << "\n           |";
      else if (p==0) os << "|";
      if (p==bs.periods-1) os << bs.demands[i][p];
      else os << bs.demands[i][p] << ", ";
    }
  }
  os << "|];\n";
  os << "StockingCosts = [";
  for (i = 0; i < bs.items-1; i++)
    os << bs.stocking_costs[i] << ", ";
  os << bs.stocking_costs[bs.items-1] << "];\n";
  os << "SetupCosts = [";
  for (i1 = 0; i1 < bs.items; i1++)
  {
    for (i2 = 0; i2 < bs.items; i2++)
    {
      if (i1!=0 && i2==0) os << "\n              |";
      else if (i2==0) os << "|";
      if (i2==bs.items-1) os << bs.setup_costs[i1][i2];
      else os << bs.setup_costs[i1][i2] << ", ";
    }
  }
  os << "|];\n";
  return os;
}

LS_Output::LS_Output(const LS_Input& i)
  : in(i), produced_items(in.Periods(),0)
{}

LS_Output& LS_Output::operator=(const LS_Output& out)	
{
  produced_items = out.produced_items;
  return *this;
}

ostream& operator<<(ostream& os, const LS_Output& out)
{
  unsigned p;
  os << "[";
  for (p = 0; p < out.produced_items.size()-1; p++)
  {
    os << out.produced_items[p] << ", ";
  }
  os << out.produced_items[p] << "]";
  return os;
}

istream& operator>>(istream& is, LS_Output& out)
{
  unsigned p = 0;
  string s;
  is >> s;
  while (s!="");
  {
    if (p==0) out.produced_items[0] = stoi(s.substr(1,s.length()-1));
    else out.produced_items[p] = stoi(s.substr(0,s.length()-1));
    is >> s;
    p++;
  }
  return is;
}
