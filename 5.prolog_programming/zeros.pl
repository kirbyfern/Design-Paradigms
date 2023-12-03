% Zeros relation
zeros([], 0).
zeros([0 | T], Z) :- zeros(T, Z1), !, Z is Z1 + 1.
zeros([_ | T], Z) :- zeros(T, Z).

% Example usage:
% ?- zeros([1, 0, 0, 5], X).
% X = 2
% ?- zeros([], X).
% X = 0
