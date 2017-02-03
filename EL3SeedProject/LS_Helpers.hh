// File LS_Helpers.hh
#ifndef LS_HELPERS_HH
#define LS_HELPERS_HH

#include "LS_Basics.hh"
#include <easylocal/easylocal.hh>

using namespace EasyLocal::Core;

/***************************************************************************
 * State Manager 
 ***************************************************************************/

class SetupCosts : public CostComponent<LS_Input,LS_State> 
{
public:
  SetupCosts(const LS_Input & in, int w, bool hard) :    CostComponent<LS_Input,LS_State>(in,w,hard,"LS_CostComponent1") 
  {}
  int ComputeCost(const LS_State& st) const;
  void PrintViolations(const LS_State& st, ostream& os = cout) const;
};

class  StockingCosts: public CostComponent<LS_Input,LS_State> 
{
public:
  StockingCosts(const LS_Input & in, int w, bool hard) : CostComponent<LS_Input,LS_State>(in,w,hard,"StockingCosts") 
  {}
  int ComputeCost(const LS_State& st) const;
  void PrintViolations(const LS_State& st, ostream& os = cout) const;
};

class LS_StateManager : public StateManager<LS_Input,LS_State> 
{
public:
  LS_StateManager(const LS_Input &);
  void RandomState(LS_State&);   
  bool CheckConsistency(const LS_State& st) const;
protected:
}; 

/***************************************************************************
 * LS_Move Neighborhood Explorer:
 ***************************************************************************/

class LS_MoveDeltaCostComponent1
  : public DeltaCostComponent<LS_Input,LS_State,LS_Move>
{
public:
  LS_MoveDeltaCostComponent1(const LS_Input & in, SetupCosts& cc) 
    : DeltaCostComponent<LS_Input,LS_State,LS_Move>(in,cc,"LS_MoveDeltaCostComponent1") 
  {}
  int ComputeDeltaCost(const LS_State& st, const LS_Move& mv) const;
};

class LS_MoveDeltaCostComponent2
  : public DeltaCostComponent<LS_Input,LS_State,LS_Move>
{
public:
  LS_MoveDeltaCostComponent2(const LS_Input & in, StockingCosts& cc) 
    : DeltaCostComponent<LS_Input,LS_State,LS_Move>(in,cc,"LS_MoveDeltaCostComponent2") 
  {}
  int ComputeDeltaCost(const LS_State& st, const LS_Move& mv) const;
};

class LS_MoveNeighborhoodExplorer
  : public NeighborhoodExplorer<LS_Input,LS_State,LS_Move> 
{
public:
  LS_MoveNeighborhoodExplorer(const LS_Input & pin, StateManager<LS_Input,LS_State>& psm)  
    : NeighborhoodExplorer<LS_Input,LS_State,LS_Move>(pin, psm, "LS_MoveNeighborhoodExplorer") {} 
  void RandomMove(const LS_State&, LS_Move&) const throw(EmptyNeighborhood);          
  bool FeasibleMove(const LS_State&, const LS_Move&) const;  
  void MakeMove(LS_State&,const LS_Move&) const;             
  void FirstMove(const LS_State&,LS_Move&) const throw(EmptyNeighborhood);  
  bool NextMove(const LS_State&,LS_Move&) const;   
protected:
};

/***************************************************************************
 * Output Manager:
 ***************************************************************************/
class LS_OutputManager
  : public OutputManager<LS_Input,LS_Output,LS_State> 
{
public:
  LS_OutputManager(const LS_Input & pin)
    : OutputManager<LS_Input,LS_Output,LS_State>(pin,"LSOutputManager") {}
  void InputState(LS_State&, const LS_Output&) const;  
  void OutputState(const LS_State&, LS_Output&) const; 
}; 
#endif
