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

stocking_cost (1,13).
stocking_cost (2,13).

setup_cost (X,X,0) :- items(X).
setup_cost (1,2,168).
setup_cost (2,1,146).

1 { assign(P,I) : items(I) } 1 :- periods(P).

sum_prod(I,P,N) :- N = #count{ P1 : assign(P1,I), periods(P1), P1<=P }, items(I), periods(P).

sum_dem(I,P,N) :- N = #count{ P1 : demand(I,P1), periods(P1), P1<=P }, items(I), periods(P).

:- sum_dem(I,P,N1), sum_prod(I,P,N2), N1>N2, items(I), periods(P).


stock (N,P,I) :- N = #sum{ M : sum_dem(I,P,N1), sum_prod(I,P,N2), M=(N2) },
                 items(I), periods(P).

#minimize { N : stock(N,P,I), items(I), periods(P) }.


%#minimize { N : sum_dem(I,P,N1), sum_prod(I,P,N2), stocking_cost(I,M), N=M*(N2-N1),
%                periods(P), items(I) }.

%#minimize { N : setup_cost(I1,I2,N), assign(P,I1), assign(P+1,I2), periods(P), periods(P+1),
%                items(I1), items(I2) }.

%#show assign/2.
#show sum_prod/3.
