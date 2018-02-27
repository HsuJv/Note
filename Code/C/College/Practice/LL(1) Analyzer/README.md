# Course project: Grammar Analyzer for LL(1)

<!-- MarkdownTOC -->

- [Project Requirement](#project-requirement)
- [Requirement 1: Store the grammar in memory](#requirement-1-store-the-grammar-in-memory)
- [Requirement 2: Detect and eliminate left recursion](#requirement-2-detect-and-eliminate-left-recursion)
- [Requirement 3: Work out the First and Follow sets for all the symbols](#requirement-3-work-out-the-first-and-follow-sets-for-all-the-symbols)
- [Requirement 4: Construct LL\(1\) analysis table](#requirement-4-construct-ll1-analysis-table)
- [Requirement 5: Build the LL\(1\) analysis program](#requirement-5-build-the-ll1-analysis-program)
- [Data Dictionary](#data-dictionary)
- [Reference](#reference)

<!-- /MarkdownTOC -->


### Project Requirement
+ This system will identify whether a character sequence is a sentence of a grammar given by the user
    + The grammar is restrained by following rules: 
        + It must be context-free grammar; 
        + After a limited number of equivalent conversion, it turns out to be a LL(1) Grammar;
        + A nonterminal can not be generalized to derive two or more sentence patterns that begin with the same nonterminal;
        + There are no white blank characters in the alphabet.
        + The character 0 is a reserved for ε.
    + The grammar should be stored in a file name "grammar.txt":
        + The first line will be non-terminals, starting with the start symbol, separated by a single blank; 
        + The second line will be terminals, separated by a single blank; 
        + Following are the lines of each and only A rule:
            * The first symbol is the right part of the rule; 
            * The remaining symbols are the left part of the rule, separated by a single blank.

### Requirement 1: Store the grammar in memory
+ The grammar has already been stored in the disk.
+ This system will read it line by line
    * For the first, a linked list is used to store all the nonterminals
    * For the second, the former linked will be used as well to store all the terminals
    * For the remaining lines, a counter is used to count how many rules is there in this grammar
    * And the file pointer will be seek to the third line to read in all the rules.

### Requirement 2: Detect and eliminate left recursion
+ Sort non-terminal characters
+ Scan non-terminal, for each symbol x:
    + Scan the symbol y in front of it
    + If there is a rule x :: = y ..., then all the patterns that can be deduced directly from y are substituted into y in sequence to generate new rules
+ Delete the direct left recursion about x:
    * If there is a rule x :: = x ..., then rewrite it as x :: = a x', x' :: = ... x' | ε, where a is a pattern that all x can derive directly, not starting with x.

### Requirement 3: Work out the First and Follow sets for all the symbols
+ First set:
    * For each X in the alphabet, if X belongs to VT, First(X) = {X};
    * if there are rules in the form of X ::= a alpha | epsilon for a belongs to VT, a and/or epsilon will be appended to First(X);
    * if there are rules in the form of X ::= Y1 Y2 Y3 ... Yk, for Yn belongs to VN, First(Y1) without epsilon will be appended to First(X); if epsilon is in First(Y1), then First(Y2) without epsilon will be appended to First(X), etc (Till Y(k-1));
    * if for all symbols in Y1 Y2 Y3 ... Yk, epsilon is in First(Yn), epsilon will be appended to First(X);
    * Repeat the above steps until the First set is no longer enlarged.
+ Follow set:
    * For each B belongs to VN, if B is the start symbol of grammar, then the terminator will be appended to Follow(B);
    * if there are rules in form of A ::= alpha B beta, and beta != epsilon, then First(beta) without epsilon will be appended to Follow(B);
    * if there are rules in form of A ::= alpha B or A ::= alpha B beta (beta can be generalized to epsilon), then Follow(A) will be appended to Follow(B);
    * Repeat the above steps until the Follow set is no longer enlarged.

### Requirement 4: Construct LL(1) analysis table
+ For each rule A ::= alpha:
    * For all a in alphabet, T[A, a] = 0;
    * For each terminal a in First(alpha), T[A, a] = "A ::= alpha";
    * If epsilon belongs to First(alpha), for each b in Follow(A), T[A, b] = "A ::= alpha"

### Requirement 5: Build the LL(1) analysis program
+ The program should identify whether a character sequence is a sentence of a grammar given by the user
    * Push the start symbol into the analysis stack;
    * Traverse all terminators, comparing the terminal-length string which the input string scan pointer pointing with the terminal, selecting the input terminal as long as possible.
    * If the input terminal equals to the top of analysis stack, scan pointer will move backward, the top of stack will be popped;
    * Else, the stack top will be popped as well, but the rule T[stack top, input terminal] will be pushed in to the analysis stack in reserve.
    * If the scan pointer is pointing the end of input string, then consider it as the terminator;
+ The program should display the procedure of the analysis

### Data Dictionary
+ Nonterminals are stored in a linked list that each nodes consists of a serial number (odd), the symbol, the address point to its First set and the address point to its Follow set.
+ Terminal are stored in a linked list that each nodes consists of a serial number (even), the symbol, the address point to its First set and the address point to its Follow set.
+ Grammar rules are stored in an array that each element of this array is a address point to the top of an array which represents a single grammar rule.
+ Analysis table are stored in a two dimensional array which a row of it represents a nonterminal of the grammar and a column of it represents a terminal of the grammar 

### Reference
+ <编译技术原理及其应用方法> 王汝传 编著