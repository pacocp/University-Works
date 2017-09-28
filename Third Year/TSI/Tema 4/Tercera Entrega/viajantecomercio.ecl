:-lib(fd).

viajanteComercio(Var):-
	Var=[X1, X2, X3, X4,X5,X6,X7],
	element(X1,[0,4,8,10,7,14,15],EX1),
	element(X2,[4,0,7,7,10,12,5],EX2),
	element(X3,[8,7,0,4,6,8,10],EX3),
	element(X4,[10,7,4,0,2,5,8],EX4),
	element(X5,[7,10,6,2,0,6,7],EX5),
	element(X6,[14,12,8,5,6,0,5],EX6),
	element(X7,[15,5,10,8,7,5,0],EX7),
	gfd:circuit(Var),
	Coste #= EX1+EX2+EX3+EX4+EX5+EX6+EX7,
	minimize(labeling(Var),Coste).

