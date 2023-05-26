# Program_Analyzer
Created a Program Analyzer which takes a CPP code as a input and returns the Available Expressions and Live Variables in input code.

The program is parsed into a vector of statements, where each statement consists of an expression and the variables involved.
The code takes a program as input and analyzes the dependencies between expressions and variables.
It identifies the available expressions that can be computed at compile time and the live variables that hold values used before being modified.
First of all it parses the program into statements, each consisting of an expression and the variables involved.
Then it builds map of expression dependencies for each variable.
Then it performs available expressions analysis by checking if variables in the statement have only one expression dependency and adding the expression to the available expressions set.
Then it performs live variable analysis by identifying variables whose expression is not in the available expressions set and adding them to the live variables set.
Prints the available expressions and live variables as the analysis results as output.
