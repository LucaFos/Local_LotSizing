// File XYZ_Helpers.hh
#ifndef XYZ_HELPERS_HH
#define XYZ_HELPERS_HH

#include "XYZ_Basics.hh"
#include <easylocal/easylocal.hh>

using namespace EasyLocal::Core;

/***************************************************************************
 * State Manager 
 ***************************************************************************/

class XYZ_CostComponent1 : public CostComponent<XYZ_Input,XYZ_State> 
{
public:
  XYZ_CostComponent1(const XYZ_Input & in, int w, bool hard) :    CostComponent<XYZ_Input,XYZ_State>(in,w,hard,"XYZ_CostComponent1") 
  {}
  int ComputeCost(const XYZ_State& st) const;
  void PrintViolations(const XYZ_State& st, ostream& os = cout) const;
};

class  XYZ_CostComponent2: public CostComponent<XYZ_Input,XYZ_State> 
{
public:
  XYZ_CostComponent2(const XYZ_Input & in, int w, bool hard) : CostComponent<XYZ_Input,XYZ_State>(in,w,hard,"XYZ_CostComponent2") 
  {}
  int ComputeCost(const XYZ_State& st) const;
  void PrintViolations(const XYZ_State& st, ostream& os = cout) const;
};

class XYZ_StateManager : public StateManager<XYZ_Input,XYZ_State> 
{
public:
  XYZ_StateManager(const XYZ_Input &);
  void RandomState(XYZ_State&);   
  bool CheckConsistency(const XYZ_State& st) const;
protected:
}; 

/***************************************************************************
 * XYZ_Move Neighborhood Explorer:
 ***************************************************************************/

class XYZ_MoveDeltaCostComponent1
  : public DeltaCostComponent<XYZ_Input,XYZ_State,XYZ_Move>
{
public:
  XYZ_MoveDeltaCostComponent1(const XYZ_Input & in, XYZ_CostComponent1& cc) 
    : DeltaCostComponent<XYZ_Input,XYZ_State,XYZ_Move>(in,cc,"XYZ_MoveDeltaCostComponent1") 
  {}
  int ComputeDeltaCost(const XYZ_State& st, const XYZ_Move& mv) const;
};

class XYZ_MoveDeltaCostComponent2
  : public DeltaCostComponent<XYZ_Input,XYZ_State,XYZ_Move>
{
public:
  XYZ_MoveDeltaCostComponent2(const XYZ_Input & in, XYZ_CostComponent2& cc) 
    : DeltaCostComponent<XYZ_Input,XYZ_State,XYZ_Move>(in,cc,"XYZ_MoveDeltaCostComponent2") 
  {}
  int ComputeDeltaCost(const XYZ_State& st, const XYZ_Move& mv) const;
};

class XYZ_MoveNeighborhoodExplorer
  : public NeighborhoodExplorer<XYZ_Input,XYZ_State,XYZ_Move> 
{
public:
  XYZ_MoveNeighborhoodExplorer(const XYZ_Input & pin, StateManager<XYZ_Input,XYZ_State>& psm)  
    : NeighborhoodExplorer<XYZ_Input,XYZ_State,XYZ_Move>(pin, psm, "XYZ_MoveNeighborhoodExplorer") {} 
  void RandomMove(const XYZ_State&, XYZ_Move&) const throw(EmptyNeighborhood);          
  bool FeasibleMove(const XYZ_State&, const XYZ_Move&) const;  
  void MakeMove(XYZ_State&,const XYZ_Move&) const;             
  void FirstMove(const XYZ_State&,XYZ_Move&) const throw(EmptyNeighborhood);  
  bool NextMove(const XYZ_State&,XYZ_Move&) const;   
protected:
};

/***************************************************************************
 * Output Manager:
 ***************************************************************************/
class XYZ_OutputManager
  : public OutputManager<XYZ_Input,XYZ_Output,XYZ_State> 
{
public:
  XYZ_OutputManager(const XYZ_Input & pin)
    : OutputManager<XYZ_Input,XYZ_Output,XYZ_State>(pin,"XYZOutputManager") {}
  void InputState(XYZ_State&, const XYZ_Output&) const;  
  void OutputState(const XYZ_State&, XYZ_Output&) const; 
}; 
#endif
