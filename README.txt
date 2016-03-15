README for Othello Tournament
by Grace Chen and Mary Giambrone


== Grace Chen ==
Wrote a pseudocode outline for the minimax algorithm.
Later wrote the actual code for the minimax algorithm, with the exception
of the scoring function. Also wrote some helper functions for player.cpp and
testminimax to use.
Wrote this README.txt.

== Mary Giambrone ==
Wrote the code for first two versions: 1. Return first legal move it finds,
and 2.  Heuristic function, which returns the move with the best score.
Wrote the scoring function for the minimax algorithm, which returns the score
of the board after a particular move is made. Also wrote some helper functions
for player.cpp.


== Improvements ==
The first major improvement we made was changing our scoring system. We found
some minor errors in our scoring function, namely which tiles it would modify
the score for. Then, rather than multiplying the score by 3 or 5 for sides and corners,
as was used in lecture, we decided to add or subtract a certain amount from
the score. This actually worked much better for our algorithm, as we could
consistently win games after we implemented the change.

Our next major step is using an algorithm called Negascout, or alternatively,
Principal variation search. We first found the algorithm when we were looking more
into alpha-beta pruning. It is similar to alpha-beta pruning in that it computes
minimax while getting rid of nodes it doesn't need to search anymore. However,
it also never examines a node that can be pruned by alpha-beta pruning.