# Stack_Implementation_Expression_Evaluation
It’s required to implement Stack (Array Based or Linkedlist Based) with the
following function: -
1. Initialize
Prototype  Stack* initialize();
It initializes stack so that there are no elements inserted.
2. Pop
Prototype  Item pop (Stack *s);
It removes the last inserted element in the stack and return it.
3. Push
Prototype  void push(Stack *s,Item value);
It inserts element at the top of the stack.
4. Top
Prototype  Item top (Stack *s);
It returns the last inserted element in the stack without removing it.
5. isEmpty
Prototype int isEmpty(Stack *s);
It returns 1 if stack is empty or 0 otherwise.

Part 2:
Write a C function that takes a infix expression as input and convert it to
postfix
Function prototype 
void infixTopostfix(char *infix, char* postfix);
Note that infix input is the infix expression and postfix is an empty array
and will be filled with postfix expression

Part 3:
Write a C function that takes a postfix expression as input and shows the
value of the value of the expression as output.
The input will be a postfix (not infix) and you have to use your
stack implementation to evaluate the expression.
Function prototype  float evaluatePostfix(char* postfix);
Part 4:
The main should take a string as input from user, convert it to postfix
notation using infixToPostfix(), and then call evaluatePostfix().
