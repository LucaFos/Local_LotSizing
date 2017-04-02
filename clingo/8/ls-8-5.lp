periods (1..8).
items (1..2).
demand (1,1).
demand (1,4).
demand (2,4).
demand (1,6).
demand (1,7).
demand (2,7).
demand (1,8).
demand (2,8).

stocking_cost (1,41).
stocking_cost (2,12).

setup_cost (X,X,0) :- items(X).
setup_cost (1,2,65).
setup_cost (2,1,56).
