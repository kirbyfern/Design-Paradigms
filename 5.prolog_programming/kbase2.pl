% kbase2 knowledge base
loves(vincent, mia).
loves(marcellus, mia).
loves(pumpkin, honey_bunny).
loves(honey_bunny, pumpkin).

% Rule: Jealousy rule
jealous(X, Y) :-
    loves(X, Z),
    loves(Y, Z).