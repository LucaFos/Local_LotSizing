%% Lot-Sizing%%

%Input
int: Periods;
int: Items;
array[1..Items,1..Periods] of 0..1: Demands;
array[1..Items] of int: StockingCosts;
array[1..Items,1..Items] of int: SetupCosts;
array[1..Items, 1..Periods] of var 0..1: X;      % Output matrix
array[1..Items*Items*Periods] of var 0..1: Y;

%Output
array[1..Periods] of var 1..Items: SolVett;      % Output array

%Constraints

%in ogni periodo può essere eseguito un solo item
constraint
      forall (t in 1..Periods)
              (sum(i in 1..Items)(X[i,t]) == 1);

%in ogni istante possono essere stati fatti almeno quanti item richiesti o di più (mai di meno)
constraint
      forall (i in 1..Items, j in 1..Periods)
               (sum (k in 1..j) (Demands[i,k]) <= sum (k in 1..j) (X[i,k]));

constraint
      forall (i in 1..Items, j in 1..Items, t in 1..Periods-1)
               (Y[(i-1)*Items*Periods+(j-1)*Periods+t] >= X[i,t] + X[j,t+1] -1);

constraint
      forall (i in 1..Items, j in 1..Items, t in 1..Periods-1)
               (2*Y[(i-1)*Items*Periods+(j-1)*Periods+t] <= X[i,t] + X[j,t+1]);

constraint
      forall(t in 1..Periods)
               (sum (i in 1..Items)(i*X[i,t]) == SolVett[t]);

%:: int_search(SolVett, input_order, indomain_random, complete)
%:: int_search(SolVett, impact, indomain, complete) 
solve minimize (
          sum (i in 1..Items) (StockingCosts[i] * sum(t in 1..Periods, j in 1..t)(X[i,j]-Demands[i,j]))
          +
          sum (i in 1..Items, j in 1..Items) (SetupCosts[i,j] * sum(t in 1..Periods)( Y[(i-1)*Items*Periods+(j-1)*Periods+t]))
         );

                                                                                                                                  
output ["\nSolution:\n"]++[show(SolVett)]++["\n"]++["Cost: "++show (
         sum (i in 1..Items) (StockingCosts[i] * sum(t in 1..Periods, j in 1..t)(X[i,j]-Demands[i,j]))
          +
          sum (i in 1..Items, j in 1..Items) (SetupCosts[i,j] * sum(t in 1..Periods)( Y[(i-1)*Items*Periods+(j-1)*Periods+t])))++"\n"]
