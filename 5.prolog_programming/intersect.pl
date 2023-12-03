% Intersect relation
intersect([], _, []).
intersect([X | R], Y, [X | Z]) :- member(X, Y), !, intersect(R, Y, Z).
intersect([_ | R], Y, Z) :- intersect(R, Y, Z).

% Example usage:
% ?- intersect([0, 1, 6, 3], [5, 1, 8, 2, 3, 9], X).
% X = [1, 3]
% ?- intersect([1], [4], X).
% X = []
