Logic Engine side of ALPACA

Tree:
Parses input statements depending on specific symbols

Syntax
Negation    ~
Or          v
And         &
Conditional > or |
XOr         @
Blocks for node name are figured using parenthesis (VALUE)

(-) Very finicky syntax

Statementevaluator:
Using parsed in information, generates 0 order logic truth table
showing all possible results from True/False input values

(-) Limit in how many nodes can be used for truth table

LogicGate:
Currently takes in simple node info that can have updated
Truth/False input values, with possibly adding and removing of nodes

(-) Bug in state change currently
(-) Cannot add logical operators yet