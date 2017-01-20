// File XYZ_Data.hh
#ifndef XYZ_DATA_HH
#define XYZ_DATA_HH

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

class XYZ_Input 
{
  friend ostream& operator<<(ostream& os, const XYZ_Input& bs);
public:
  XYZ_Input(string file_name);
  // Insert your getters
protected:
  // Insert your data members
};

class XYZ_Output 
{
  friend ostream& operator<<(ostream& os, const XYZ_Output& out);
  friend istream& operator>>(istream& is, XYZ_Output& out);
public:
  XYZ_Output(const XYZ_Input& i);
  XYZ_Output& operator=(const XYZ_Output& out);
  // Insert your getters
protected:
  const XYZ_Input& in;
  // Insert your data members
};
#endif
