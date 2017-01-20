// File XYZ_Basics.cc
#include "XYZ_Basics.hh"

XYZ_State::XYZ_State(const XYZ_Input &my_in) 
  : in(my_in)
{
  // Insert the code that initialized the data structure of the
  // state object based on the input object	
  cerr << "XYZ_State::XYZ_State(const XYZ_Input &) not implemented yet" << endl;
}

XYZ_State& XYZ_State::operator=(const XYZ_State& st)
{
  // Insert the code that copies all data structures of the
  // state object from the ones of the parameter out
  // (excluding the reference to the input object, that is constant)
  throw logic_error("XYZ_State::operator= not implemented yet");
  return *this;
}
  
bool operator==(const XYZ_State& st1, const XYZ_State& st2)
{
  // Insert the code that compares two states (this is used by the tester)
  throw logic_error("operator==(const XYZ_State& st1, const XYZ_State& st2) not implemented yet");
  return true;
}


ostream& operator<<(ostream& os, const XYZ_State& st)
{
  // Insert the code that writes the state object (for debugging)
  throw logic_error("operator<<(ostream& os, const XYZ_State& as) not implemented yet");
  return os;
}

XYZ_Move::XYZ_Move()
{
  // Insert the code that initialize the move
  cerr << "XYZ_Move::XYZ_Move() not implemented yet" << endl;
}

bool operator==(const XYZ_Move& mv1, const XYZ_Move& mv2)
{
  // Insert the code that checks if two moves are identical
  throw logic_error("operator==(const XYZ_Move& mv1, const XYZ_Move& mv2) not implemented yet");	
  return true;
}

bool operator!=(const XYZ_Move& mv1, const XYZ_Move& mv2)
{
  // Insert the code that checks if two moves are different
  throw logic_error("operator!=(const XYZ_Move& mv1, const XYZ_Move& mv2) not implemented yet");	
  return true;
}

bool operator<(const XYZ_Move& mv1, const XYZ_Move& mv2)
{
  // Insert the code that checks if one move precedes another one
  // (in any selected order)
  throw logic_error("operator<(const XYZ_Move& mv1, const XYZ_Move& mv2) not implemented yet");	
  return true;
}

istream& operator>>(istream& is, XYZ_Move& mv)
{
  // Insert the code that read a move
  throw logic_error("operator>>(istream& is, XYZ_Move& cìmv) not implemented yet");	
  return is;
}

ostream& operator<<(ostream& os, const XYZ_Move& mv)
{
  // Insert the code that writes a move
  throw logic_error("operator<<(ostream& os, const XYZ_Move& mv) not implemented yet");	
  return os;
}
