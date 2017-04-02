periods (1..8).
items (1..2).
demand (2,1).
demand (2,2).
demand (1,4).
demand (1,5).
demand (2,5).
demand (1,7).
demand (2,7).
demand (2,8).

stocking_cost (1,14).
stocking_cost (2,8).

setup_cost (X,X,0) :- items(X).
setup_cost (1,2,116).
setup_cost (2,1,114).
