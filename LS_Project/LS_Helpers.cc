// File LS_Helpers.cc
#include "LS_Helpers.hh"

int DueDates::ComputeCost(const LS_State& st) const
{
  unsigned violations = 0;
  unsigned i, p;
  for(i = 0; i < in.Items(); i++)
    for(p = 0; p < in.Periods(); p++)
      if (st.DiffItems(i,p) < 0)
      {
        violations -= st.DiffItems(i,p);
      }
  
  return violations;
}

void DueDates::PrintViolations(const LS_State& st, ostream& os) const
{
  unsigned i, p;
  for(i = 0; i < in.Items(); i++)
    for(p = 0; p < in.Periods(); p++)
      if (st.DiffItems(i,p) < 0)
        os << (-st.DiffItems(i,p)) << " item(s) of type " << i << " needed on period " << p << " but weren't produced" << endl;
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
      if(st.DiffItems(i,p) > 0)
        cost += st.DiffItems(i,p) * in.StockingCosts(i);
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
    out.SetItem(st[p],p);
}


/*****************************************************************************
 * LS_Move Neighborhood Explorer Methods
 *****************************************************************************/

// initial move builder
void LS_MoveNeighborhoodExplorer::RandomMove(const LS_State& st, LS_Move& mv) const  throw(EmptyNeighborhood)
{
  unsigned p;
  vector<unsigned> unequal_items;
  while(true)
  {
    mv.p1 = Random::Int(0,in.Periods()-1);
    
    // This for cycle fills unequal_items with the positions in which the produced item
    // is different than the one produced in p1
    for(p = 0; p < in.Periods(); p++)
    {
      if(st[mv.p1] != st[p])
      {
        unequal_items.push_back(p);
      }
    }
    
    mv.p2 = unequal_items[Random::Int(0,unequal_items.size()-1)];
    if(mv.p1 > mv.p2)
    {
      p = mv.p1;
      mv.p1 = mv.p2;
      mv.p2 = p;
    }
    return;
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
  unsigned i1 = st[mv.p1];
  unsigned i2 = st[mv.p2];
  st.RemoveItem(mv.p1);
  st.RemoveItem(mv.p2);
  st.SetItem(i1, mv.p2);
  st.SetItem(i2, mv.p1);
}

// Automatically avoids null moves
void LS_MoveNeighborhoodExplorer::FirstMove(const LS_State& st, LS_Move& mv) const  throw(EmptyNeighborhood)
{
  mv.p1 = 0;
  mv.p2 = 1;
  while(st[mv.p2] == st[mv.p1])
    mv.p2++;
}

// Generate next move avoiding null moves
bool LS_MoveNeighborhoodExplorer::NextMove(const LS_State& st, LS_Move& mv) const
{
  if (mv.p2 == in.Periods()-1)
  {
    mv.p1++;
    mv.p2 = mv.p1+1;
  }
  else
  {
    mv.p2++;
  }
  while(mv.p1 < in.Periods()-1)
  {
    while(st[mv.p1] == st[mv.p2] && mv.p2 < in.Periods()-1)
      mv.p2++;
    if(st[mv.p1] != st[mv.p2])
      return true;
    
    mv.p1++;
    mv.p2 = mv.p1+1;
  }
  
  return false;
}

int LS_MoveDeltaCostDueDates::ComputeDeltaCost(const LS_State& st, const LS_Move& mv) const
{
  int violations = 0;
  unsigned p;
  
  // It checks the rows corresponding to st[mv.p1] and st[mv.p2] between p1 and p2-1
  for(p = mv.p1; p < mv.p2; p++)
  {
    if(st.DiffItems(st[mv.p2],p) < 0){
      violations--;
    }
    if(st.DiffItems(st[mv.p1],p) <= 0){
      violations++;
    }
  }
  return violations;
}

// It is sufficient to check on the preceding and the succeeding of p1 and p2
int LS_MoveDeltaCostSetupCosts::ComputeDeltaCost(const LS_State& st, const LS_Move& mv) const
{
  int cost = 0;
  unsigned p1 = mv.p1;
  unsigned p2 = mv.p2;
  
  if(p1+1 != p2)
  {
    cost += in.SetupCosts(st[p2],st[p1+1]);
    cost -= in.SetupCosts(st[p1],st[p1+1]);
  }
  else
  {
    cost += in.SetupCosts(st[p2],st[p1]);
  }
  
  if(p1 != 0)
  {
    cost += in.SetupCosts(st[p1-1],st[p2]);
    cost -= in.SetupCosts(st[p1-1],st[p1]);
  }
  
  if(p2 != in.Periods()-1)
  {
    cost += in.SetupCosts(st[p1],st[p2+1]);
    cost -= in.SetupCosts(st[p2],st[p2+1]);
  }
  
  cost += in.SetupCosts(st[p2-1],st[p1]);
  cost -= in.SetupCosts(st[p2-1],st[p2]);
  
  return cost;
}

int LS_MoveDeltaCostStockingCosts::ComputeDeltaCost(const LS_State& st, const LS_Move& mv) const
{
  int cost = 0;
  unsigned p;
  
  // It checks the rows corresponding to st[mv.p1] and st[mv.p2] between p1 and p2-1 
  for(p = mv.p1; p < mv.p2; p++)
  {
    if(st.DiffItems(st[mv.p2],p) >= 0){
      cost += in.StockingCosts(st[mv.p2]);
    }
    if(st.DiffItems(st[mv.p1],p) > 0){
      cost -= in.StockingCosts(st[mv.p1]);
    }
  }
  
  return cost;
}

