include "globals.mzn";

int: Periods;
int: Items;
array[1..Items,1..Periods] of 0..1: Demands;
array[1..Items] of int: StockingCosts;
array[1..Items,1..Items] of int: SetupCosts;

array[1..Items,1..Periods] of var 0..1: SolMatrix;        % Solution matrix
array[1..Periods] of var 0..Items-1: Sol;                 % Output array



% Schedule the production of exactly one item for each period
constraint
      forall (t in 1..Periods)
              (exactly(1,[SolMatrix[i,t] | i in 1..Items],1));


% Every item must be produced before the time for which it's requested
constraint
      forall (i in 1..Items, j in 1..Periods)
               (sum (k in 1..j) (Demands[i,k]) <= sum (k in 1..j) (SolMatrix[i,k]));


% This constraint "links" SolMatrix and Sol
constraint
      forall(t in 1..Periods)
               (sum (i in 1..Items)(i*SolMatrix[i,t]) == Sol[t]+1);               



% Minimize the stocking costs (keeping an already produced item stored) and
%          the setup costs (switching from producing a certain type of item to another)
solve:: int_search([SolMatrix[i,j] | i in 1..Items, j in 1..Periods], occurrence, indomain_min, complete)
       minimize (
          sum (i in 1..Items) (StockingCosts[i] * sum(t in 1..Periods, j in 1..t)(SolMatrix[i,j]-Demands[i,j]))
          %+
          %sum (i in 1..Periods-1) (SetupCosts[Sol[i]+1,Sol[i+1]+1])
         );


output ["Cost: "++show (
          sum (i in 1..Items) (StockingCosts[i] * sum(t in 1..Periods, j in 1..t)(SolMatrix[i,j]-Demands[i,j]))
          %+
          %sum (i in 1..Periods-1) (SetupCosts[Sol[i]+1,Sol[i+1]+1])
          )++" "]
       ++
       [show(Sol)]