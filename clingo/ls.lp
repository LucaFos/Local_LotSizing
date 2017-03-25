%items (1..2).
%periods (1..10).
%demand (2,1).
%demand (2,2).
%demand (1,4).
%demand (2,4).
%demand (1,6).
%demand (1,7).
%demand (2,7).
%demand (2,9).
%demand (1,10).
%demand (2,10).

items (1..2).
periods (1..3).
demand (1,1).
demand (2,2).
%demand (1,3).

stocking_cost (1,13).
stocking_cost (2,14).

setup_cost (X,X,0) :- items(X).
setup_cost (1,2,168).
setup_cost (2,1,146).


1 { assign(P,I) : items(I) } 1 :- periods(P).

sum_prod(I,P,N) :- N = #count{ P1 : assign(P1,I), periods(P1), P1<=P }, items(I), periods(P).

sum_dem(I,P,N) :- N = #count{ P1 : demand(I,P1), periods(P1), P1<=P }, items(I), periods(P).

:- sum_dem(I,P,N1), sum_prod(I,P,N2), N1>N2, items(I), periods(P).


stock (I,P,N) :- N = #sum{ M : sum_dem(I,P,N1), sum_prod(I,P,N2), stocking_cost(I,C),
                          M=C*(N2-N1) },
                 items(I), periods(P).

sum_stock (N) :- N = #sum{ M,I,P : stock(I,P,M) }.


#minimize { N : sum_stock(N) }.


#show assign/2.
%#show sum_dem/3.
%#show stock/3.
#show sum_stock/1.
