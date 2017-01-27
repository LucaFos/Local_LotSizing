// File LS_Data.cc
#include "LS_Data.hh"
#include <fstream>
#include <cassert>
#include <string>

LS_Input::LS_Input(string file_name)
{
  ifstream is(file_name.c_str());
  assert(!is.fail());
  
  unsigned i, p, i1, i2;
  string s;
  is >> s >> s >> s;
  periods = stoi(s.substr(0,s.length()));
  is >> s >> s >> s;
  items = stoi(s.substr(0,s.length()));
  
  demands.resize(items, vector<unsigned>(periods,false));
  is >> s >> s;
  for (i = 0; i < items; i++)
  {
    for (p = 0; p < periods; p++)
    {
      is >> s;
      
	  if (i==0 && p==0) demands[0][0] = stoi(s.substr(2,2));
	  else if (p==0) demands[i][0] = stoi(s.substr(1,1));
	  else demands[i][p] = stoi(s.substr(0,1));
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
  */
}

ostream& operator<<(ostream& os, const LS_Input& pa)
{
  // Insert the code that write the input object (needed for debugging purposes)
  throw logic_error("operator<<(ostream& os, const LS_Input& pa) not implemented yet");	
  return os;
}

LS_Output::LS_Output(const LS_Input& i)
  : in(i) {}

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
    os << out.produced_items[p] << ", ";
  os << out.produced_items[p] << "]";
  return os;
}

istream& operator>>(istream& is, LS_Output& out)
{
  // Insert the code that reads the output object
  throw logic_error("operator>>(istream& is, LS_Output& out) not implemented yet");	
  return is;
}
