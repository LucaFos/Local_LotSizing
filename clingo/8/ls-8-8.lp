periods (1..8).
items (1..2).
demand (2,1).
demand (1,2).
demand (1,3).
demand (1,4).
demand (1,6).
demand (2,6).
demand (1,7).
demand (2,8).

stocking_cost (1,9).
stocking_cost (2,12).

setup_cost (X,X,0) :- items(X).
setup_cost (1,2,34).
setup_cost (2,1,24).
