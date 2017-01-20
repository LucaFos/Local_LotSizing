// File XYZ_Basics.hh
#ifndef XYZ_BASICS_HH
#define XYZ_BASICS_HH

#include "XYZ_Data.hh"

class XYZ_State
{  
  friend ostream& operator<<(ostream& os, const XYZ_State& st);
  friend bool operator==(const XYZ_State& st1, const XYZ_State& st2);
public:
  XYZ_State(const XYZ_Input &in);
  XYZ_State& operator=(const XYZ_State& s);
protected:
  const XYZ_Input & in;  
};

class XYZ_Move
{
  friend bool operator==(const XYZ_Move& m1, const XYZ_Move& m2);
  friend bool operator!=(const XYZ_Move& m1, const XYZ_Move& m2);
  friend bool operator<(const XYZ_Move& m1, const XYZ_Move& m2);
  friend ostream& operator<<(ostream& os, const XYZ_Move& c);
  friend istream& operator>>(istream& is, XYZ_Move& c);
 public:
  XYZ_Move();
};
#endif

