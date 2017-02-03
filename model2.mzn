int: Periods;
int: Items;
array[1..Items,1..Periods] of 0..1: Demands;
array[1..Items] of int: StockingCosts;
array[1..Items,1..Items] of int: SetupCosts;

array[1..Periods] of var 0..Items-1: Sol;      % Output array


constraint
      forall (i in 1..Items, j in 1..Periods)
               (sum (k in 1..j) (Demands[i,k]) <= sum (k in 1..j) (if Sol[k]=i-1 then 1 else 0 endif));

constraint
     forall (i in 1..Items)
               (sum (k in 1..Periods) (Demands[i,k]) == sum (j in 1..Periods) (if Sol[j]==i-1 then 1 else 0 endif));

constraint
     forall (i in 1..Items, j in 1..Periods)
               (sum (k in j..Periods) (Demands[i,k]) == 0 -> Sol[j] != i-1);



solve :: int_search(Sol, occurrence, indomain_random, complete)
minimize (
          sum (i in 1..Periods-1) (if Sol[i] != Sol[i+1] then SetupCosts[Sol[i]+1,Sol[i+1]+1] else 0 endif)
          +
          sum (i in 1..Items, j in 1..Periods) ((sum (k in 1..j) (if Sol[k]=i-1 then 1 else 0 endif) - sum (k in 1..j) (Demands[i,k])) * StockingCosts[i])
         );

                                                                                                                                  
output ["\nSolution:\n"]++[show(Sol)]++["\n"]++["Cost: "++show (
          sum (i in 1..Periods-1) (if Sol[i] != Sol[i+1] then SetupCosts[Sol[i]+1,Sol[i+1]+1] else 0 endif)
          +
          sum (i in 1..Items, j in 1..Periods) ((sum (k in 1..j) (if Sol[k]=i-1 then 1 else 0 endif) - sum (k in 1..j) (Demands[i,k])) * StockingCosts[i])
         )++"\n"]
