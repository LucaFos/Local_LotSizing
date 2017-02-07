// File LS_Helpers.cc
#include "LS_Helpers.hh"

int DueDates::ComputeCost(const LS_State& st) const
{
  unsigned violations = 0;
  unsigned i, p;
  for(i = 0; i < in.Items(); i++)
    for(p = 0; p < in.Periods(); p++)
      if (st.AccumulatedProducedItems(i,p) < in.AccumulatedDemands(i,p) && in.Demands(i,p) != 0)
        violations++;
  return violations;
}

void DueDates::PrintViolations(const LS_State& st, ostream& os) const
{
  unsigned i, p;
  for(i = 0; i < in.Items(); i++)
    for(p = 0; p < in.Periods(); p++)
      if (st.AccumulatedProducedItems(i,p) < in.AccumulatedDemands(i,p) && in.Demands(i,p) != 0)
        os << "Item " << i << "needed on period " << p << "but wasn't produced" << endl;
}

int SetupCosts::ComputeCost(const LS_State& st) const
{
  unsigned cost = 0;
  unsigned i;
  for (i = 0; i < in.Periods()-1; i++)
    if (st[i] != st[i+1])
      cost += in.SetupCosts(st[i],st[i+1]);
  return cost;
}

void SetupCosts::PrintViolations(const LS_State& st, ostream& os) const
{
  unsigned i;
  for (i = 0; i < in.Periods()-1; i++)
    if (st[i] != st[i+1])
      os << "The cost of setting up item " <<  st[i+1] << " from item " << st[i] << " is " << in.SetupCosts(st[i],st[i+1]) << endl;
}

int StockingCosts::ComputeCost(const LS_State& st) const
{
  unsigned cost = 0;
  unsigned i, p;
  for(i = 0; i < in.Items(); i++)
    for(p = 0; p < in.Periods(); p++)
      cost += (st.AccumulatedProducedItems(i,p) - in.AccumulatedDemands(i,p)) * in.StockingCosts(i);
  return cost;
}
 
void StockingCosts::PrintViolations(const LS_State& st, ostream& os) const
{
  unsigned i, p;
  for(i = 0; i < in.Items(); i++)
  {
    for(p = 0; p < in.Periods(); p++)
    {
      os << "Stocking item " << i << " costs " << in.StockingCosts(i) << endl;
    }
  }
}

// constructor
LS_StateManager::LS_StateManager(const LS_Input & pin) 
  : StateManager<LS_Input,LS_State>(pin, "LSStateManager")  {} 

// initial state builder (random permutation)
void LS_StateManager::RandomState(LS_State& st) 
{
  unsigned i, p, items;
  vector<unsigned> number_of_items;
  number_of_items.resize(in.Items(),0);
  
  for(i = 0; i < in.Items(); i++)
    for(p = 0; p < in.Periods(); p++)
      if(in.Demands(i,p) != 0)
        number_of_items[i]++;
  
  for(p = 0; p < in.Periods(); p++)
  {
    items = 0;
    for(i = 0; i < in.Items(); i++)
      items += number_of_items[i];
    i = 0;
    while(true)
    {
      if(static_cast<unsigned>(Random::Int(1,items)) <= number_of_items[i])
      {
        st.SetItem(i,p);
        number_of_items[i]--;
        break;
      }
      items -= number_of_items[i];
      i++;
    }
  }
}

bool LS_StateManager::CheckConsistency(const LS_State& st) const
{
  unsigned p;
  for(p = 0; p < in.Periods(); p++)
    if(st[p] < 0 || st[p] >= in.Items())
      return false;
  
  return true;
}

/*****************************************************************************
 * Output Manager Methods
 *****************************************************************************/

void LS_OutputManager::InputState(LS_State& st, const LS_Output& out) const 
{
  unsigned p;
  for(p = 0; p < in.Periods(); p++)
    st.SetItem(out.ProducedItem(p),p);
}

void LS_OutputManager::OutputState(const LS_State& st, LS_Output& out) const 
{
  unsigned p;
  for(p = 0; p < in.Periods(); p++)
  {
    out.SetItem(st[p],p);
  }
}


/*****************************************************************************
 * LS_Move Neighborhood Explorer Methods
 *****************************************************************************/

// initial move builder
void LS_MoveNeighborhoodExplorer::RandomMove(const LS_State& st, LS_Move& mv) const  throw(EmptyNeighborhood)
{
  unsigned n1 = ((in.Periods()-1) * in.Periods())/2;
  unsigned n2 = in.Periods()-1;
  unsigned p = 0;
  while(true)
  {
    if(static_cast<unsigned>(Random::Int(1,n1)) <= n2)
    {
      mv.p1 = p;
      mv.p2 = Random::Int(p+1,in.Periods()-1);
      break;
    }
    else
    {
      n1 -= n2;
      n2--;
      p++;
    }
  }
}

// check move feasibility
bool LS_MoveNeighborhoodExplorer::FeasibleMove(const LS_State& st, const LS_Move& mv) const
{
  return mv.p1 < mv.p2;
} 

// update the state according to the move 
void LS_MoveNeighborhoodExplorer::MakeMove(LS_State& st, const LS_Move& mv) const
{
  unsigned i = st[mv.p2];
  st.SetItem(st[mv.p1], mv.p2);
  st.SetItem(st[i], mv.p1);
}  

void LS_MoveNeighborhoodExplorer::FirstMove(const LS_State& st, LS_Move& mv) const  throw(EmptyNeighborhood)
{
  mv.p1 = 0;
  mv.p2 = 1;
}

bool LS_MoveNeighborhoodExplorer::NextMove(const LS_State& st, LS_Move& mv) const
{
  if (mv.p2 < in.Periods() - 1) 
  {
    mv.p2++;
    return true;
  }
  else if (mv.p1 < in.Periods() - 2)
  { 
    mv.p1++; 
    mv.p2 = mv.p1 + 1; 
    return true;
  }
  else
    return false;
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

int LS_MoveDeltaCostComponent3::ComputeDeltaCost(const LS_State& st, const LS_Move& mv) const
{
  int cost = 0;
  // Insert the code that computes the delta cost of component 1 for move mv in state st
	throw logic_error("LS_MoveDeltaCostComponent2::ComputeDeltaCost not implemented yet");	
  return cost;
}

