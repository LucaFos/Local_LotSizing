int: Periods;
int: Items;
array[1..Items,1..Periods] of 0..1: Demands;
array[1..Items] of int: StockingCosts;
array[1..Items,1..Items] of int: SetupCosts;
array[1..Periods*Items] of var 0..1: X;        % Output matrix
array[1..Periods] of var 0..Items-1: Sol;      % Output array

% array[1..Periods] of int: SolMia = [10, 9, 4, 4, 13, 13, 3, 7, 1, 5, 19, 19, 17, 12, 8, 8, 8, 16, 10, 10, 6, 6, 6, 3, 16, 10, 13, 13, 13, 13, 13, 9, 11, 10, 3, 3, 17, 18, 5, 15, 19, 10, 10, 13, 8, 6, 0, 0, 2, 2, 7, 8, 8, 8, 1, 1, 5, 5, 6, 9, 17, 19, 15, 18, 12, 0, 7, 7, 1, 5, 5, 15, 14, 0, 16, 16, 18, 5, 2, 0, 0, 17, 19, 19, 10, 11, 1, 1, 1, 15, 4, 0, 17, 12, 8, 14, 14, 0, 11, 18, 13, 13, 13, 8, 10, 10, 15, 15, 5, 6, 12, 16, 19, 19, 19, 18, 18, 18, 6, 2, 2, 3, 3, 1, 1, 15, 15, 9, 17, 11, 11, 18, 5, 3, 3, 15, 15, 15, 7, 3, 9, 9, 19, 19, 12, 8, 6, 6, 0, 4, 8, 15, 19, 7, 7, 16, 16, 5, 5, 5, 2, 12, 1, 1, 14, 0, 17, 17, 15, 6, 9, 2, 12, 12, 1, 1, 10, 13, 14, 15, 2, 14, 19, 5, 18, 6, 2, 2, 13, 15, 17, 11, 10, 13, 0, 1, 5, 7, 11, 11, 3, 16, 18, 13, 13, 7, 1, 1, 1, 17, 9, 9, 9, 2, 2, 2, 2, 6, 1, 4, 4, 4, 11, 11, 5, 6, 6, 13, 13, 7, 7, 1, 12, 12, 8, 4, 4, 4, 4, 3, 3, 16, 8, 8, 15, 11, 11, 11, 14, 18, 18, 17, 12, 19, 19, 15, 15, 4, 11, 11, 12, 9, 9, 6, 6, 7, 7, 0, 11, 11, 4, 10, 10, 9, 14, 0, 1, 1, 5, 2, 2, 2, 7, 9, 9, 18, 18, 13, 13, 13, 13, 19, 11, 10, 4, 7, 1, 19, 19, 16, 8, 18, 2, 2, 4, 4, 4, 0, 17, 19, 11, 10, 3, 3, 14, 14, 8, 8, 6, 5, 5, 18, 17, 17, 12, 0, 0, 9, 9, 15, 18, 2, 2, 2, 2, 5, 8, 6, 16, 10, 11, 11, 1, 1, 1, 1, 1, 1, 1, 12, 15, 15, 15, 18, 6, 9, 9, 4, 4, 15, 14, 19, 0, 0, 7, 7, 8, 15, 15, 13, 3, 3, 3, 12, 18, 18, 19, 8, 8, 9, 2, 2, 3, 3, 13, 13, 5, 10, 16, 16, 19, 12, 12, 3, 11, 11, 14, 7, 17, 9, 9, 9, 15, 15, 5, 12, 16, 19, 19, 18, 17, 4, 10, 3, 3, 3, 16, 10, 10, 10, 13, 13, 0, 18, 18, 18, 18, 0, 0, 1, 1, 19, 15, 2, 2, 14, 14, 6, 6, 1, 1, 1, 15, 15, 19, 10, 10, 10, 13, 9, 14, 7, 7, 17, 0, 11, 10, 13, 13, 18, 5, 6, 9, 12, 16, 16, 6, 1, 17, 11, 13, 19, 18, 18, 10, 10, 19, 19, 19, 0, 8, 8, 6, 7, 1, 5, 8, 11, 11, 6, 9, 4, 1, 7, 2, 14, 15, 13, 4, 17];

% constraint
%       forall (p in 1..Periods)
%               (Sol[p] == SolMia[p]);

constraint
      forall (t in 1..Periods)
              (sum(i in 1..Items)(X[(i-1)*Periods+t]) == 1);

constraint
      forall (i in 1..Items, j in 1..Periods)
               (sum (k in 1..j) (Demands[i,k]) <= sum (k in 1..j) (X[(i-1)*Periods+k]));


constraint
      forall(t in 1..Periods)
               (sum (i in 1..Items)(i*X[(i-1)*Periods+t]) == Sol[t]+1);


solve:: int_search(X, occurrence, indomain_random, complete) 
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
