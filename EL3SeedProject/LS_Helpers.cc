// File LS_Helpers.cc
#include "LS_Helpers.hh"

int LS_CostComponent1::ComputeCost(const LS_State& st) const
{
  unsigned cost = 0;
  // Insert the code that computes the cost for component 1 
  // of state st
	throw logic_error("LS_CostComponent1::ComputeCost not implemented yet");	
  return cost;
}
          
void LS_CostComponent1::PrintViolations(const LS_State& st, ostream& os) const
{
  // Insert the code that prints the violations of component 1 
  // of state st
	throw logic_error("LS_CostComponent1::PrintViolations not implemented yet");	
}

int LS_CostComponent2::ComputeCost(const LS_State& st) const
{ 
  unsigned cost = 0;
  // Insert the code that computes the cost for component 2
  // of state st
	throw logic_error("LS_CostComponent2::ComputeCost not implemented yet");	
  return cost;
}
 
void LS_CostComponent2::PrintViolations(const LS_State& st, ostream& os) const
{
  // Insert the code that prints the violations of component 1 
  // of state st
	throw logic_error("LS_CostComponent2::PrintViolations not implemented yet");	
}

// constructor
LS_StateManager::LS_StateManager(const LS_Input & pin) 
  : StateManager<LS_Input,LS_State>(pin, "LSStateManager")  {} 

// initial state builder (random rooms)
void LS_StateManager::RandomState(LS_State& st) 
{
// Insert the code that creates a random state in object st
	throw logic_error("LS_StateManager::RandomState not implemented yet");	
} 

bool LS_StateManager::CheckConsistency(const LS_State& st) const
{
  // Insert the code that checks if state in object st is consistent
  // (for debugging purposes)
	throw logic_error("LS_StateManager::CheckConsistency not implemented yet");	
  return true;
}

/*****************************************************************************
 * Output Manager Methods
 *****************************************************************************/

void LS_OutputManager::InputState(LS_State& st, const LS_Output& LS) const 
{
  // Insert the code that "translates" an output object to a state object
	throw logic_error("LS_OutputManager::InputState not implemented yet");	
}

void LS_OutputManager::OutputState(const LS_State& st, LS_Output& LS) const 
{
  // Insert the code that "translates" a state object to an output object
	throw logic_error("LS_OutputManager::OutputState not implemented yet");	
}


/*****************************************************************************
 * LS_Move Neighborhood Explorer Methods
 *****************************************************************************/

// initial move builder
void LS_MoveNeighborhoodExplorer::RandomMove(const LS_State& st, LS_Move& mv) const  throw(EmptyNeighborhood)
{
  // insert the code that writes a random move on mv in state st
	throw logic_error("LS_MoveNeighborhoodExplorer::RandomMove not implemented yet");	
} 

// check move feasibility
bool LS_MoveNeighborhoodExplorer::FeasibleMove(const LS_State& st, const LS_Move& mv) const
{
  // Insert the code that check is move mv is legal in state st 
  // (return true if legal, false otherwise)
	throw logic_error("LS_MoveNeighborhoodExplorer::FeasibleMove not implemented yet");	
  return true;
} 

// update the state according to the move 
void LS_MoveNeighborhoodExplorer::MakeMove(LS_State& st, const LS_Move& mv) const
{
  // Insert the code that modify the state st based on the application of move mv
	throw logic_error("LS_MoveNeighborhoodExplorer::MakeMove not implemented yet");	
}  

void LS_MoveNeighborhoodExplorer::FirstMove(const LS_State& st, LS_Move& mv) const  throw(EmptyNeighborhood)
{
  // Insert the code the generate the first move in the neighborhood and store it in mv
	throw logic_error("LS_MoveNeighborhoodExplorer::FirstMove not implemented yet");	
}

bool LS_MoveNeighborhoodExplorer::NextMove(const LS_State& st, LS_Move& mv) const
{
  // Insert the code that generate the move that follows mv in the neighborhood, and writes
  // it back in mv. Return false if mv is already the last move. 
	throw logic_error("LS_MoveNeighborhoodExplorer::NextMove not implemented yet");	
  return true;
}

int LS_MoveDeltaCostComponent1::ComputeDeltaCost(const LS_State& st, const LS_Move& mv) const
{
  int cost = 0;
  // Insert the code that computes the delta cost of component 1 for move mv in state st
	throw logic_error("LS_MoveDeltaCostComponent1::ComputeDeltaCost not implemented yet");	
  return cost;
}
          
int LS_MoveDeltaCostComponent2::ComputeDeltaCost(const LS_State& st, const LS_Move& mv) const
{
  int cost = 0;
  // Insert the code that computes the delta cost of component 1 for move mv in state st
	throw logic_error("LS_MoveDeltaCostComponent2::ComputeDeltaCost not implemented yet");	
  return cost;
}

