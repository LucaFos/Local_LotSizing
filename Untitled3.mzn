%% Lot-Sizing%%

%Input
int: Periods;
int: Items;
array[1..Items,1..Periods] of 0..1: Demands;
array[1..Items] of int: StockingCosts;
array[1..Items,1..Items] of int: SetupCosts;
var 0..1: Execute; %oggetto eseguito al tempo t
var 0..1: Changed; %oggetto i cambiato con oggetto j in tempo t

%Output
array[1..Periods] of var 0..Items-1: SolVett;      % Output array
array[1..Items, 1..Periods] of var 0..1: SolMat;      % Output matrix

%Constraints

%in ogni istante possono essere stati fatti almeno quanti item richiesti o di più (mai di meno)
constraint
      forall (i in 1..Items, j in 1..Periods)
               (sum (k in 1..j) (Demands[i,k]) <= sum (k in 1..j) (SolMat[i,k]));

%vanno fatti tanti item quanti richiesti
constraint
     forall (i in 1..Items)
               (sum (k in 1..Periods) (Demands[i,k]) == sum (j in 1..Periods) (SolMat[i,j]));

%si riduce da sinistra la somma dei periodi e quando questa fa 0 significa che non ci sono più richieste di quell'item
constraint
     forall (i in 1..Items, j in 1..Periods)
               (sum (k in j..Periods) (Demands[i,k]) == 0 -> SolMat[i,j] != 1);
%riempimento vettore
constraint 
     forall (i in 1..Items, p in 1..Periods)
               (if SolMat[i,p] == 1 then SolVett[p] = i-1 else SolMat[i,p] = 0 endif);


solve :: int_search(SolVett, input_order, indomain_min, complete)
minimize (
          sum (i in 1..Periods-1) (if SolVett[i] != SolVett[i+1] then SetupCosts[SolVett[i]+1,SolVett[i+1]+1] else 0 endif)
          +
          sum (i in 1..Items, j in 1..Periods) ((sum (k in 1..j) (if SolVett[k]=i-1 then 1 else 0 endif) - sum (k in 1..j) (Demands[i,k])) * StockingCosts[i])
         );

                                                                                                                                  
output ["\nSolution:\n"]++[show(SolVett)]++["\n"]++["Cost: "++show (
          sum (i in 1..Periods-1) (if SolVett[i] != SolVett[i+1] then SetupCosts[SolVett[i]+1,SolVett[i+1]+1] else 0 endif)
          +
          sum (i in 1..Items, j in 1..Periods) ((sum (k in 1..j) (if SolVett[k]=i-1 then 1 else 0 endif) - sum (k in 1..j) (Demands[i,k])) * StockingCosts[i])
         )++"\n"]
