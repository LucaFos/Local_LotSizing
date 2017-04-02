periods (1..10).
items (1..2).
demand (1,1).
demand (1,2).
demand (1,4).
demand (2,6).
demand (1,7).
demand (2,7).
demand (1,8).
demand (1,9).
demand (2,9).
demand (1,10).

stocking_cost (1,8).
stocking_cost (2,9).

setup_cost (X,X,0) :- items(X).
setup_cost (1,2,34).
setup_cost (2,1,72).
