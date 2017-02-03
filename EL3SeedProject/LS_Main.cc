#include "LS_Helpers.hh"

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
  LS_Input in(instance);

  if (seed.IsSet())
    Random::Seed(seed);
  
  // cost components: second parameter is the cost, third is the type (true -> hard, false -> soft)
  SetupCosts cc1(in, 1, true);
  StockingCosts cc2(in, 1, true);
 
  LS_MoveDeltaCostComponent1 dcc1(in, cc1);
  LS_MoveDeltaCostComponent2 dcc2(in, cc2);

  // helpers
  LS_StateManager LS_sm(in);
  LS_MoveNeighborhoodExplorer LS_nhe(in, LS_sm);

  LS_OutputManager LS_om(in);
  
  // All cost components must be added to the state manager
  LS_sm.AddCostComponent(cc1);
  LS_sm.AddCostComponent(cc2);
  
  // All delta cost components must be added to the neighborhood explorer
  LS_nhe.AddDeltaCostComponent(dcc1);
  LS_nhe.AddDeltaCostComponent(dcc2);
  
  // runners
  HillClimbing<LS_Input, LS_State, LS_Move> LS_hc(in, LS_sm, LS_nhe, "LS_MoveHillClimbing");
  SteepestDescent<LS_Input, LS_State, LS_Move> LS_sd(in, LS_sm, LS_nhe, "LS_MoveSteepestDescent");
  SimulatedAnnealing<LS_Input, LS_State, LS_Move> LS_sa(in, LS_sm, LS_nhe, "LS_MoveSimulatedAnnealing");

  // tester
  Tester<LS_Input, LS_Output, LS_State> tester(in,LS_sm,LS_om);
  MoveTester<LS_Input, LS_Output, LS_State, LS_Move> swap_move_test(in,LS_sm,LS_om,LS_nhe, "LS_Move move", tester); 

  SimpleLocalSearch<LS_Input, LS_Output, LS_State> LS_solver(in, LS_sm, LS_om, "LS solver");
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
          LS_solver.SetRunner(LS_sa);
        }
      else if (method == string("HC"))
        {
          LS_solver.SetRunner(LS_hc);
        }
      else // if (method.GetValue() == string("SD"))
        {
          LS_solver.SetRunner(LS_sd);
        }
      auto result = LS_solver.Solve();
	  // result is a tuple: 0: solutio, 1: number of violations, 2: total cost, 3: computing time
      LS_Output out = result.output;
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
