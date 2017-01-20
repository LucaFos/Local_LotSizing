#include "XYZ_Helpers.hh"

using namespace EasyLocal::Debug;

int main(int argc, const char* argv[])
{
  ParameterBox main_parameters("main", "Main Program options");

  // The set of arguments added are the following:
  
  Parameter<string> instance("instance", "Input instance", main_parameters); 
  Parameter<int> seed("seed", "Random seed", main_parameters);
  Parameter<string> method("method", "Solution method (empty for tester)", main_parameters);   
  Parameter<string> init_state("init_state", "Initial state (to be read from file)", main_parameters);
  Parameter<unsigned> observer("observer", "Attach the observers", main_parameters);
  Parameter<string> output_file("output_file", "Write the output to a file (filename required)", main_parameters);
 
  // 3rd parameter: false = do not check unregistered parameters
  // 4th parameter: true = silent
  CommandLineParameters::Parse(argc, argv, false, true);  

  if (!instance.IsSet())
    {
      cout << "Error: --main::instance filename option must always be set" << endl;
      return 1;
    }
  XYZ_Input in(instance);

  if (seed.IsSet())
    Random::Seed(seed);
  
  // cost components: second parameter is the cost, third is the type (true -> hard, false -> soft)
  XYZ_CostComponent1 cc1(in, 1, true);
  XYZ_CostComponent2 cc2(in, 1, true);
 
  XYZ_MoveDeltaCostComponent1 dcc1(in, cc1);
  XYZ_MoveDeltaCostComponent2 dcc2(in, cc2);

  // helpers
  XYZ_StateManager XYZ_sm(in);
  XYZ_MoveNeighborhoodExplorer XYZ_nhe(in, XYZ_sm);

  XYZ_OutputManager XYZ_om(in);
  
  // All cost components must be added to the state manager
  XYZ_sm.AddCostComponent(cc1);
  XYZ_sm.AddCostComponent(cc2);
  
  // All delta cost components must be added to the neighborhood explorer
  XYZ_nhe.AddDeltaCostComponent(dcc1);
  XYZ_nhe.AddDeltaCostComponent(dcc2);
  
  // runners
  HillClimbing<XYZ_Input, XYZ_State, XYZ_Move> XYZ_hc(in, XYZ_sm, XYZ_nhe, "XYZ_MoveHillClimbing");
  SteepestDescent<XYZ_Input, XYZ_State, XYZ_Move> XYZ_sd(in, XYZ_sm, XYZ_nhe, "XYZ_MoveSteepestDescent");
  SimulatedAnnealing<XYZ_Input, XYZ_State, XYZ_Move> XYZ_sa(in, XYZ_sm, XYZ_nhe, "XYZ_MoveSimulatedAnnealing");

  // tester
  Tester<XYZ_Input, XYZ_Output, XYZ_State> tester(in,XYZ_sm,XYZ_om);
  MoveTester<XYZ_Input, XYZ_Output, XYZ_State, XYZ_Move> swap_move_test(in,XYZ_sm,XYZ_om,XYZ_nhe, "XYZ_Move move", tester); 

  SimpleLocalSearch<XYZ_Input, XYZ_Output, XYZ_State> XYZ_solver(in, XYZ_sm, XYZ_om, "XYZ solver");
  if (!CommandLineParameters::Parse(argc, argv, true, false))
    return 1;

  if (!method.IsSet())
    { // If no search method is set -> enter in the tester
      if (init_state.IsSet())
	    tester.RunMainMenu(init_state);
      else
	    tester.RunMainMenu();
    }
  else
    {

      if (method == string("SA"))
        {
          XYZ_solver.SetRunner(XYZ_sa);
        }
      else if (method == string("HC"))
        {
          XYZ_solver.SetRunner(XYZ_hc);
        }
      else // if (method.GetValue() == string("SD"))
        {
          XYZ_solver.SetRunner(XYZ_sd);
        }
      auto result = XYZ_solver.Solve();
	  // result is a tuple: 0: solutio, 1: number of violations, 2: total cost, 3: computing time
      XYZ_Output out = result.output;
      if (output_file.IsSet())
        { // write the output on the file passed in the command line
          ofstream os(static_cast<string>(output_file).c_str());
          os << out << endl;
          os << "Cost: " << result.cost.total << endl;
					os << "Time: " << result.running_time << "s " << endl;
          os.close();
        }
      else
        { // write the solution in the standard output
          cout << out << endl;
          cout << "Cost: " << result.cost.total << endl;
					cout << "Time: " << result.running_time << "s " << endl;					
        }
   }
  return 0;
}
