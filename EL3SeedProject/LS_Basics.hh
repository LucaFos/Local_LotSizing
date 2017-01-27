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
protected:
  const LS_Input & in;  
};

class LS_Move
{
  friend bool operator==(const LS_Move& m1, const LS_Move& m2);
  friend bool operator!=(const LS_Move& m1, const LS_Move& m2);
  friend bool operator<(const LS_Move& m1, const LS_Move& m2);
  friend ostream& operator<<(ostream& os, const LS_Move& c);
  friend istream& operator>>(istream& is, LS_Move& c);
 public:
  LS_Move();
};
#endif

