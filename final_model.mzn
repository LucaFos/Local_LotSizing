int: Periods;
int: Items;
array[1..Items,1..Periods] of 0..1: Demands;
array[1..Items] of int: StockingCosts;
array[1..Items,1..Items] of int: SetupCosts;
array[1..Items,1..Periods] of var 0..1: SolMatrix;        % Solution matrix
array[1..Periods] of var 0..Items-1: Sol;                 % Output array

constraint
      forall (t in 1..Periods)
              (sum(i in 1..Items)(SolMatrix[i,t]) == 1);

constraint
      forall (i in 1..Items, j in 1..Periods)
               (sum (k in 1..j) (Demands[i,k]) <= sum (k in 1..j) (SolMatrix[i,k]));


constraint
      forall(t in 1..Periods)
               (sum (i in 1..Items)(i*SolMatrix[i,t]) == Sol[t]+1);


solve:: int_search([SolMatrix[i,j] | i in 1..Items, j in 1..Periods], occurrence, indomain_random, complete) 
       minimize (
          sum (i in 1..Items) (StockingCosts[i] * sum(t in 1..Periods, j in 1..t)(SolMatrix[i,j]-Demands[i,j]))
          +
          sum (i in 1..Periods-1) (if Sol[i] != Sol[i+1] then SetupCosts[Sol[i]+1,Sol[i+1]+1] else 0 endif)
         );


output ["Cost: "++show (
         sum (i in 1..Items) (StockingCosts[i] * sum(t in 1..Periods, j in 1..t)(SolMatrix[i,j]-Demands[i,j]))
          +
          sum (i in 1..Periods-1) (if Sol[i] != Sol[i+1] then SetupCosts[Sol[i]+1,Sol[i+1]+1] else 0 endif)
          )++" "]
        ++[show(Sol)]