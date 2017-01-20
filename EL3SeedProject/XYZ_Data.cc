// File XYZ_Data.cc
#include "XYZ_Data.hh"
#include <fstream>

XYZ_Input::XYZ_Input(string file_name)
{
  // Insert the code that reads the input from the file 
  // and stored it into the data structures of the object 
  cerr << "XYZ_Input::XYZ_Input not implemented yet" << endl;	
}

ostream& operator<<(ostream& os, const XYZ_Input& pa)
{
  // Insert the code that write the input object (needed for debugging purposes)
  throw logic_error("operator<<(ostream& os, const XYZ_Input& pa) not implemented yet");	
  return os;
}

XYZ_Output::XYZ_Output(const XYZ_Input& my_in)
  : in(my_in)
{
  // Insert the code that initialize the data structures of the
  // output object based in the input object
  cerr << "XYZ_Output::XYZ_Output(const XYZ_Input&) not implemented yet" << endl;
}

XYZ_Output& XYZ_Output::operator=(const XYZ_Output& out)	
{
  // Insert the code that copies all data structures of the
  // output object from the ones of the parameter out
  // (excluding the reference to the input object, that is constant)
  throw logic_error("XYZ_Output::operator= not implemented yet");	
  return *this;
}

ostream& operator<<(ostream& os, const XYZ_Output& out)
{ 
 // Insert the code that writes the output object
  throw logic_error("operator<<(ostream& os, const XYZ_Output& out) not implemented yet");		
  return os;
}

istream& operator>>(istream& is, XYZ_Output& out)
{
  // Insert the code that reads the output object
  throw logic_error("operator>>(istream& is, XYZ_Output& out) not implemented yet");	
  return is;
}
