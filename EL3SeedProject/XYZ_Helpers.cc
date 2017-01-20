// File XYZ_Helpers.cc
#include "XYZ_Helpers.hh"

int XYZ_CostComponent1::ComputeCost(const XYZ_State& st) const
{
  unsigned cost = 0;
  // Insert the code that computes the cost for component 1 
  // of state st
	throw logic_error("XYZ_CostComponent1::ComputeCost not implemented yet");	
  return cost;
}
          
void XYZ_CostComponent1::PrintViolations(const XYZ_State& st, ostream& os) const
{
  // Insert the code that prints the violations of component 1 
  // of state st
	throw logic_error("XYZ_CostComponent1::PrintViolations not implemented yet");	
}

int XYZ_CostComponent2::ComputeCost(const XYZ_State& st) const
{ 
  unsigned cost = 0;
  // Insert the code that computes the cost for component 2
  // of state st
	throw logic_error("XYZ_CostComponent2::ComputeCost not implemented yet");	
  return cost;
}
 
void XYZ_CostComponent2::PrintViolations(const XYZ_State& st, ostream& os) const
{
  // Insert the code that prints the violations of component 1 
  // of state st
	throw logic_error("XYZ_CostComponent2::PrintViolations not implemented yet");	
}

// constructor
XYZ_StateManager::XYZ_StateManager(const XYZ_Input & pin) 
  : StateManager<XYZ_Input,XYZ_State>(pin, "XYZStateManager")  {} 

// initial state builder (random rooms)
void XYZ_StateManager::RandomState(XYZ_State& st) 
{
// Insert the code that creates a random state in object st
	throw logic_error("XYZ_StateManager::RandomState not implemented yet");	
} 

bool XYZ_StateManager::CheckConsistency(const XYZ_State& st) const
{
  // Insert the code that checks if state in object st is consistent
  // (for debugging purposes)
	throw logic_error("XYZ_StateManager::CheckConsistency not implemented yet");	
  return true;
}

/*****************************************************************************
 * Output Manager Methods
 *****************************************************************************/

void XYZ_OutputManager::InputState(XYZ_State& st, const XYZ_Output& XYZ) const 
{
  // Insert the code that "translates" an output object to a state object
	throw logic_error("XYZ_OutputManager::InputState not implemented yet");	
}

void XYZ_OutputManager::OutputState(const XYZ_State& st, XYZ_Output& XYZ) const 
{
  // Insert the code that "translates" a state object to an output object
	throw logic_error("XYZ_OutputManager::OutputState not implemented yet");	
}


/*****************************************************************************
 * XYZ_Move Neighborhood Explorer Methods
 *****************************************************************************/

// initial move builder
void XYZ_MoveNeighborhoodExplorer::RandomMove(const XYZ_State& st, XYZ_Move& mv) const  throw(EmptyNeighborhood)
{
  // insert the code that writes a random move on mv in state st
	throw logic_error("XYZ_MoveNeighborhoodExplorer::RandomMove not implemented yet");	
} 

// check move feasibility
bool XYZ_MoveNeighborhoodExplorer::FeasibleMove(const XYZ_State& st, const XYZ_Move& mv) const
{
  // Insert the code that check is move mv is legal in state st 
  // (return true if legal, false otherwise)
	throw logic_error("XYZ_MoveNeighborhoodExplorer::FeasibleMove not implemented yet");	
  return true;
} 

// update the state according to the move 
void XYZ_MoveNeighborhoodExplorer::MakeMove(XYZ_State& st, const XYZ_Move& mv) const
{
  // Insert the code that modify the state st based on the application of move mv
	throw logic_error("XYZ_MoveNeighborhoodExplorer::MakeMove not implemented yet");	
}  

void XYZ_MoveNeighborhoodExplorer::FirstMove(const XYZ_State& st, XYZ_Move& mv) const  throw(EmptyNeighborhood)
{
  // Insert the code the generate the first move in the neighborhood and store it in mv
	throw logic_error("XYZ_MoveNeighborhoodExplorer::FirstMove not implemented yet");	
}

bool XYZ_MoveNeighborhoodExplorer::NextMove(const XYZ_State& st, XYZ_Move& mv) const
{
  // Insert the code that generate the move that follows mv in the neighborhood, and writes
  // it back in mv. Return false if mv is already the last move. 
	throw logic_error("XYZ_MoveNeighborhoodExplorer::NextMove not implemented yet");	
  return true;
}

int XYZ_MoveDeltaCostComponent1::ComputeDeltaCost(const XYZ_State& st, const XYZ_Move& mv) const
{
  int cost = 0;
  // Insert the code that computes the delta cost of component 1 for move mv in state st
	throw logic_error("XYZ_MoveDeltaCostComponent1::ComputeDeltaCost not implemented yet");	
  return cost;
}
          
int XYZ_MoveDeltaCostComponent2::ComputeDeltaCost(const XYZ_State& st, const XYZ_Move& mv) const
{
  int cost = 0;
  // Insert the code that computes the delta cost of component 1 for move mv in state st
	throw logic_error("XYZ_MoveDeltaCostComponent2::ComputeDeltaCost not implemented yet");	
  return cost;
}

