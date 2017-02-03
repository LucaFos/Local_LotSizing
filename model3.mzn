int: Periods;
int: Items;
array[1..Items,1..Periods] of 0..1: Demands;
array[1..Items] of int: StockingCosts;
array[1..Items,1..Items] of int: SetupCosts;
array[1..Periods*Items] of var 0..1: X;        % Output matrix
array[1..Periods] of var 0..Items-1: Sol;      % Output array


constraint
      forall (t in 1..Periods)
              (sum(i in 1..Items)(X[(i-1)*Periods+t]) == 1);

constraint
      forall (i in 1..Items, j in 1..Periods)
               (sum (k in 1..j) (Demands[i,k]) <= sum (k in 1..j) (X[(i-1)*Periods+k]));


constraint
      forall(t in 1..Periods)
               (sum (i in 1..Items)(i*X[(i-1)*Periods+t]) == Sol[t]+1);


solve:: int_search(X, occurrence, indomain, complete) 
       minimize (
          sum (i in 1..Items) (StockingCosts[i] * sum(t in 1..Periods, j in 1..t)(X[(i-1)*Periods+j]-Demands[i,j]))
          +
          sum (i in 1..Periods-1) (if Sol[i] != Sol[i+1] then SetupCosts[Sol[i]+1,Sol[i+1]+1] else 0 endif)
         );

                                                                                                                                  
output ["\nSolution:\n"]++[show(Sol)]++["\n"]++["Cost: "++show (
         sum (i in 1..Items) (StockingCosts[i] * sum(t in 1..Periods, j in 1..t)(X[(i-1)*Periods+j]-Demands[i,j]))
          +
          sum (i in 1..Periods-1) (if Sol[i] != Sol[i+1] then SetupCosts[Sol[i]+1,Sol[i+1]+1] else 0 endif)
          )++"\n"]
