/* GRUPO A2 SUBGRUPO 1.4*/

:-lib(ic).
:-lib(clpb).
:-use_module(library(clpfd)).

/*APARTADO A*/

/*APARTADO B*/
asignaTrabajadores(Var):-
	Var=[W1, W2, W3, W4],
	Var::[1, 2, 3, 4],
	alldifferent(Var),

	element(W1, [7,1,3,4], EW1),
	element(W2, [8,2,5,1], EW2),
	element(W3, [4,3,7,2], EW3),
	element(W4, [3,1,6,3], EW4),
	EW1+EW2+EW3+EW4#>18,
	labeling(Var),

	C is EW1+EW2+EW3+EW4,
	write("Coste asignacion: "), writeln(C).

/*APARTADO C*/
asignaProductos(Var):-
   Var=[P1, P2, P3, P4],
   Var::[1, 2, 3, 4],
   alldifferent(Var),

   element(P1, [7,8,4,3], EP1),
   element(P2, [1,2,3,1], EP2),
   element(P3, [3,5,7,6], EP3),
   element(P4, [4,1,2,3], EP4),
   EP1+EP2+EP3+EP4#>18,

   labeling(Var),

   C is EP1+EP2+EP3+EP4,
   write("Coste asignacion: "), writeln(C).
