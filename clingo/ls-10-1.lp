items (1..2).
periods (1..10).
demand (2,1).
demand (2,2).
demand (1,4).
demand (2,4).
demand (1,6).
demand (1,7).
demand (2,7).
demand (2,9).
demand (1,10).
demand (2,10).

%items (1..2).
%periods (1..3).
%demand (1,1).
%demand (2,2).
%demand (1,3).


stocking_cost (1,13).
stocking_cost (2,13).

setup_cost (X,X,0) :- items(X).
setup_cost (1,2,168).
setup_cost (2,1,146).
