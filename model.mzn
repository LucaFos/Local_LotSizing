%include "globals.mzn";

int: Periods;
int: Items;
array[1..Items,1..Periods] of int: Demands;
array[1..Items] of int: StockingCosts;
array[1..Items,1..Items] of int: SetupCosts;

array[1..Items,1..Periods] of var 0..Periods: AccumulatedDemands;
array[1..Items,1..Periods] of var 0..Periods: AccumulatedSol;

array[1..Periods] of var 0..Items-1: Sol;      % Output array

constraint
      forall (i in 1..Items, j in 1..Periods)
                (AccumulatedDemands[i,j] == sum (k in 1..j) (Demands[i,k]));

constraint
      forall (i in 1..Items, j in 1..Periods)
                (AccumulatedSol[i,j] == sum (k in 1..j) (if Sol[k]=i-1 then 1 else 0 endif));


constraint
      forall (i in 1..Items, j in 1..Periods)
                (AccumulatedDemands[i,j] <= sum (k in 1..j) (if Sol[k]=i-1 then 1 else 0 endif));




solve minimize (
                sum (i in 1..Items-1) (if Sol[i] != Sol[i+1] then SetupCosts[Sol[i],Sol[i+1]] else 0 endif)
                +
                sum (i in 1..Items, j in 1..Periods) ((AccumulatedSol[i,j] - AccumulatedDemands[i,j]) * StockingCosts[i])
               );

output ["\nSolution:\n"]++[show(Sol)]++["\n"]++["Cost: "++show (
                sum (i in 1..Items-1) (if Sol[i] != Sol[i+1] then SetupCosts[Sol[i],Sol[i+1]] else 0 endif)
                +
                sum (i in 1..Items, j in 1..Periods) ((AccumulatedSol[i,j] - AccumulatedDemands[i,j]) * StockingCosts[i])
               )++"\n"]++
% just for debug:
["AccumulatedSol:\n"]++
[ show(AccumulatedSol[i,j]) ++
if j=Periods then "\n" else " " endif |
i in 1..Items, j in 1..Periods
]++
["Demands:\n"]++
[ show(Demands[i,j]) ++
if j=Periods then "\n" else " " endif |
i in 1..Items, j in 1..Periods
]++
["AccumulatedDemands:\n"]++
[ show(AccumulatedDemands[i,j]) ++
if j=Periods then "\n" else " " endif |
i in 1..Items, j in 1..Periods
]
