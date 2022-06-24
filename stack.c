#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Item: An item that is being pushed to or popped from the stack
* It may be float (to be used while evaluating the postfix)
* It may be char (to be used while converting infix to postfix)
*/
typedef union
{
    float fData;
    char  cData;
} Item;
/*
*



*/


#include "LinkedList.c" //defines struct Node and newNode()

typedef struct
{
   Node* top;
   int num;
} Stack;
/*
*
*/
Stack * initialize()
{
   Stack* s = (Stack*) malloc(sizeof(Stack));
   s->num = 0;
   s->top = NULL;
   return s;

}
/*
*
*/
int isEmpty(Stack *s)
{
    return s->num == 0 ? 1 : 0;
}
/*
*
*/
Item top(Stack *s)
{
    return s->top->val;
}
/*
*
*/
Item pop(Stack *s)
{
   s->num--;
   Node* l = s->top;
   s->top = s->top->next;
   Item val = l->val;
   free(l);
   return val;
}
/*
*
*/
void push(Stack *s, Item val)
{
   s->num++;
   Node* l = newNode(val);
   l->next = s->top;
   s->top = l;
}
/*
* infixToPostfix: converts an expression in infix notation to
* to a postfix notation (Reverse-Polish Notation)
* ASSUME single-digit operands
* ASSUME ^*+-/ operators
* e.g., 22+31 --> 22 31 +
* e.g., (2+3)*4 --> 2 3 + 4 *
*/

#include "evaluate.c" //defines evaluate(), operandToFloat(), isOperator() and isOperand()
#include "infixHelper.c"  //defines isNumeric() and priority()
void infixToPostfix(char* infix, char* postfix)
{
    Stack *copy= initialize();
    char *ptr = calloc(strlen(infix) + 1, 1);
    strcpy(ptr, infix);
    char *token = strtok(ptr," ");
    int index=0;
    int twoInARow = 1; //Flag used to check if there is two operators or two operands after each other
    while(token)
    {
            if(isOperand(token))
            {
                if(twoInARow==0)
                {
                    printf("Invalid Expression 1 %s\n", token);
                    exit(-1);
                }
                twoInARow=0;
                int i=0;
                while(token[i]!='\0')
                {
                    postfix[index++]=token[i++];
                }
                postfix[index++]=' ';
            }
            else if (token[0]=='(')
            {
                push(copy,(Item)(token[0]));
            }
            else if (token[0]==')')
            {
                while( !isEmpty(copy) && top(copy).cData!='(')
                {
                    postfix[index++]=pop(copy).cData;
                    postfix[index++]=' ';
                }
                if (isEmpty(copy) || top(copy).cData!='(')
                {
                    printf("Invalid Expression 2 %s\n", token);
                    exit(0);
                }
                pop(copy);
            }
            else if (isOperator(token[0]) && strlen(token) == 1) //length check is necessary for edge cases such as "5 4 -+"
            {
                if(twoInARow==1)
                {
                    printf("Invalid Expression 3 %s\n", token);
                    exit(-1);
                }
                twoInARow=1;
                while( !isEmpty(copy) && top(copy).cData!='(' && priority(top(copy).cData)>=priority(token[0]) )
                {
                    char x=pop(copy).cData;
                    if (x!='(')
                    {
                        postfix[index++]=x;
                        postfix[index++]=' ';
                    }
                }
                push(copy,(Item)(token[0]));
            } else {
                printf("Invalid expression 4 %s\n", token);
                exit(-1);
            }
        token=strtok(NULL," ");
    }
    while(!isEmpty(copy))
    {
        if (top(copy).cData=='(' || top(copy).cData==')')
        {
            printf("Invalid Expression 5\n");
            exit(-1);
        }
        postfix[index++]=pop(copy).cData;
        postfix[index++]=' ';
    }
    postfix[index++]='\0';
}
/*
* evaluatePostfix: Evaluates an expression in postfix notation
* (Reverse-Polish Notation)
* ASSUME single-digit operands
*/

#include <ctype.h> //needed for isdigit()

float evaluatePostfix(char* postfix)
{
    Stack* s = initialize();
    float out;
    int i;
    Item operand1, operand2;
    char* current;
    current = strtok(postfix, " ");
    //printf("no seg fault yet");
    while (current != NULL){
       //printf("no seg fault yet");
       if (isOperator(current[0]) && strlen(current) == 1){   //length check is necessary for edge cases such as "5 4 -+"
          if (isEmpty(s)){
             printf("Invalid expression!\n");
             exit(-1);
          }
          operand2 = pop(s);

          if (isEmpty(s)){
             printf("Invalid expression!\n");
             exit(-1);
          }
          operand1 = pop(s);

          push(s, (Item) (evaluate(current[0], operand1, operand2)));
       }else if (isOperand(current)) {
          push(s, (Item) operandToFloat(current));
       } else {
          printf("Invalid expression!\n");
          exit(-1);
       }
       current = strtok(NULL, " ");
    }
    out = pop(s).fData;
    return out;
}
/*
*
*/
void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}
/*
*
*/
int main(int argc, char**argv)
{
    char infixExpr[256] = "";
    char postfixExpr[256] = "";
    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);
        infixToPostfix(infixExpr, postfixExpr);
        printf("Postfix : %s\n", postfixExpr);
        float result = evaluatePostfix(postfixExpr);
        printf("Result: %f\n\n", result);
        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    }
    return 0;
}







/*
int main(){
   //Ramez tests

   //Linked list tests
   Item x, y, z;
   x.cData = 'b';
   y.cData = 'c';
   z.cData = 'd';
   Node* n = newNode(x);
   n->next = newNode(y);
   printf("%c %p %c %p\n", n->val.cData, n->next, n->next->val.cData, n->next->next);

   //Stack tests
   Stack* s = initialize();
   printf("\n%d\n", isEmpty(s));
   push(s, x);
   printf("%d\n", isEmpty(s));
   push(s, y);
   push(s, z);
   push(s, (Item) (char) 'e');
   printf("%c\n", top(s).cData);
   printf("%c\n", pop(s).cData);
   printf("%c\n", top(s).cData);
   printf("%c\n", pop(s).cData);
   printf("%c\n", pop(s).cData);

   //evaluatePostfix tests
   printf("%d\n", isOperand("-2.5"));
   //char postfix[] = " 1 2 + 5 + -80.5 -";
   //printf("\n%f\n", evaluatePostfix(postfix));


   //////////////////////////////////////////////////////////////////////////////////////
   //Amr tests
   char infix[200] = "2 + ( -2.5 + 3.14 ) * ( -5.4 + 8.1 ) ^ ( -0.5 )", postfix[200];
   infixToPostfix(infix, postfix);
   printf("\n%s %f\n" , postfix, evaluatePostfix(postfix));

   return 0;
}


*/
