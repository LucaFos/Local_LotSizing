periods (1..10).
items (1..2).
demand (2,1).
demand (1,3).
demand (1,6).
demand (2,6).
demand (1,7).
demand (2,7).
demand (1,8).
demand (2,9).
demand (1,10).
demand (2,10).

stocking_cost (1,13).
stocking_cost (2,9).

setup_cost (X,X,0) :- items(X).
setup_cost (1,2,128).
setup_cost (2,1,186).
