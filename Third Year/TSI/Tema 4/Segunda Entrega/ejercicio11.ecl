/* GRUPO A2 SUBGRUPO 1.4*/

:- lib(fd).

profesores(Vars):-
	% Variables
	Vars=[Pedro, Juana, Ana, Yago, David,Maria],
	Pedro #::[3..6],
	Juana #::[3..4],
	Ana #::[2..5],
	Yago #::[2..4],
	David #::[3..4],
	Maria #::[1..6],
	alldifferent(Vars),
	S#=Juana+Ana+Maria,
	minimize(labeling(Vars),S).

