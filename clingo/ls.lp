1 { assign(P,I) : items(I) } 1 :- periods(P).

sum_prod(I,P,N) :- N = #count{ P1 : assign(P1,I), periods(P1), P1<=P }, items(I), periods(P).

sum_dem(I,P,N) :- N = #count{ P1 : demand(I,P1), periods(P1), P1<=P }, items(I), periods(P).

:- sum_dem(I,P,N1), sum_prod(I,P,N2), N1>N2, items(I), periods(P).


stock (I,P,N) :- N = #sum{ M : sum_dem(I,P,N1), sum_prod(I,P,N2), stocking_cost(I,C),
                          M = C*(N2-N1) },
                 items(I), periods(P).

sum_stock (N) :- N = #sum{ M,I,P : stock(I,P,M) }.


setup (P,N) :- N = #sum{ M : assign(P,I1), assign(P+1,I2), I1!=I2, setup_cost(I1,I2,C),
                        M = C },
                   periods(P).
sum_setup (N) :- N = #sum{ M,P : setup(P,M) }.


sum_total (N) :- N = N1+N2, sum_stock(N1), sum_setup(N2).


#minimize { N : sum_total(N) }.


%#show assign/2.
%#show sum_dem/3.
%#show stock/3.
#show sum_total/1.
