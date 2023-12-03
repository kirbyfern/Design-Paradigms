% kbase1 knowledge base
woman(mia).
woman(jody).
woman(yolanda).
loves(vincent, mia).
loves(marcellus, mia).
loves(pumpkin, honey_bunny).
loves(honey_bunny, pumpkin).

% Queries
% a. tell me which of the individuals you know about is a woman.
is_woman(X) :- woman(X).

% b. Is there any individual X such that Marcellus loves X and X is a woman?
marcellus_loves_woman(X) :- loves(marcellus, X), woman(X).
