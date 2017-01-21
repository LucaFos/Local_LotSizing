%include "globals.mzn";

int: Periods;
int: Items;
array[1..Items,1..Periods] of int: Demands;
array[1..Items] of int: StockingCosts;
array[1..Items,1..Items] of int: SetupCosts;

array[1..Items,1..Periods] of var int: AccumulatedDemands;

array[1..Periods] of var 0..Items-1: Sol;      % Output array

constraint
      forall (i in 1..Items, j in 1..Periods)
                (AccumulatedDemands[i,j] == sum (k in 1..j) (Demands[i,k]));

constraint
      forall (i in 1..Items, j in 1..Periods)
                (AccumulatedDemands[i,j] <= sum (k in 1..j) (if Sol[j]=i-1 then 1 else 0 endif));




solve satisfy; %minimize (sum (i in 1..Items-1) (if Sol[i] != Sol[i+1] then SetupCosts[Sol[i],Sol[i+1]] else 0 endif));    % atm only computes the setup costs


output [show(Sol)]++["\n"]++
% just for debug:
[ show(AccumulatedDemands[i,j]) ++
if j=Periods then "\n" else " " endif |
i in 1..Items, j in 1..Periods
]